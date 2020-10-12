#include "main.h"
#include "Config.h"

#define TEA5767_ADDR (0x60 << 1)
#define TEA5767_IF 225000 // 225 KHz

//#define SEARCH_MODE

uint8_t buffer[5] = {0x00, 0x00, 0xF8, 0x16, 0x00};
uint32_t frequency = 94000000; // 94.0 MHz
uint32_t pll = 0;
uint32_t timeout = 1000;

int main(void)
{
	uint8_t left = 0;
	uint8_t right = 0;
	
	// Callback executed every 1 ms (1000 us)
	ticker.attach_us(&tickMCU, 1000);
	
	// Add seven segment into a group
	sevenSegGroup.add(&sevenSeg0);
	sevenSegGroup.add(&sevenSeg1);
	sevenSegGroup.add(&sevenSeg2);
	sevenSegGroup.add(&sevenSeg3);
	
	// Set Digit pins open drain
	digit[0].type(Open_Drain);
	digit[1].type(Open_Drain);
	digit[2].type(Open_Drain);
	digit[3].type(Open_Drain);
	
	// Set brightness
	brightness.set(100);
	
	// Dots OFF
	dots = 0;
	
	Delay(100);
	
	pll = 4 * (frequency + TEA5767_IF) >> 15; // 32768 = 2^15
	
	buffer[0] = (uint8_t) (pll >> 8) & 0x3F;
	
#ifdef SEARCH_MODE
	buffer[0] = buffer[0] | 0x40;
#endif

	buffer[1] = (uint8_t) pll;
	
	i2c.write(TEA5767_ADDR, buffer, sizeof(buffer));
	
	sevenSegGroup.set(frequency / 100000);
	
	Delay(100);
	
  while (1)
  {
		// Manage push buttons
		buttonLeft.update();
		buttonRight.update();
		
		// Get button left and right
		left = buttonLeft.get();
		right = buttonRight.get();
		

		if((left != 0) || (right != 0))
		{	
			if(left != 0)
			{
#ifndef SEARCH_MODE
				frequency += 100000; // 0.1 MHz
#else
				buffer[2] = 0xF0;
#endif
			}
			else
			{
#ifndef SEARCH_MODE
				frequency -= 100000; // 0.1 MHz
#else
				buffer[2] = 0x70;
#endif
			}
				
			pll = 4 * (frequency + TEA5767_IF) >> 15; // 32768 = 2^15
		
			buffer[0] = (uint8_t) (pll >> 8) & 0x3F;
			
#ifdef SEARCH_MODE
			buffer[0] = buffer[0] | 0x40;
#endif
			
			buffer[1] = (uint8_t) pll;
		
			i2c.write(TEA5767_ADDR, buffer, sizeof(buffer));
			
#ifdef SEARCH_MODE
			timeout = 1000;
#endif
		}
		
#ifdef SEARCH_MODE		
		if(timeout == 0)
		{
			if(i2c.read(TEA5767_ADDR, buffer, sizeof(buffer)) != 0)
			{
				pll = 4 * (frequency + TEA5767_IF) >> 15; // 32768 = 2^15
				
				pll = (buffer[0] & 0x3F) << 8;
				pll += buffer[1];
				
				frequency = ((pll << 15) >> 2) - TEA5767_IF;
				
				timeout = 1000;
			}
		}
#endif
		
		sevenSegGroup.set(frequency / 100000);
	}
}

void tickMCU(void)
{	
	if(timeout) timeout--;
	
	buttonLeft.timer();
	buttonRight.timer();
	sevenSegGroup.timer();
	
	// Manage display
	sevenSegGroup.update();		
}
