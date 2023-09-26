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
 * Project : A_os_U575_devel 
*/
/*
 * nfc_config.h
 *
 *  Created on: Sep 25, 2023
 *      Author: fil
 */

#ifndef DRIVERS_COMMON_COMPONENTS_NFC_NFC_CONFIG_H_
#define DRIVERS_COMMON_COMPONENTS_NFC_NFC_CONFIG_H_

extern	I2C_HandleTypeDef 	hi2c1;
#define	NFC_I2C_BUS			hi2c1
#define	NFC_I2C_TIMEOUT		1000

#define	ST25DV_ADDR					0xa6

#define	ST25_I2C_BUS		(NFC_I2C_BUS)

#ifdef	STM32U575xx
#include "stm32u5xx_hal_i2c.h"
#endif

/* st25dvxxkc_driver */
extern	uint8_t ST25DV_I2C_SS_Lock(void);
extern	uint8_t ST25DV_I2C_SS_Unlock(uint8_t *passwd);
extern	uint8_t ST25DV_ReadMailboxData(uint8_t *mb_data,uint16_t len);
extern	uint8_t ST25DV_ReadMailboxDataLen(uint16_t *len);
extern	uint8_t ST25DV_WriteMailboxData(uint8_t * data,  uint16_t len);
extern	uint8_t ST25DV_ReSetMB_en_Ctrl_Dyn(void);
extern	uint8_t ST25DV_SetMB_en_Ctrl_Dyn(void);
extern	uint8_t ST25DV_SetMB_Ctrl_Dyn(uint8_t mb_dyn);
extern	uint8_t ST25DV_GetI2CSS_Dyn(uint8_t *i2csso_dyn);
extern	uint8_t ST25DV_GetMB_Ctrl_Dyn(uint8_t *mb_dyn);
extern	uint8_t ST25DV_ReadMBMode(uint8_t *mbmode);
extern	uint8_t ST25DV_GetWhoAmI(uint8_t *who_am_i);







#endif /* DRIVERS_COMMON_COMPONENTS_NFC_NFC_CONFIG_H_ */
