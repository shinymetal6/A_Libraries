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
 * qspi_mngr.c
 *
 *  Created on: Dec 23, 2023
 *      Author: fil
 */

#include "main.h"
#include "../../../../../../A_os/kernel/A.h"
#include "../../../../../../A_os/kernel/system_default.h"
#include "qspi_mngr.h"

extern	Asys_t			Asys;

uint8_t init_qspi(void)
{
	//Asys.flash_id = W25Q_Init();
	//if ( Asys.flash_id )
		//Asys.flash_on_board = ASYS_FLASH_FOUND;
	W25Q_ReadID(&Asys.qspi_id);
	return 0;
}

