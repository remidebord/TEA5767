#include "Altitude.h"
#include "Config.h"

static const uint8_t altitude[4] = {' ', 'A', 'L', 'T'};
static uint8_t state = ALTITUDE_INIT;
static uint16_t timer = ALTITUDE_INIT_TIME;

void altitude_init(void)
{
	state = ALTITUDE_INIT;
	timer = ALTITUDE_INIT_TIME;
	dots = 0;
}

void altitude_main(void)
{
	uint8_t buffer[4] = {0};
	uint16_t tmp = 0;
	
	switch(state)
	{
		case ALTITUDE_INIT:
			// Display menu name
			sevenSegGroup.set((uint8_t*)&altitude[0], sizeof(altitude));
		
			if(timer == 0) state = ALTITUDE_MAIN;
			break;
		
		case ALTITUDE_MAIN:		
			// Get altitude from GPS
			tmp = gnss.altitude();
		
			// Formatting
			buffer[2] = bin2bcd((tmp % 10)) + '0';
			
			if(tmp >= 10) buffer[1] = bin2bcd((tmp / 10) % 10) + '0';
			if(tmp >= 100) buffer[0] = bin2bcd((tmp / 100) % 10) + '0';
		
			buffer[3] = 'M';
		
			// Set seven segment display
			sevenSegGroup.set(&buffer[0], sizeof(buffer));
			break;
		
		default: break;
	}
}

void altitude_sub(void)
{
	// Nothing to do !
}

void altitude_timer(void)
{
	if(timer) timer--;
}
