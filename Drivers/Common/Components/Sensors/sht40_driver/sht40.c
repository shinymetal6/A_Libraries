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
 * sht40.c
 *
 *  Created on: Sep 22, 2023
 *      Author: fil
 */

#include "main.h"
#include "sht40.h"
#include "../sensors_config.h"

int32_t  SHT40_StartAcquisition(void)
{
uint8_t		cmd = 0xfd;
	return HAL_I2C_Master_Transmit(&SHT40_I2C_BUS, SHT40_ADDR, &cmd,1, SHT40_TIMEOUT);
}

int32_t  SHT40_ReadData(uint8_t *pData)
{
	return HAL_I2C_Master_Receive(&SHT40_I2C_BUS, SHT40_ADDR, pData, 6, SHT40_TIMEOUT);
}


