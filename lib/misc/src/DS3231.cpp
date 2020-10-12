/*!
 * \file DS3231.cpp
 * \brief DS3231 I2C RTC API.
 * \author Rémi.Debord
 * \version 1.0
 * \date 28 janvier 2017
 *
 * DS3231 High Precision RTC library.
 *
 */

#include "DS3231.h"

DS3231 :: DS3231(I2C* i2cx)
{
	uint8_t* ptr = 0;
	uint8_t i = 0;
	
	m_i2c = i2cx;
	m_timer = DS3231_STARTUP_TIME;
	m_state = DS3231_RESET_REGISTER_POINTER;
	
	ptr = (uint8_t*)&m_ds3231;
	
	for(i = 0; i < sizeof(m_ds3231); i++)
	{
		ptr[i] = 0x00;
	}
}

void DS3231 :: update(void)
{
	uint8_t result = 0;
	uint8_t tmp = 0;
	
	if(m_timer == 0)
	{
		switch(m_state)
		{
			case DS3231_READ_REGISTERS:
				result = m_i2c->read(DS3231_I2C_ADDR, (uint8_t*)&(m_ds3231.SECR), sizeof(m_ds3231)-1);				
				break;
			
			case DS3231_WRITE_REGISTERS:
				m_ds3231.CR = 0x00;
				result = m_i2c->write(DS3231_I2C_ADDR, (uint8_t*)&m_ds3231, sizeof(m_ds3231));
				break;
			
			case DS3231_RESET_REGISTER_POINTER:
				result = m_i2c->write(DS3231_I2C_ADDR, (uint8_t*)&tmp, sizeof(tmp));
				break;
			
			default: break;
		}
			
		if(result != 0)
		{
			if(m_state != DS3231_RESET_REGISTER_POINTER)
			{
				m_state = DS3231_RESET_REGISTER_POINTER;
			}
			else
			{
				m_state = DS3231_READ_REGISTERS;
			}
			
			m_timer = DS3231_READ_TIME;
		}
	}
}

void DS3231 :: set(Time* time)
{
	m_ds3231.SECR = bin2bcd(time->seconds);
	m_ds3231.MINR = bin2bcd(time->minutes);
	m_ds3231.HOUR = bin2bcd(time->hours);
	
	m_state = DS3231_WRITE_REGISTERS;
}

void DS3231 :: set(Date* date)
{
	m_ds3231.DATR = bin2bcd(date->day);
	m_ds3231.MONR = bin2bcd(date->month);
	m_ds3231.YEAR = bin2bcd(date->year);
	
	m_state = DS3231_WRITE_REGISTERS;
}

void DS3231 :: get(Time *time)
{
	time->seconds = bcd2bin(m_ds3231.SECR & 0x7F);
	time->minutes = bcd2bin(m_ds3231.MINR & 0x7F);
	time->hours = bcd2bin(m_ds3231.HOUR & 0x3F);
}

void DS3231 :: get(Date *date)
{
	date->day = bcd2bin(m_ds3231.DATR & 0x3F);
	date->month = bcd2bin(m_ds3231.MONR & 0x1F);
	date->year = bcd2bin(m_ds3231.YEAR);
}

uint8_t DS3231 :: temperature(void)
{
	return m_ds3231.HTEMP;
}

//float DS3231 :: temperature(void)
//{
//	uint16_t tmp = 0;
//	
//	tmp = (m_ds3231.HTEMP << 8) + m_ds3231.LTEMP;
//	
//	// Convert fixed point to float (Qm.n with m = 7 and n = 8)
//	// f = fp / 2^n
//	return ((float)tmp / 256);
//}

void DS3231 :: timer(void)
{
	if(m_timer) m_timer--;
}

