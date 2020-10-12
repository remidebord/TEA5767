#include "Satellites.h"
#include "Config.h"

static const uint8_t satellites[4] = {' ', 'S', 'A', 'T'};
static uint8_t state = SATELLITES_INIT;
static uint16_t timer = SATELLITES_INIT_TIME;

void satellites_init(void)
{
	state = SATELLITES_INIT;
	timer = SATELLITES_INIT_TIME;
	dots = 0;
}

void satellites_main(void)
{
	uint8_t buffer[4] = {0};
	uint16_t tmp = 0;
	
	switch(state)
	{
		case SATELLITES_INIT:
			// Display menu name
			sevenSegGroup.set((uint8_t*)&satellites[0], sizeof(satellites));
		
			if(timer == 0) state = SATELLITES_MAIN;
			break;
		
		case SATELLITES_MAIN:		
			// Get number of satellites from GPS
			tmp = gnss.satellites();
		
			// Formatting
			buffer[3] = (bin2bcd(tmp) & 0x0F) + '0';
			
			if(tmp >= 10) buffer[2] = (bin2bcd(tmp) >> 4) + '0';
		
			// Set seven segment display
			sevenSegGroup.set(&buffer[0], sizeof(buffer));
			break;
		
		default: break;
	}
}

void satellites_sub(void)
{
	// Nothing to do !
}

void satellites_timer(void)
{
	if(timer) timer--;
}
