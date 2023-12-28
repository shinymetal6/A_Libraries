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
 * include_paths.h
 *
 *  Created on: Sep 18, 2023
 *      Author: fil
 */

#ifndef INCLUDE_PATHS_H_
#define INCLUDE_PATHS_H_
/*
ALL platform, to exclude errors for duplicated symbols in file stm32h5xx_it.c :
1) set #ifdef A_NOT_USED circa @ line 79, after the closing } of the while in void NMI_Handler(void)
2) set #endif circa @ line 152 after   USER CODE BEGIN SVCall_IRQn 1 comment, before the } of void SVC_Handler(void)
3) set #ifdef A_NOT_USED circa @ line 166, after the closing } after USER CODE BEGIN DebugMonitor_IRQn 1 in DebugMon_Handler
4) set #endif circa @ line 194 after USER CODE BEGIN SysTick_IRQn 1 comment, before the } of void SysTick_Handler(void)
All platform to start A:
1) set A_init_mem(); between  USER CODE BEGIN SysInit  and USER CODE END SysInit
2) set A_start(); between USER CODE BEGIN 2 and USER CODE END 2
Those will raise 2 warning for implicit declaration, it's your choice to include the declarations somewhere


 *
STM32U5 includes
USB:
../../A_Libraries/ExternalLibraries/STM32U5/STM32_USB_Device_Library/Class/CDC
../../A_Libraries/Drivers/STM32U5/Usb_Device/Target
../../A_Libraries/ExternalLibraries/STM32U5/STM32_USB_Device_Library/Core
Exclude from compilation A_Libraries/Drivers/STM32H5/USB_Device/App/usbd_HID_desc.c or A_Libraries/Drivers/STM32H5/USB_Device/App/usbd_CDC_desc.c

STM32H5 includes
USB:
../../A_Libraries/ExternalLibraries/STM32H5/STM32_USB_Device_Library/Class/CDC/Inc
../../A_Libraries/Drivers/STM32H5/USB_Device/Target
../../A_Libraries/ExternalLibraries/STM32H5/STM32_USB_Device_Library/Core/Inc
LWIP:
../../A_Libraries/Drivers/STM32H5/LWIP/Target
../../A_Libraries/ExternalLibraries/STM32H5/LwIP/system
../../A_Libraries/ExternalLibraries/STM32H5/LwIP/src/include
NFC:
CRC and SPI1 must be enabled
SPI1 must have PLL3P @ 40 MHz ( DIVN 100 DIVQ10 ), 2 edges, 8 bit, motorola format -> 5MHz clock
../../A_Libraries/ExternalLibraries/Common/Nfc/rfal/Src
../../A_Libraries/ExternalLibraries/Common/Nfc
../../A_Libraries/ExternalLibraries/Common/Nfc/ndef/Inc
../../A_Libraries/ExternalLibraries/Common/Nfc/ndef/Inc/message
../../A_Libraries/ExternalLibraries/Common/Nfc/ndef/Inc/poller
../../A_Libraries/ExternalLibraries/Common/Nfc/rfal/Inc
../../A_Libraries/Components/ST25R3916

STM32F7 includes
USB:
../../A_Libraries/Drivers/STM32F7/USB_Host/Target
../../A_Libraries/Drivers/STM32F7/USB_Host/App
../../A_Libraries/Drivers/STM32F7/USB_Device/App
../../A_Libraries/Drivers/STM32F7/USB_Device/Target
../../A_Libraries/ExternalLibraries/STM32F7/STM32_USB_Device_Library/Class/CDC/Inc
../../A_Libraries/ExternalLibraries/STM32F7/STM32_USB_Host_Library/Class/AUDIO/Inc
../../A_Libraries/ExternalLibraries/STM32F7/STM32_USB_Host_Library/Class/CDC/Inc
../../A_Libraries/ExternalLibraries/STM32F7/STM32_USB_Host_Library/Class/HID/Inc
../../A_Libraries/ExternalLibraries/STM32F7/STM32_USB_Host_Library/Class/MSC/Inc
../../A_Libraries/ExternalLibraries/STM32F7/STM32_USB_Host_Library/Class/MTP/Inc
../../A_Libraries/ExternalLibraries/STM32F7/STM32_USB_Host_Library/Core/Inc
../../A_Libraries/ExternalLibraries/STM32F7/STM32_USB_Device_Library/Core/Inc
LWIP
../../A_Libraries/Drivers/STM32F7/LwIP/App
../../A_Libraries/Drivers/STM32F7/LwIP/Target
../../A_Libraries/ExternalLibraries/STM32F7/LwIP/src/include
../../A_Libraries/ExternalLibraries/STM32F7/LwIP/system
../../A_Libraries/ExternalLibraries/STM32F7/LwIP/src/include/netif/ppp
../../A_Libraries/ExternalLibraries/STM32F7/LwIP/src/include/lwip
../../A_Libraries/ExternalLibraries/STM32F7/LwIP/src/include/lwip/apps
../../A_Libraries/ExternalLibraries/STM32F7/LwIP/src/include/lwip/priv
../../A_Libraries/ExternalLibraries/STM32F7/LwIP/src/include/lwip/prot
../../A_Libraries/ExternalLibraries/STM32F7/LwIP/src/include/netif
../../A_Libraries/ExternalLibraries/STM32F7/LwIP/src/include/compat/posix
../../A_Libraries/ExternalLibraries/STM32F7/LwIP/src/include/compat/posix/arpa
../../A_Libraries/ExternalLibraries/STM32F7/LwIP/src/include/compat/posix/net
../../A_Libraries/ExternalLibraries/STM32F7/LwIP/src/include/compat/posix/sys
../../A_Libraries/ExternalLibraries/STM32F7/LwIP/src/include/compat/stdc
../../A_Libraries/ExternalLibraries/STM32F7/LwIP/system/arch
FAT
../../A_Libraries/ExternalLibraries/STM32F7/FatFs/src
../../A_Libraries/Drivers/STM32F7/FatFS/Target

STM32H7 includes
USB:
../../A_Libraries/Drivers/STM32H7/USB_Device/App
../../A_Libraries/Drivers/STM32H7/USB_Device/Target
../../A_Libraries/ExternalLibraries/STM32H7/STM32_USB_Device_Library/Core/Inc
../../A_Libraries/ExternalLibraries/STM32H7/STM32_USB_Device_Library/Class/CDC/Inc
LWIP
../../A_os/drivers/rmii
../../A_Libraries/Drivers/STM32H7/LwIP/App
../../A_Libraries/Drivers/STM32H7/LwIP/Target
../../A_Libraries/ExternalLibraries/STM32H7/LwIP/src/include
../../A_Libraries/ExternalLibraries/STM32H7/LwIP/src/include/lwip
../../A_Libraries/ExternalLibraries/STM32H7/LwIP/system
FAT
../../A_Libraries/Drivers
../../A_Libraries/ExternalLibraries/STM32H7/FatFs/src

*/
#endif /* INCLUDE_PATHS_H_ */
