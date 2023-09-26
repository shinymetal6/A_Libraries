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
 * st25dvxxkc.c
 *
 *  Created on: Sep 23, 2023
 *      Author: fil
 */

#include "main.h"
#include "st25dvxxkc.h"
#include "../nfc_config.h"
#include <string.h>

static uint8_t	read_st25dv_reg(uint16_t address, uint8_t device_selector, uint8_t *data, uint16_t len)
{
	return HAL_I2C_Mem_Read(&ST25_I2C_BUS, ST25DV_ADDR|device_selector, address, I2C_MEMADD_SIZE_16BIT, data, len, NFC_I2C_TIMEOUT);
}

static uint8_t	write_st25dv_reg(uint16_t address, uint8_t device_selector,uint8_t *data, uint16_t len)
{
	return HAL_I2C_Mem_Write(&ST25_I2C_BUS, ST25DV_ADDR|device_selector, address, I2C_MEMADD_SIZE_16BIT, data, len, NFC_I2C_TIMEOUT);
}

uint8_t ST25DV_GetWhoAmI(uint8_t *who_am_i)
{
	return read_st25dv_reg(ST25DVXXKC_ICREF_REG,DEVICE_SELECTOR_SYSMEM,who_am_i,1);
}

uint8_t ST25DV_ReadMBMode(uint8_t *mbmode)
{
	return read_st25dv_reg(ST25DVXXKC_AFI_REG,DEVICE_SELECTOR_SYSMEM,mbmode,1);
}

uint8_t ST25DV_GetMB_Ctrl_Dyn(uint8_t *mb_dyn)
{
	return read_st25dv_reg(ST25DVXXKC_MB_CTRL_DYN_REG,DEVICE_SELECTOR_USERMEM,mb_dyn,1);
}
uint8_t ST25DV_GetI2CSS_Dyn(uint8_t *i2csso_dyn)
{
	return read_st25dv_reg(ST25DVXXKC_I2C_SSO_DYN_REG,DEVICE_SELECTOR_USERMEM,i2csso_dyn,1);
}

uint8_t ST25DV_SetMB_Ctrl_Dyn(uint8_t mb_dyn)
{
	return write_st25dv_reg(ST25DVXXKC_MB_CTRL_DYN_REG,DEVICE_SELECTOR_USERMEM,(uint8_t *)&mb_dyn,1);
}

uint8_t ST25DV_SetMB_en_Ctrl_Dyn(void)
{
uint8_t	mb_dyn;
	read_st25dv_reg(ST25DVXXKC_MB_CTRL_DYN_REG,DEVICE_SELECTOR_USERMEM,&mb_dyn,1);
	mb_dyn |= MB_EN;
	return write_st25dv_reg(ST25DVXXKC_MB_CTRL_DYN_REG,DEVICE_SELECTOR_USERMEM,&mb_dyn,1);
}

uint8_t ST25DV_ReSetMB_en_Ctrl_Dyn(void)
{
uint8_t	mb_dyn;
	read_st25dv_reg(ST25DVXXKC_MB_CTRL_DYN_REG,DEVICE_SELECTOR_USERMEM,&mb_dyn,1);
	mb_dyn &= ~MB_EN;
	return write_st25dv_reg(ST25DVXXKC_MB_CTRL_DYN_REG,DEVICE_SELECTOR_USERMEM,&mb_dyn,1);
}

uint8_t ST25DV_WriteMailboxData(uint8_t * data,  uint16_t len)
{
	return write_st25dv_reg(ST25DVXXKC_MAILBOX_RAM_REG,DEVICE_SELECTOR_USERMEM,data,len);
}

uint8_t ST25DV_ReadMailboxDataLen(uint16_t *len)
{
uint8_t	mb_dyn_len,ret_val;
	ret_val = read_st25dv_reg(ST25DVXXKC_MBLEN_DYN_REG,DEVICE_SELECTOR_USERMEM,&mb_dyn_len,1);
	*len = mb_dyn_len;
	return ret_val;
}

uint8_t ST25DV_ReadMailboxData(uint8_t *mb_data,uint16_t len)
{
	return read_st25dv_reg(ST25DVXXKC_MBLEN_DYN_REG,DEVICE_SELECTOR_USERMEM,mb_data,len);
}

uint8_t local_passwd[17];

uint8_t ST25DV_I2C_SS_Unlock(uint8_t *passwd)
{
uint8_t	rreg;
	ST25DV_GetI2CSS_Dyn(&rreg);
	if (( rreg & I2C_SS_OPEN) == 0 )
	{
		memcpy(local_passwd,passwd,17);
		local_passwd[8] = 0x09;
		write_st25dv_reg(ST25DVXXKC_I2CPASSWD_REG,DEVICE_SELECTOR_SYSMEM,local_passwd,PASSWORD_LENGTH);
		ST25DV_GetI2CSS_Dyn(&rreg);
		if (( rreg & I2C_SS_OPEN ) == I2C_SS_OPEN )
			return 0;
		else
			return 1;
	}
	return 0;
}

uint8_t ST25DV_I2C_SS_Lock(void)
{
uint8_t	rreg;
	ST25DV_GetI2CSS_Dyn(&rreg);
	if (( rreg & I2C_SS_OPEN) == I2C_SS_OPEN )
	{
		local_passwd[0] = ~local_passwd[0];
		local_passwd[8] = 0x09;
		write_st25dv_reg(ST25DVXXKC_I2CPASSWD_REG,DEVICE_SELECTOR_SYSMEM,local_passwd,PASSWORD_LENGTH);
		ST25DV_GetI2CSS_Dyn(&rreg);
		if (( rreg & I2C_SS_OPEN ) == 0 )
			return 0;
		else
			return 1;

	}
	return 0;
}







