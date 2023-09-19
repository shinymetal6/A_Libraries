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
 *
STM32U5 includes
USB:
../../A_Libraries/ExternalLibraries/STM32U5/STM32_USB_Device_Library/Class/CDC
../../A_Libraries/Drivers/STM32U5/Usb_Device/Target
../../A_Libraries/ExternalLibraries/STM32U5/STM32_USB_Device_Library/Core

STM32H5 includes
USB:
../../A_Libraries/ExternalLibraries/STM32H5/STM32_USB_Device_Library/Class/CDC/Inc
../../A_Libraries/Drivers/STM32H5/USB_Device/Target
../../A_Libraries/ExternalLibraries/STM32H5/STM32_USB_Device_Library/Core/Inc
LWIP:
../../A_Libraries/Drivers/STM32H5/LWIP/Target
../../A_Libraries/ExternalLibraries/STM32H5/LwIP/system
../../A_Libraries/ExternalLibraries/STM32H5/LwIP/src/include
../../A_Libraries/Components/lan8742
NFC:
CRC and SPI1 must be enabled
SPI1 must have PLL3P @ 40 MHz ( DIVN 100 DIVQ10 ), 2 edges, 8 bit, motorola format -> 5MHz clock
../../A_Libraries/ExternalLibraries/Common/Nfc/ndef/Inc
../../A_Libraries/ExternalLibraries/Common/Nfc/ndef/Inc/message
../../A_Libraries/ExternalLibraries/Common/Nfc/ndef/Inc/poller
../../A_Libraries/ExternalLibraries/Common/Nfc/rfal/Inc
../../A_Libraries/Components/ST25R3916
*/
#endif /* INCLUDE_PATHS_H_ */
