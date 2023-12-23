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
 * Project : fy-201023-00 
*/
/*
 * w25q.c
 *
 *  Created on: Dec 23, 2023
 *      Author: fil
 */

#include "main.h"
#include "w25q.h"
#include "../../../../../../A_os/kernel/A.h"
#include "../../../../../../A_os/kernel/system_default.h"

extern	void task_delay(uint32_t tick_count);

static void set_com(QSPI_CommandTypeDef *com , uint8_t instruction, uint32_t address, uint32_t nbdata,uint32_t instruction_mode, uint32_t address_mode, uint32_t address_size)
{
	com->InstructionMode = instruction_mode; 	// Instruction
	com->Instruction = instruction;	 				// Command
	com->AddressMode = address_mode;
	com->AddressSize = address_size;
	com->Address = address;
	com->AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	com->AlternateBytes = QSPI_ALTERNATE_BYTES_NONE;
	com->AlternateBytesSize = QSPI_ALTERNATE_BYTES_NONE;
	com->DummyCycles = 0;
	com->DataMode = QSPI_DATA_1_LINE;
	com->NbData = nbdata;
	com->DdrMode = QSPI_DDR_MODE_DISABLE;
	com->DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	com->SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
}


uint8_t w25q_ReadStatusReg(uint8_t *reg_data, uint8_t reg_num)
{
QSPI_CommandTypeDef com;
uint32_t	instruction;

	if (reg_num == 1)
		instruction = W25Q_READ_SR1;
	else if (reg_num == 2)
		instruction = W25Q_READ_SR2;
	else if (reg_num == 3)
		instruction = W25Q_READ_SR3;
	else
		return W25Q_PARAM_ERR;
	set_com(&com,W25Q_READ_SR1,0,1,instruction,QSPI_ADDRESS_NONE,QSPI_ADDRESS_NONE);

	if (HAL_QSPI_Command(&hqspi, &com, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return W25Q_SPI_ERR;
	if (HAL_QSPI_Receive(&hqspi, reg_data, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return W25Q_SPI_ERR;
	return W25Q_OK;
}

static uint8_t w25q_WriteEnable(uint8_t enable)
{
QSPI_CommandTypeDef com;
uint32_t	instruction;

	instruction = enable ? W25Q_WRITE_ENABLE : W25Q_WRITE_DISABLE;
	set_com(&com,instruction,0,0,QSPI_INSTRUCTION_1_LINE,QSPI_ADDRESS_NONE,QSPI_ADDRESS_NONE);

	if (HAL_QSPI_Command(&hqspi, &com, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return W25Q_SPI_ERR;
	task_delay(1); // Give a little time to sleep

	Asys.qspi_status |= ASYS_QSPI_WEL;

	return W25Q_OK;
}

static uint8_t w25q_IsBusy(void)
{
uint8_t sr = 0;

	if (w25q_ReadStatusReg(&sr, 1) != W25Q_OK)
		return W25Q_CHIP_ERR;

	Asys.qspi_status &= ~ASYS_QSPI_BUSY;
	if ( sr & 0x01 )
		Asys.qspi_status |= ASYS_QSPI_BUSY;
	return sr & 0x01;
}

static uint8_t w25q_WriteStatusReg(uint8_t reg_data, uint8_t reg_num)
{
QSPI_CommandTypeDef com;
uint32_t	instruction;

	while (w25q_IsBusy() == W25Q_BUSY)
		task_delay(1);

	if (w25q_WriteEnable(1) != W25Q_OK)
		return W25Q_CHIP_ERR;



	if (reg_num == 1)
		instruction = W25Q_WRITE_SR1;
	else if (reg_num == 2)
		instruction = W25Q_WRITE_SR2;
	else if (reg_num == 3)
		instruction = W25Q_WRITE_SR3;
	else
		return W25Q_PARAM_ERR;

	set_com(&com,instruction,0,1,QSPI_INSTRUCTION_1_LINE,QSPI_ADDRESS_NONE,QSPI_ADDRESS_NONE);

	if (HAL_QSPI_Command(&hqspi, &com, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)
			!= HAL_OK) {
		return W25Q_SPI_ERR;
	}
	if (HAL_QSPI_Transmit(&hqspi, &reg_data, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)
			!= HAL_OK) {
		return W25Q_SPI_ERR;
	}
	return W25Q_OK;
}

uint8_t w25q_ReadStatusStruct(void)
{
uint8_t status_reg = 0;

	Asys.qspi_status = ASYS_QSPI_FOUND;

	// first portion
	if (w25q_ReadStatusReg(&status_reg, 1) != W25Q_OK)
		return 1;
	if ( status_reg & 0x01)
		Asys.qspi_status |= ASYS_QSPI_BUSY;
	if ( status_reg & 0x02)
		Asys.qspi_status |= ASYS_QSPI_WEL;

	// second portion
	if (w25q_ReadStatusReg(&status_reg, 2) != W25Q_OK)
		return 1;
	if ( status_reg & 0x02)
		Asys.qspi_status |= ASYS_QSPI_QE;
	if ( status_reg & 0x80)
		Asys.qspi_status |= ASYS_QSPI_SUS;

	// third portion
	if (w25q_ReadStatusReg(&status_reg, 3) != W25Q_OK)
		return 1;
	if ( status_reg & 0x01)
		Asys.qspi_status |= ASYS_QSPI_ADS;
	if ( status_reg & 0x02)
		Asys.qspi_status |= ASYS_QSPI_ADP;
	return 0;
}

uint8_t w25q_ReadID(uint8_t *buf)
{
QSPI_CommandTypeDef com;
	set_com(&com,W25Q_DEVID,0,1,QSPI_INSTRUCTION_1_LINE,QSPI_ADDRESS_1_LINE,QSPI_ADDRESS_24_BITS);
	if (HAL_QSPI_Command(&HQSPI1, &com, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)	!= HAL_OK)
		return W25Q_SPI_ERR;
	if (HAL_QSPI_Receive(&HQSPI1, buf, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return W25Q_SPI_ERR;
	return W25Q_OK;
}

uint8_t w25q_Init(void)
{
uint8_t id = 0 , buf_reg = 0;

	// read id
	if (w25q_ReadID(&id) != W25Q_OK)
		return 0;

	// read chip's state to private lib's struct
	if (w25q_ReadStatusStruct() != W25Q_OK)
		return 0;

	if (!( Asys.qspi_status & ASYS_QSPI_QE))
	{
		if (w25q_ReadStatusReg(&buf_reg, 2) != W25Q_OK)
			return 0;
		buf_reg |= 0b10;
		if (w25q_WriteStatusReg(buf_reg, 2) != W25Q_OK)
			return 0;
	}

	// make another read
	if (w25q_ReadStatusStruct() != W25Q_OK)
		return 0;
	// return communication status
	return id;
}
