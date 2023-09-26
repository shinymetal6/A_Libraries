/*
 * lis2dw12.h
 *
 *  Created on: Jul 31, 2023
 *      Author: fil
 */

#ifndef LIS2DW12_H_
#define LIS2DW12_H_

#define	MAG_LEN				6
#define	LIS2DW12_FIFO_DEPTH	32
#define	LIS2_READ_BIT		0x80
#define	LIS2DW12_ID			0x44

#define LIS2DW12_OUT_T_L                  0x0D
#define LIS2DW12_OUT_T_H                  0x0E
#define LIS2DW12_WHO_AM_I                 0x0F  // should be 0x44
#define LIS2DW12_CTRL1                    0x20
#define LIS2DW12_CTRL2                    0x21
#define LIS2DW12_CTRL3                    0x22
#define LIS2DW12_CTRL4_INT1_PAD_CTRL      0x23
#define LIS2DW12_CTRL5_INT2_PAD_CTRL      0x24
#define LIS2DW12_CTRL6                    0x25
#define LIS2DW12_OUT_T                    0x26
#define LIS2DW12_STATUS                   0x27
#define LIS2DW12_OUT_X_L                  0x28
#define LIS2DW12_OUT_X_H                  0x29
#define LIS2DW12_OUT_Y_L                  0x2A
#define LIS2DW12_OUT_Y_H                  0x2B
#define LIS2DW12_OUT_Z_L                  0x2C
#define LIS2DW12_OUT_Z_H                  0x2D
#define LIS2DW12_FIFO_CTRL                0x2E
#define LIS2DW12_FIFO_SAMPLES             0x2F
#define LIS2DW12_TAP_THS_X                0x30
#define LIS2DW12_TAP_THS_Y                0x31
#define LIS2DW12_TAP_THS_Z                0x32
#define LIS2DW12_INT_DUR                  0x33
#define LIS2DW12_WAKE_UP_THS              0x34
#define LIS2DW12_WAKE_UP_DUR              0x35
#define LIS2DW12_FREE_FALL                0x36
#define LIS2DW12_STATUS_DUP               0x37
#define LIS2DW12_WAKE_UP_SRC              0x38
#define LIS2DW12_TAP_SRC                  0x39
#define LIS2DW12_SIXD_SRC                 0x3A
#define LIS2DW12_ALL_INT_SRC              0x3B
#define LIS2DW12_X_OFS_USR                0x3C
#define LIS2DW12_Y_OFS_USR                0x3D
#define LIS2DW12_Z_OFS_USR                0x3E
#define LIS2DW12_CTRL_REG7                0x3F

typedef enum {
  LIS2DW12_LP_MODE_1                = 0x00,
  LIS2DW12_LP_MODE_2                = 0x01,
  LIS2DW12_LP_MODE_3                = 0x02,
  LIS2DW12_LP_MODE_4                = 0x03
} LPMODE;


typedef enum  {
  LIS2DW12_MODE_LOW_POWER           = 0x00,
  LIS2DW12_MODE_HIGH_PERF           = 0x01,
  LIS2DW12_MODE_SINGLE_CONV         = 0x02
} MODE;


typedef enum {
  LIS2DW12_ODR_POWER_DOWN           = 0x00,
  LIS2DW12_ODR_12_5_1_6HZ           = 0x01,
  LIS2DW12_ODR_12_5Hz               = 0x02,
  LIS2DW12_ODR_25Hz                 = 0x03,
  LIS2DW12_ODR_50Hz                 = 0x04,
  LIS2DW12_ODR_100Hz                = 0x05,
  LIS2DW12_ODR_200Hz                = 0x06,
  LIS2DW12_ODR_400_200Hz            = 0x07,
  LIS2DW12_ODR_800_200Hz            = 0x08,
  LIS2DW12_ODR_1600_200Hz           = 0x09
} ODR;


typedef enum {
  LIS2DW12_FS_2G                    = 0x00,
  LIS2DW12_FS_4G                    = 0x01,
  LIS2DW12_FS_8G                    = 0x02,
  LIS2DW12_FS_16G                   = 0x03
} FS;


typedef enum  {
  LIS2DW12_BW_FILT_ODR2             = 0x00,
  LIS2DW12_BW_FILT_ODR4             = 0x01,
  LIS2DW12_BW_FILT_ODR10            = 0x02,
  LIS2DW12_BW_FILT_ODR20            = 0x03
} BW_FILT;


typedef enum  {
	LISDW_FIFOMODE_BYPASS                            = 0x00,
	LISDW_FIFOMODE_FIFO                              = 0x01,
	LISDW_FIFOMODE_CONT_TO_FIFO                      = 0x03,
	LISDW_FIFOMODE_BYPASS_TO_CONT                    = 0x04,
	LISDW_FIFOMODE_CONTINUOUS                        = 0x06
} FIFOMODE;
#define	LISDW_FIFO_DEPTH	32

typedef enum  {
	LIS2DW12_LOWNOISE                           = 0x00,
	LIS2DW12_FAST                               = 0x01
} NOISEMODE;

typedef enum  {
	LIS2DW12_SINGLE_DOUBLE_TAP					= 0x80,
	LIS2DW12_SLEEP_ON							= 0x40
} WAKE_THS;

typedef enum  {
	LIS2DW12_INT1_6D							= 0x80,
	LIS2DW12_INT1_SINGLE_TAP					= 0x40,
	LIS2DW12_INT1_WU							= 0x20,
	LIS2DW12_INT1_FF							= 0x10,
	LIS2DW12_INT1_TAP							= 0x08,
	LIS2DW12_INT1_DIFF5							= 0x04,
	LIS2DW12_INT1_FTH							= 0x02,
	LIS2DW12_INT1_DRDY							= 0x01,
} INT1_ENABLES;

typedef enum  {
	LIS2DW12_DRDY_PULSED						= 0x80,
	LIS2DW12_INT2_ON_INT1						= 0x40,
	LIS2DW12_INTERRUPTS_ENABLE					= 0x20,
	LIS2DW12_USR_OFF_ON_OUT						= 0x10,
	LIS2DW12_USR_OFF_ON_WU						= 0x08,
	LIS2DW12_USR_OFF_W							= 0x04,
	LIS2DW12_HP_REF_MODE						= 0x02,
	LIS2DW12_LPASS_ON6D							= 0x01,
} CTRL7_REG;

typedef enum  {
	LIS2DW12_FF_IA								= 0x20,
	LIS2DW12_SLEEP_STATE_IA						= 0x10,
	LIS2DW12_WU_IA								= 0x08,
	LIS2DW12_X_WU								= 0x04,
	LIS2DW12_Y_WU								= 0x02,
	LIS2DW12_Z_WU								= 0x01,
} WAKE_UP_SRC_REG;

extern	uint8_t LIS2DW12_GetWhoAmI(void);
extern	uint8_t LIS2DW12_SetCTRL_2_Reg(void);
extern	uint8_t LIS2DW12_Init(uint8_t fifo_locations,uint8_t *id,uint8_t *status,uint8_t *ie,uint8_t lis_full_scale_acc);
extern	uint8_t LIS2DW12_ReadAccRegs(uint8_t *axis_ptr);
extern	uint8_t LIS2DW12_GetStatusReg(void);
extern	uint8_t LIS2DW12_GetTempReg(void);
extern	uint8_t LIS2DW12_GetWakeSource(void);
extern	uint8_t LIS2DW12_Reset(void);
extern	uint8_t LIS2DW12_GetFifoSamples(void);
extern	void LIS2DW12_ConfigureFIFO(uint8_t FIFOMode, uint8_t FIFOThreshold);


#endif /* LIS2DW12_H_ */
