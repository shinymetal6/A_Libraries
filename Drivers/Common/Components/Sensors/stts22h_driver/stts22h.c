/* 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Project : Rollon_Sensors_L431 
*/
/*
 * stts22h.c
 *
 *  Created on: Sep 22, 2023
 *      Author: fil
 */

#include "main.h"
#include "stts22h.h"
#include "../sensors_config.h"

static uint8_t	read_stts22h_reg(uint8_t address)
{
uint8_t	rreg;
	HAL_I2C_Mem_Read(&STTS22H_I2C_BUS, STTS22_ADDR, (uint16_t )address, I2C_MEMADD_SIZE_8BIT,	&rreg, 1, STTS22H_TIMEOUT);
	return rreg;
}

static uint8_t	write_stts22h_reg(uint8_t address,uint8_t data)
{
	return HAL_I2C_Mem_Write(&STTS22H_I2C_BUS, STTS22_ADDR, (uint16_t )address, I2C_MEMADD_SIZE_8BIT, &data, 1, STTS22H_TIMEOUT);
}

uint8_t STTS22H_GetWhoAmI(void)
{
	read_stts22h_reg(STTS22H_WHOAMI);
	return read_stts22h_reg(STTS22H_WHOAMI);
}

int32_t STTS22H_Start_Acquisition(void)
{
	return write_stts22h_reg(STTS22H_CTRL,STTS22H_ONE_SHOT_REG_CTRL);
}

uint8_t STTS22H_Read_T_Data(uint8_t *temperature_ptr)
{
	return	HAL_I2C_Mem_Read(&STTS22H_I2C_BUS, STTS22_ADDR, (uint16_t )STTS22H_TEMP_L_OUT, I2C_MEMADD_SIZE_8BIT, temperature_ptr, STTS22H_T_LEN, STTS22H_TIMEOUT);
}

uint32_t STTS22H_Init(void)
{
	return (uint32_t )STTS22H_GetWhoAmI();
}
