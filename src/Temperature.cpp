#include "Temperature.h"
#include "Config.h"

static const uint8_t temp[4] = {'T', 'E', 'M', 'P'};
static uint8_t state = TEMPERATURE_INIT;
static uint16_t timer = TEMPERATURE_INIT_TIME;

void temperature_init(void)
{
	state = TEMPERATURE_INIT;
	timer = TEMPERATURE_INIT_TIME;
	dots = 0;
}

void temperature_main(void)
{
	uint8_t buffer[4] = {0};
	int8_t tmp = 0;
	
	switch(state)
	{
		case TEMPERATURE_INIT:
			// Display menu name
			sevenSegGroup.set((uint8_t*)&temp[0], sizeof(temp));
			
			if(timer == 0) state = TEMPERATURE_MAIN;
			break;
		
		case TEMPERATURE_MAIN:
			// Get temperature from DS3231 RTC
			tmp = ds3231.temperature();
			
			// Formatting
			if((tmp > 9) || (tmp < -9))
			{
				if(tmp < 0) buffer[0] = '-';
					
				buffer[1] = (bin2bcd(tmp) >> 4) + '0';
			}
			else
			{
				if(tmp < 0) buffer[1] = '-';
			}
				
			buffer[2] = (bin2bcd(tmp) & 0x0F) + '0';
			buffer[3] = 'C';
			
			// Set seven segment display
			sevenSegGroup.set(&buffer[0], sizeof(buffer));
			break;
		
		default: break;
	}
}

void temperature_sub(void)
{
	// Nothing to do !
}

void temperature_timer(void)
{
	if(timer) timer--;
}
