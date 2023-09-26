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
 * st25dvxxkc.h
 *
 *  Created on: Sep 23, 2023
 *      Author: fil
 */

#ifndef BSP_COMPONENTS_ST25DVXXKC_DRIVER_ST25DVXXKC_H_
#define BSP_COMPONENTS_ST25DVXXKC_DRIVER_ST25DVXXKC_H_

#define ST25DVXXKC_GPO1_REG                      0x0000
#define ST25DVXXKC_GPO2_REG                      0x0001
#define ST25DVXXKC_EH_MODE_REG                   0x0002
#define ST25DVXXKC_RF_MNGT_REG                   0x0003
#define ST25DVXXKC_RFA1SS_REG                    0x0004
#define ST25DVXXKC_ENDA1_REG                     0x0005
#define ST25DVXXKC_RFA2SS_REG                    0x0006
#define ST25DVXXKC_ENDA2_REG                     0x0007
#define ST25DVXXKC_RFA3SS_REG                    0x0008
#define ST25DVXXKC_ENDA3_REG                     0x0009
#define ST25DVXXKC_RFA4SS_REG                    0x000A
#define ST25DVXXKC_I2CSS_REG                     0x000B
#define ST25DVXXKC_LOCKCCFILE_REG                0x000C
#define ST25DVXXKC_FTM_REG                       0x000D
#define ST25DVXXKC_I2CCFG_REG                    0x000E
#define ST25DVXXKC_LOCKCFG_REG                   0x000F
#define ST25DVXXKC_LOCKDSFID_REG                 0x0010
#define ST25DVXXKC_LOCKAFI_REG                   0x0011
#define ST25DVXXKC_DSFID_REG                     0x0012
#define ST25DVXXKC_AFI_REG                       0x0013
#define ST25DVXXKC_MEM_SIZE_LSB_REG              0x0014
#define ST25DVXXKC_MEM_SIZE_MSB_REG              0x0015
#define ST25DVXXKC_BLK_SIZE_REG                  0x0016
#define ST25DVXXKC_ICREF_REG                     0x0017
#define ST25DVXXKC_UID_REG                       0x0018
#define ST25DVXXKC_ICREV_REG                     0x0020
#define ST25DVXXKC_I2CPASSWD_REG                 0x0900

/* Dynamic Registers i2c address */
#define ST25DVXXKC_GPO_DYN_REG                   0x2000
#define ST25DVXXKC_EH_CTRL_DYN_REG               0x2002
#define ST25DVXXKC_RF_MNGT_DYN_REG               0x2003
#define ST25DVXXKC_I2C_SSO_DYN_REG               0x2004
#define ST25DVXXKC_ITSTS_DYN_REG                 0x2005
#define ST25DVXXKC_MB_CTRL_DYN_REG               0x2006
#define ST25DVXXKC_MBLEN_DYN_REG                 0x2007
#define ST25DVXXKC_MAILBOX_RAM_REG               0x2008

#define	MB_EN									0x01
#define	HOST_PUT_MSG							0x02
#define	RF_PUT_MSG								0x02
#define	I2C_SS_OPEN								0x01

#define	DEVICE_SELECTOR_USERMEM					0x04
#define	DEVICE_SELECTOR_SYSMEM					0x0C
#define	DEVICE_SELECTOR_RFSWITCHON				0x00
#define	DEVICE_SELECTOR_RFSWITCHOFF				0x08
#define	PASSWORD_LENGTH							17

extern	uint8_t ST25DV_GetWhoAmI(uint8_t *who_am_i);
extern	uint8_t ST25DV_ReadMBMode(uint8_t *mbmode);
extern	uint8_t ST25DV_GetMB_Ctrl_Dyn(uint8_t *mb_dyn);
extern	uint8_t ST25DV_SetMB_Ctrl_Dyn(uint8_t mb_dyn);
extern	uint8_t ST25DV_SetMB_en_Ctrl_Dyn(void);
extern	uint8_t ST25DV_ReSetMB_en_Ctrl_Dyn(void);
extern	uint8_t ST25DV_WriteMailboxData(uint8_t * data,  uint16_t len);
extern	uint8_t ST25DV_ReadMailboxDataLen(uint16_t *len);
extern	uint8_t ST25DV_ReadMailboxData(uint8_t *mb_data,uint16_t len);
extern	uint8_t ST25DV_I2C_SS_Open(uint8_t *passwd);
extern	uint8_t ST25DV_I2C_SS_Close(uint8_t *passwd);
extern	uint8_t ST25DV_GetI2CSS_Dyn(uint8_t *i2csso_dyn);
extern	uint8_t ST25DV_I2C_SS_Unlock(uint8_t *passwd);
extern	uint8_t ST25DV_I2C_SS_Lock(void);

#endif /* BSP_COMPONENTS_ST25DVXXKC_DRIVER_ST25DVXXKC_H_ */
