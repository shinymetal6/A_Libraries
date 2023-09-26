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
 * sht40.h
 *
 *  Created on: Sep 22, 2023
 *      Author: fil
 */

#ifndef BSP_COMPONENTS_SHT40_SHT40_H_
#define BSP_COMPONENTS_SHT40_SHT40_H_


extern	int32_t  SHT40_StartAcquisition(void);
extern	int32_t  SHT40_ReadData(uint8_t *pData);

#endif /* BSP_COMPONENTS_SHT40_SHT40_H_ */
