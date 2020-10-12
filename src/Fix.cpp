#include "Fix.h"
#include "Config.h"

static const uint8_t fix[4] = {' ', 'F', 'I', 'X'};
static uint8_t state = FIX_INIT;
static uint16_t timer = FIX_INIT_TIME;

void fix_init(void)
{
	state = FIX_INIT;
	timer = FIX_INIT_TIME;
	dots = 0;
}

void fix_main(void)
{
	uint8_t buffer[4] = {0};
	uint16_t tmp = 0;
	
	switch(state)
	{
		case FIX_INIT:
			// Display menu name
			sevenSegGroup.set((uint8_t*)&fix[0], sizeof(fix));
		
			if(timer == 0) state = FIX_MAIN;
			break;
		
		case FIX_MAIN:		
			// Get altitude from GPS
			tmp = gnss.fix();
		
			if(tmp == 0) buffer[1] = 'N';
		
			buffer[2] = 'O';
			buffer[3] = 'K';
		
			// Set seven segment display
			sevenSegGroup.set(&buffer[0], sizeof(buffer));
			break;
		
		default: break;
	}
}

void fix_sub(void)
{
	// Nothing to do !
}

void fix_timer(void)
{
	if(timer) timer--;
}
