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
 * Project : Rollon_A_563 
*/
/*
 * st25r3916b.c
 *
 *  Created on: Sep 25, 2023
 *      Author: fil
 */

#include "main.h"
#include "st25r3916b.h"

extern	SPI_HandleTypeDef hspi1;
#define	ST25R3916B_SPI	hspi1
#define BUS_SPI1_TIMEOUT        2000U /* baud rate of SPI1 = 5 Mbps*/
uint8_t irq_done;

static void	select_st25r3916b(void)
{
	HAL_GPIO_WritePin(ST25R391X_SS_GPIO_Port, ST25R391X_SS_Pin, GPIO_PIN_RESET);
}

static void	de_select_st25r3916b(void)
{
	HAL_GPIO_WritePin(ST25R391X_SS_GPIO_Port, ST25R391X_SS_Pin, GPIO_PIN_SET);
}

static uint32_t	read_st25r3916b_reg(uint8_t reg_addr, uint8_t *data, uint16_t len)
{
uint32_t ret_val;
	select_st25r3916b();
	ret_val = HAL_SPI_Transmit(&ST25R3916B_SPI, &reg_addr, 1, BUS_SPI1_TIMEOUT);
	ret_val = HAL_SPI_Receive(&ST25R3916B_SPI, (uint8_t *)data, len, BUS_SPI1_TIMEOUT);
	de_select_st25r3916b();
	return ret_val;
}

static uint32_t	write_st25r3916b_reg(uint8_t reg_addr, uint8_t *data, uint16_t len)
{
uint32_t ret_val;
	select_st25r3916b();
	ret_val = HAL_SPI_Transmit(&ST25R3916B_SPI, &reg_addr, 1, BUS_SPI1_TIMEOUT);
	ret_val = HAL_SPI_Transmit(&ST25R3916B_SPI, data, len, BUS_SPI1_TIMEOUT);
	de_select_st25r3916b();
	return ret_val;
}

uint32_t	ST25R3916B_send_command(uint8_t command)
{
uint32_t ret_val;
uint8_t cmd = command | ST25R3916_CMD_MODE;
	select_st25r3916b();
	ret_val =  HAL_SPI_Transmit(&ST25R3916B_SPI, &cmd, 1, BUS_SPI1_TIMEOUT);
	de_select_st25r3916b();
	return ret_val;
}


uint32_t	ST25R3916B_send_command_no_deselect_ss(uint8_t command)
{
uint32_t ret_val;
uint8_t cmd = command | ST25R3916_CMD_MODE;
	select_st25r3916b();
	ret_val =  HAL_SPI_Transmit(&ST25R3916B_SPI, &cmd, 1, BUS_SPI1_TIMEOUT);
	return ret_val;
}

uint32_t	ST25R3916B_write_registers(uint8_t reg, uint8_t* data, uint8_t len)
{
uint32_t ret_val;
uint16_t r3916b_register = (uint16_t )reg;
	if( (reg & ST25R3916_SPACE_B) != 0U )
	{
		ST25R3916B_send_command_no_deselect_ss(ST25R3916_CMD_SPACE_B_ACCESS);
	}
	r3916b_register = (uint16_t )(reg & ~ST25R3916_SPACE_B);
	ret_val = write_st25r3916b_reg(r3916b_register,data,1);
	return ret_val;
}

uint32_t	ST25R3916B_read_registers(uint8_t reg, uint8_t* data, uint8_t len)
{
uint32_t ret_val;
uint16_t r3916b_register = (uint16_t )reg;
	if( (reg & ST25R3916_SPACE_B) != 0U )
	{
		ST25R3916B_send_command_no_deselect_ss(ST25R3916_CMD_SPACE_B_ACCESS);
	}
	r3916b_register = (uint16_t )(reg & ~ST25R3916_SPACE_B)| ST25R3916_READ_MODE;
	ret_val = read_st25r3916b_reg(r3916b_register,data,1);
	return ret_val;
}

uint32_t	ST25R3916B_whoami(uint8_t* who_am_i)
{
	return ST25R3916B_read_registers(ST25R3916_REG_IC_IDENTITY,who_am_i,1);
}

uint32_t	ST25R3916B_oscillator_on(void)
{
uint8_t rreg,wreg,timeout=0;

	ST25R3916B_read_registers(ST25R3916_REG_OP_CONTROL,&rreg,1);
	wreg = (rreg & ST25R3916_REG_OP_CONTROL_en);
    /* Clear any eventual previous oscillator IRQ */
	ST25R3916B_write_registers(ST25R3916_REG_IRQ_MASK_MAIN,&wreg ,1);

    /* Enable oscillator frequency stable interrupt */
	irq_done = 0;
	wreg = ST25R3916_IRQ_MASK_OSC;
	ST25R3916B_write_registers(ST25R3916_REG_OP_CONTROL,&wreg ,1);

    /* Enable oscillator and regulator output */
	wreg = ST25R3916_REG_OP_CONTROL_en;
	ST25R3916B_write_registers(ST25R3916_REG_OP_CONTROL,&wreg ,1);
    /* Wait for the oscillator interrupt */
	while(irq_done == 0)
	{
		HAL_Delay(1);
		timeout++;
		if ( timeout > 10 )
			return 1;
	}
	ST25R3916B_read_registers(ST25R3916_REG_AUX_DISPLAY,&rreg,1);
	return 0;
}


uint8_t	who_am_i[32];
uint8_t	calibration[32];


uint32_t	ST25R3916B_send_command_get_result(uint8_t command, uint8_t* data, uint8_t len)
{
uint32_t ret_val;
uint8_t cmd = command | ST25R3916_CMD_MODE;
uint8_t rreg,wreg,wreg_multi[8];

/*
 *     // Clear and enable Direct Command interrupt
    st25r3916GetInterrupt( ST25R3916_IRQ_MASK_DCT );
    st25r3916EnableInterrupts( ST25R3916_IRQ_MASK_DCT );

    st25r3916ExecuteCommand( cmd );

    st25r3916WaitForInterruptsTimed( ST25R3916_IRQ_MASK_DCT, tOut );
    st25r3916DisableInterrupts( ST25R3916_IRQ_MASK_DCT );

    / After execution read out the result if the pointer is not NULL
    if( result != NULL )
    {
        st25r3916ReadRegister( resReg, result);
    }

    return ERR_NONE;

 */
	select_st25r3916b();
	irq_done = 0;
	// enable interrupts
	wreg_multi[0] = ST25R3916_REG_IRQ_MASK_TIMER_NFC;
	wreg_multi[1] = ST25R3916_REG_IRQ_MASK_MAIN_value;
	ret_val = HAL_SPI_Transmit(&ST25R3916B_SPI, wreg_multi, 2, BUS_SPI1_TIMEOUT);
	// execute command
	ret_val =  HAL_SPI_Transmit(&ST25R3916B_SPI, &cmd, 1, BUS_SPI1_TIMEOUT);
	// wait for interrupt
	while(irq_done == 0);
	// disable interrupts
	ret_val = HAL_SPI_Receive(&ST25R3916B_SPI,&rreg, 1, BUS_SPI1_TIMEOUT);
	wreg = (rreg & ~ST25R3916_IRQ_MASK_DCT);
	ret_val = HAL_SPI_Transmit(&ST25R3916B_SPI, &wreg, 1, BUS_SPI1_TIMEOUT);
	de_select_st25r3916b();
	return ret_val;
}

uint8_t	cal_data[128];
uint32_t ST25R3916B_Init( void )
{
uint8_t	wreg = ST25R3916_REG_IO_CONF2_io_drv_lvl | ST25R3916_REG_IO_CONF2_miso_pd1 | ST25R3916_REG_IO_CONF2_miso_pd2;
	ST25R3916B_send_command( ST25R3916_CMD_SET_DEFAULT );
	ST25R3916B_write_registers(ST25R3916_REG_IO_CONF2,&wreg ,1);
	ST25R3916B_whoami(who_am_i);
	ST25R3916B_oscillator_on();
	ST25R3916B_send_command_get_result(ST25R3916_CMD_RC_CAL,cal_data,8);
	return 0;
}


