/*!
 * \file Button.cpp
 * \brief Button API.
 * \author Rémi.Debord
 * \version 1.0
 * \date 28 janvier 2017
 *
 * Button library.
 *
 */

#include "Button.h"

Button :: Button(PinName pin): DigitalOut(pin)
{
	m_value = 0;
	m_state = WAIT_PRESS;
	m_timer = 0;
}

/*!
 *  \brief Update
 *
 *  Manage button state.
 *
 */

void Button :: update(void)
{
	switch(m_state)
	{
		case WAIT_PRESS:
			if((this->read()) && (m_value == 0))
			{
				// Debounce
				if(m_timer >= DEBOUNCE_TIME)
				{
					m_timer = 0;
					m_state = WAIT_RELEASE;
				}
			}
			else
			{
				m_timer = 0;
			}
			break;
		
		case WAIT_RELEASE:
			if(this->read() == 0)
			{
				// Short press ?
				if(m_timer < LONG_PRESS_TIME)
				{
					m_value = SHORT_PRESS;
				}
				// Long press ?
				else
				{
					m_value = LONG_PRESS;
				}
				
				m_state = WAIT_PRESS;
				m_timer = 0;
			}
			// Continuous press ?
			else if((this->read()) && (m_timer >= CONTINUOUS_PRESS_TIME))
			{
				m_value = CONTINUOUS_PRESS;
				m_state = WAIT_CONTINUOUS;
			}
			break;
			
		case WAIT_CONTINUOUS:
			if(this->read() == 0)
			{
				m_state = WAIT_PRESS;
				m_timer = 0;
			}
	}
}

uint8_t Button :: get(void)
{
	char value = m_value;
	
	m_value = 0;
	
	return value;
}

void Button :: timer(void)
{
	if(m_timer < 10000) m_timer++;
}
