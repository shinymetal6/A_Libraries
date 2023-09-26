/*
 * lis2dw12.c
 *
 *  Created on: Jul 31, 2023
 *      Author: fil
 */

#include "main.h"
#include "lis2dw12.h"
#include "../sensors_config.h"

#include <string.h>

static uint8_t	read_lis_reg(uint8_t address)
{
uint8_t	rreg;
	HAL_I2C_Mem_Read(&LIS2DW12_I2C_BUS, LIS2DW12_ADDR, (uint16_t )address, I2C_MEMADD_SIZE_8BIT,	&rreg, 1, 1000);
	return rreg;
}

static uint8_t	write_lis_reg(uint8_t address,uint8_t data)
{
	return HAL_I2C_Mem_Write(&LIS2DW12_I2C_BUS, LIS2DW12_ADDR, (uint16_t )address, I2C_MEMADD_SIZE_8BIT, &data, 1, 1000);
}

uint8_t LIS2DW12_GetWhoAmI(void)
{
	read_lis_reg(LIS2DW12_WHO_AM_I);
	return read_lis_reg(LIS2DW12_WHO_AM_I);
}

uint8_t LIS2DW12_ReadAccRegs(uint8_t *axis_ptr)
{
	return HAL_I2C_Mem_Write(&LIS2DW12_I2C_BUS, LIS2DW12_ADDR, (uint16_t )LIS2DW12_OUT_X_L, I2C_MEMADD_SIZE_8BIT, axis_ptr, 6, 1000);
}

uint8_t LIS2DW12_GetStatusReg(void)
{
	return read_lis_reg(LIS2DW12_STATUS);
}

uint8_t LIS2DW12_SetCTRL_2_Reg(void)
{
	write_lis_reg(LIS2DW12_CTRL2,0x40);
	HAL_Delay(1);
	write_lis_reg(LIS2DW12_CTRL2,0x80);
	HAL_Delay(1);
	return write_lis_reg(LIS2DW12_CTRL2,0x14);
}

uint8_t LIS2DW12_GetWakeSource(void)
{
	return read_lis_reg(LIS2DW12_WAKE_UP_SRC);
}

uint8_t LIS2DW12_GetFifoSamples(void)
{
	return read_lis_reg(LIS2DW12_FIFO_SAMPLES);
}

void LIS2DW12_ConfigureFIFO(uint8_t FIFOMode, uint8_t FIFOThreshold)
{
	write_lis_reg(LIS2DW12_FIFO_CTRL, FIFOMode << 5 | (FIFOThreshold-1) );
}

uint8_t LIS2DW12_Reset(void)
{
uint8_t temp;
	temp = read_lis_reg(LIS2DW12_CTRL2);
	write_lis_reg(LIS2DW12_CTRL2, temp | 0x40); // software reset the LIS2DW12
	return read_lis_reg(LIS2DW12_STATUS);
}

//https://github.com/kriswiner/LIS2DW12/blob/main/LIS2DW12_Tap_OrientationDetect_Ladybug/LIS2DW12.cpp#L36

uint8_t	lpMode		= LIS2DW12_LP_MODE_2;      	// choices are low power modes 1, 2, 3, or 4
uint8_t	mode		= LIS2DW12_MODE_HIGH_PERF; 	// choices are low power, high performance, and one shot modes
uint8_t	odr			= LIS2DW12_ODR_400_200Hz;  	// choices are 12.5, 25, 50, 100, 200, 400, 800, 1600 Hz, 1.6 Hz in lpMode, and POWERDOWN
//uint8_t	fs			= LIS2DW12_FS_2G;          	// choices are 2, 4, 8, or 16 g
uint8_t	bw			= LIS2DW12_BW_FILT_ODR10;	// choices are ODR divided by 2, 4, 10, or 20
uint8_t	lowNoise	= 0x04;                    	// low noise or lowest power


uint8_t LIS2DW12_GetTempReg(void)
{
	return read_lis_reg(LIS2DW12_OUT_T);
}
/*
uint8_t LIS2DW12_SetCompensation(uint8_t fs,float *aRes,uint8_t *lis_full_scale_acc)
{
uint8_t	i;
int32_t sum[3] = {0, 0, 0};

	*aRes = 0.000244f * (1 << fs);
	*lis_full_scale_acc = fs;
	write_lis_reg( LIS2DW12_CTRL2 , 0x08 | 0x04);
	write_lis_reg( LIS2DW12_CTRL3 , 0x00);
	write_lis_reg( LIS2DW12_CTRL4_INT1_PAD_CTRL , 0x00);
	write_lis_reg( LIS2DW12_CTRL5_INT2_PAD_CTRL , 0x00);
	write_lis_reg( LIS2DW12_CTRL6 , bw << 6 | fs << 4 | lowNoise );
	write_lis_reg( LIS2DW12_CTRL1 , odr << 4 | mode << 2 | lpMode );
	HAL_Delay(100);
	while((LIS2DW12_GetStatusReg() & 0x01) != 0x01)
		HAL_Delay(10);
	LIS2DW12_ReadAccRegs(System.axis_regs[0]);	// discard data;
	for(i=0;i<128;i++)
	{
		while((LIS2DW12_GetStatusReg() & 0x01) != 0x01)
			HAL_Delay(1);
		LIS2DW12_ReadAccRegs(System.axis_regs[0]);
		sum[0] += (int32_t)(System.axis_regs[0][0] + (System.axis_regs[0][1] << 8));
		sum[1] += (int32_t)(System.axis_regs[0][2] + (System.axis_regs[0][3] << 8));
		sum[2] += (int32_t)(System.axis_regs[0][4] + (System.axis_regs[0][5] << 8));
	}
	System.lis_offset[0] = (float )sum[0] / 128.0f;
	System.lis_offset[1] = (float )sum[1] / 128.0f;
	System.lis_offset[2] = (float )sum[2] / 128.0f;
	System.lis_offset[0] *= System.aRes;
	System.lis_offset[1] *= System.aRes;
	System.lis_offset[2] *= System.aRes;
	if(System.lis_offset[2] > +0.5f) System.lis_offset[2] = System.lis_offset[2] - 1.0f;
	if(System.lis_offset[2] < -0.5f) System.lis_offset[2] = System.lis_offset[2] + 1.0f;

	return 0;
}
*/
uint8_t LIS2DW12_Init(uint8_t fifo_locations,uint8_t *id,uint8_t *status,uint8_t *ie,uint8_t lis_full_scale_acc)
{
	lpMode = LIS2DW12_LP_MODE_2;      // choices are low power modes 1, 2, 3, or 4
	mode   = LIS2DW12_MODE_LOW_POWER; // choices are low power, high performance, and one shot modes
	odr    = LIS2DW12_ODR_25Hz;       // choices are 12.5, 25, 50, 100, 200, 400, 800, 1600 Hz, 1.6 Hz in lpMode, and POWERDOWN
	bw     = LIS2DW12_BW_FILT_ODR4;   // choices are ODR divided by 2, 4, 10, or 20
	lowNoise	= 0;                  // low noise or lowest power

	write_lis_reg( LIS2DW12_CTRL1 , odr << 4 | mode << 2 | lpMode );
	write_lis_reg( LIS2DW12_CTRL6, bw << 6 | lis_full_scale_acc << 4);
	write_lis_reg( LIS2DW12_CTRL2 , 0x08 | 0x04);
	write_lis_reg( LIS2DW12_CTRL3 , 0x10);
	write_lis_reg( LIS2DW12_CTRL4_INT1_PAD_CTRL , LIS2DW12_INT1_WU);
	write_lis_reg( LIS2DW12_CTRL5_INT2_PAD_CTRL , 0x40);
	write_lis_reg( LIS2DW12_WAKE_UP_THS ,  0x40 | 0x02);
	write_lis_reg( LIS2DW12_WAKE_UP_DUR ,  0x40 | 0x01);
	write_lis_reg( LIS2DW12_CTRL_REG7, LIS2DW12_DRDY_PULSED | LIS2DW12_INTERRUPTS_ENABLE | LIS2DW12_INT2_ON_INT1);

	LIS2DW12_ConfigureFIFO(LISDW_FIFOMODE_CONT_TO_FIFO,fifo_locations);

	*ie = read_lis_reg(LIS2DW12_CTRL4_INT1_PAD_CTRL);
	*status = LIS2DW12_GetStatusReg();
	return 0;
}




