#include "Clock.h"
#include "Config.h"

static const uint8_t clock[4] = {'T', 'I', 'M', 'E'};
static uint8_t state = CLOCK_INIT;
static uint16_t timer = CLOCK_INIT_TIME;

void clock_init(void)
{
	state = CLOCK_INIT;
	timer = CLOCK_INIT_TIME;
	dots = 0;
}

void clock_main(void)
{
	uint8_t buffer[4] = {0};
	uint8_t tmp = 0;
	Time t;
	
	float latitude = 0;
	float longitude = 0;
	
	switch(state)
	{
		case CLOCK_INIT:
			// Display menu name
			sevenSegGroup.set((uint8_t*)&clock[0], sizeof(clock));
		
			// Dots OFF
			dots = 0;
		
			if(timer == 0) state = CLOCK_MAIN;
			break;
		
		case CLOCK_MAIN:			
			// Get time from DS3231 RTC
			ds3231.get(&t);
			
			// Formatting
			tmp = bin2bcd(t.hours);
			
			buffer[0] = (tmp >> 4) + '0';
			buffer[1] = (tmp & 0x0F) + '0';
			
			tmp = bin2bcd(t.minutes);
			
			buffer[2] = (tmp >> 4) + '0';
			buffer[3] = (tmp & 0x0F) + '0';
			
			// Set seven segment display
			sevenSegGroup.set(&buffer[0], sizeof(buffer));
			break;
		
		case CLOCK_SUB:
			tmp = gnss.fix();
			
			// GPS fix ?
			if(tmp != 0)
			{
				gnss.time(&t);
					
				ds3231.set(&t);
			}
			
			ds3231.get(&t);
			
			ds3231.set(&t);
				
			if(timer == 0)
			{	
				state = CLOCK_MAIN;
			}
			break;
		
		default: break;
	}
}

void clock_sub(void)
{
	uint8_t buffer[4] = {'-', '-', '-', '-'};
	
	// Set seven segment display
	sevenSegGroup.set(&buffer[0], sizeof(buffer));
	
	timer = CLOCK_SYNC_TIME;
	state = CLOCK_SUB;
}

void clock_timer(void)
{
	if(timer) timer--;
}
