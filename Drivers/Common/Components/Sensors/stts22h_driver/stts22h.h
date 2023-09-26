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
 * stts22h.h
 *
 *  Created on: Sep 22, 2023
 *      Author: fil
 */

#ifndef BSP_COMPONENTS_STTS22H_DRIVER_STTS22H_H_
#define BSP_COMPONENTS_STTS22H_DRIVER_STTS22H_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include <math.h>


/* who am i */
#define STTS22H_ID				0xA0U
/* registers */
#define STTS22H_WHOAMI			0x01U
#define STTS22H_TEMP_H_LIMIT	0x02U
#define STTS22H_TEMP_L_LIMIT	0x03U
#define STTS22H_CTRL			0x04U
#define STTS22H_STATUS			0x05U
#define STTS22H_TEMP_L_OUT		0x06U
#define STTS22H_TEMP_H_OUT		0x07U
#define STTS22H_SOFTWARE_RESET	0x0CU

#define	STTS22H_ONE_SHOT_REG_CTRL	0x01


extern	uint32_t STTS22H_Init(void);
extern	uint8_t STTS22H_GetWhoAmI(void);
extern	int32_t STTS22H_Start_Acquisition(void);
extern	uint8_t STTS22H_Read_T_Data(uint8_t *temperature_ptr);

#ifdef __cplusplus
}
#endif

#endif /* BSP_COMPONENTS_STTS22H_DRIVER_STTS22H_H_ */
