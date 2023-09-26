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
 * Project : A
*/
/*
 * sensors_config.h
 *
 *  Created on: Sep 25, 2023
 *      Author: fil
 */

#ifndef DRIVERS_COMMON_COMPONENTS_SENSORS_CONFIG_H_
#define DRIVERS_COMMON_COMPONENTS_SENSORS_CONFIG_H_

extern	I2C_HandleTypeDef 	hi2c1;
#define	SENSORS_I2C_TIMEOUT	1000

#define	LIS2DW12_I2C_BUS			hi2c1

#define	LPS22DF_I2C_BUS				hi2c1
#define	LPS22DF_TIMEOUT				(SENSORS_I2C_TIMEOUT)
#define	LPS22DF_P_LEN				3
#define	LPS22DF_T_LEN				2

#define	SHT40_I2C_BUS				hi2c1
#define	SHT40_TIMEOUT				(SENSORS_I2C_TIMEOUT)

#define	STTS22H_I2C_BUS				hi2c1
#define	STTS22H_TIMEOUT				(SENSORS_I2C_TIMEOUT)
#define	STTS22H_T_LEN				2

#define	LPS22DF_ADDR				0xb8
#define	LIS2DW12_ADDR				0x32
#define	STTS22_ADDR					0x7e
#define	SHT40_ADDR					0x88

#ifdef	STM32U575xx
#include "stm32u5xx_hal_i2c.h"
#endif

#endif /* DRIVERS_COMMON_COMPONENTS_SENSORS_CONFIG_H_ */
