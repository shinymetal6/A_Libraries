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
 * st25r3916b.h
 *
 *  Created on: Sep 25, 2023
 *      Author: fil
 */

#ifndef COMPONENTS_ST25R3916B_DRIVER_ST25R3916B_H_
#define COMPONENTS_ST25R3916B_DRIVER_ST25R3916B_H_

/* ST25R3916 direct commands */
#define ST25R3916_CMD_SET_DEFAULT              0xC1U    /*!< Puts the chip in default state (same as after power-up) */
#define ST25R3916_CMD_STOP                     0xC2U    /*!< Stops all activities and clears FIFO                    */
#define ST25R3916_CMD_TRANSMIT_WITH_CRC        0xC4U    /*!< Transmit with CRC                                       */
#define ST25R3916_CMD_TRANSMIT_WITHOUT_CRC     0xC5U    /*!< Transmit without CRC                                    */
#define ST25R3916_CMD_TRANSMIT_REQA            0xC6U    /*!< Transmit REQA                                           */
#define ST25R3916_CMD_TRANSMIT_WUPA            0xC7U    /*!< Transmit WUPA                                           */
#define ST25R3916_CMD_INITIAL_RF_COLLISION     0xC8U    /*!< NFC transmit with Initial RF Collision Avoidance        */
#define ST25R3916_CMD_RESPONSE_RF_COLLISION_N  0xC9U    /*!< NFC transmit with Response RF Collision Avoidance       */
#define ST25R3916_CMD_GOTO_SENSE               0xCDU    /*!< Passive target logic to Sense/Idle state                */
#define ST25R3916_CMD_GOTO_SLEEP               0xCEU    /*!< Passive target logic to Sleep/Halt state                */
#define ST25R3916_CMD_MASK_RECEIVE_DATA        0xD0U    /*!< Mask receive data                                       */
#define ST25R3916_CMD_UNMASK_RECEIVE_DATA      0xD1U    /*!< Unmask receive data                                     */
#define ST25R3916_CMD_AM_MOD_STATE_CHANGE      0xD2U    /*!< AM Modulation state change                              */
#define ST25R3916_CMD_MEASURE_AMPLITUDE        0xD3U    /*!< Measure singal amplitude on RFI inputs                  */
#define ST25R3916_CMD_RESET_RXGAIN             0xD5U    /*!< Reset RX Gain                                           */
#define ST25R3916_CMD_ADJUST_REGULATORS        0xD6U    /*!< Adjust regulators                                       */
#define ST25R3916_CMD_CALIBRATE_DRIVER_TIMING  0xD8U    /*!< Starts the sequence to adjust the driver timing         */
#define ST25R3916_CMD_MEASURE_PHASE            0xD9U    /*!< Measure phase between RFO and RFI signal                */
#define ST25R3916_CMD_CLEAR_RSSI               0xDAU    /*!< Clear RSSI bits and restart the measurement             */
#define ST25R3916_CMD_CLEAR_FIFO               0xDBU    /*!< Clears FIFO, Collision and IRQ status                   */
#define ST25R3916_CMD_TRANSPARENT_MODE         0xDCU    /*!< Transparent mode                                        */
#define ST25R3916_CMD_MEASURE_VDD              0xDFU    /*!< Measure power supply voltage                            */
#define ST25R3916_CMD_START_GP_TIMER           0xE0U    /*!< Start the general purpose timer                         */
#define ST25R3916_CMD_START_WUP_TIMER          0xE1U    /*!< Start the wake-up timer                                 */
#define ST25R3916_CMD_START_MASK_RECEIVE_TIMER 0xE2U    /*!< Start the mask-receive timer                            */
#define ST25R3916_CMD_START_NO_RESPONSE_TIMER  0xE3U    /*!< Start the no-response timer                             */
#define ST25R3916_CMD_START_PPON2_TIMER        0xE4U    /*!< Start PPon2 timer                                       */
#define ST25R3916_CMD_STOP_NRT                 0xE8U    /*!< Stop No Response Timer                                  */
#define ST25R3916_CMD_RC_CAL                   0xEAU    /*!< Trigger RC calibration                                  */
#define ST25R3916_CMD_SPACE_B_ACCESS           0xFBU    /*!< Enable R/W access to the test registers                 */
#define ST25R3916_CMD_TEST_ACCESS              0xFCU    /*!< Enable R/W access to the test registers                 */

/* IO configuration registers */
#define ST25R3916_REG_IO_CONF1                              0x00U    /*!< RW IO Configuration Register 1                       */
#define ST25R3916_REG_IO_CONF2                              0x01U    /*!< RW IO Configuration Register 2                       */
#define ST25R3916_REG_OP_CONTROL                            0x02U    /*!< RW Operation Control Register                        */
#define ST25R3916_REG_MODE                                  0x03U    /*!< RW Mode Definition Register                          */
#define ST25R3916_REG_BIT_RATE                              0x04U    /*!< RW Bit Rate Definition Register                      */
#define ST25R3916_REG_ISO14443A_NFC                         0x05U    /*!< RW ISO14443A and NFC 106 kBit/s Settings Register    */
#define ST25R3916_REG_EMD_SUP_CONF       (ST25R3916_SPACE_B|0x05U)   /*!< RW EMD Suppression Configuration Register            */
#define ST25R3916_REG_ISO14443B_1                           0x06U    /*!< RW ISO14443B Settings Register 1                     */
#define ST25R3916_REG_SUBC_START_TIME    (ST25R3916_SPACE_B|0x06U)   /*!< RW Subcarrier Start Time Register                    */
#define ST25R3916_REG_ISO14443B_2                           0x07U    /*!< RW ISO14443B Settings Register 2                     */
#define ST25R3916_REG_PASSIVE_TARGET                        0x08U    /*!< RW Passive Target Definition Register                */
#define ST25R3916_REG_STREAM_MODE                           0x09U    /*!< RW Stream Mode Definition Register                   */
#define ST25R3916_REG_AUX                                   0x0AU    /*!< RW Auxiliary Definition Register                     */
#define ST25R3916_REG_RX_CONF1                              0x0BU    /*!< RW Receiver Configuration Register 1                 */
#define ST25R3916_REG_RX_CONF2                              0x0CU    /*!< RW Receiver Configuration Register 2                 */
#define ST25R3916_REG_RX_CONF3                              0x0DU    /*!< RW Receiver Configuration Register 3                 */
#define ST25R3916_REG_RX_CONF4                              0x0EU    /*!< RW Receiver Configuration Register 4                 */
#define ST25R3916_REG_P2P_RX_CONF        (ST25R3916_SPACE_B|0x0BU)   /*!< RW P2P Receiver Configuration Register 1             */
#define ST25R3916_REG_CORR_CONF1         (ST25R3916_SPACE_B|0x0CU)   /*!< RW Correlator configuration register 1               */
#define ST25R3916_REG_CORR_CONF2         (ST25R3916_SPACE_B|0x0DU)   /*!< RW Correlator configuration register 2               */
#define ST25R3916_REG_MASK_RX_TIMER                         0x0FU    /*!< RW Mask Receive Timer Register                       */
#define ST25R3916_REG_NO_RESPONSE_TIMER1                    0x10U    /*!< RW No-response Timer Register 1                      */
#define ST25R3916_REG_NO_RESPONSE_TIMER2                    0x11U    /*!< RW No-response Timer Register 2                      */
#define ST25R3916_REG_TIMER_EMV_CONTROL                     0x12U    /*!< RW Timer and EMV Control                             */
#define ST25R3916_REG_GPT1                                  0x13U    /*!< RW General Purpose Timer Register 1                  */
#define ST25R3916_REG_GPT2                                  0x14U    /*!< RW General Purpose Timer Register 2                  */
#define ST25R3916_REG_PPON2                                 0x15U    /*!< RW PPON2 Field waiting Timer Register                */
#define ST25R3916_REG_SQUELCH_TIMER      (ST25R3916_SPACE_B|0x0FU)   /*!< RW Squelch timeout Register                          */
#define ST25R3916_REG_FIELD_ON_GT        (ST25R3916_SPACE_B|0x15U)   /*!< RW NFC Field on guard time                           */
#define ST25R3916_REG_IRQ_MASK_MAIN                         0x16U    /*!< RW Mask Main Interrupt Register                      */
#define ST25R3916_REG_IRQ_MASK_TIMER_NFC                    0x17U    /*!< RW Mask Timer and NFC Interrupt Register             */
#define ST25R3916_REG_IRQ_MASK_ERROR_WUP                    0x18U    /*!< RW Mask Error and Wake-up Interrupt Register         */
#define ST25R3916_REG_IRQ_MASK_TARGET                       0x19U    /*!< RW Mask 3916 Target Interrupt Register               */
#define ST25R3916_REG_IRQ_MAIN                              0x1AU    /*!< R  Main Interrupt Register                           */
#define ST25R3916_REG_IRQ_TIMER_NFC                         0x1BU    /*!< R  Timer and NFC Interrupt Register                  */
#define ST25R3916_REG_IRQ_ERROR_WUP                         0x1CU    /*!< R  Error and Wake-up Interrupt Register              */
#define ST25R3916_REG_IRQ_TARGET                            0x1DU    /*!< R  ST25R3916 Target Interrupt Register               */
#define ST25R3916_REG_FIFO_STATUS1                          0x1EU    /*!< R  FIFO Status Register 1                            */
#define ST25R3916_REG_FIFO_STATUS2                          0x1FU    /*!< R  FIFO Status Register 2                            */
#define ST25R3916_REG_COLLISION_STATUS                      0x20U    /*!< R  Collision Display Register                        */
#define ST25R3916_REG_PASSIVE_TARGET_STATUS                 0x21U    /*!< R  Passive target state status                       */
#define ST25R3916_REG_NUM_TX_BYTES1                         0x22U    /*!< RW Number of Transmitted Bytes Register 1            */
#define ST25R3916_REG_NUM_TX_BYTES2                         0x23U    /*!< RW Number of Transmitted Bytes Register 2            */
#define ST25R3916_REG_NFCIP1_BIT_RATE                       0x24U    /*!< R  NFCIP Bit Rate Detection Display Register         */
#define ST25R3916_REG_AD_RESULT                             0x25U    /*!< R  A/D Converter Output Register                     */
#define ST25R3916_REG_ANT_TUNE_A                            0x26U    /*!< RW Antenna Tuning Control (AAT-A) Register 1         */
#define ST25R3916_REG_ANT_TUNE_B                            0x27U    /*!< RW Antenna Tuning Control (AAT-B) Register 2         */
#define ST25R3916_REG_TX_DRIVER                             0x28U    /*!< RW TX driver register                                */
#define ST25R3916_REG_PT_MOD                                0x29U    /*!< RW PT modulation Register                            */
#define ST25R3916_REG_AUX_MOD            (ST25R3916_SPACE_B|0x28U)   /*!< RW Aux Modulation setting Register                   */
#define ST25R3916_REG_TX_DRIVER_TIMING   (ST25R3916_SPACE_B|0x29U)   /*!< RW TX driver timing Register                         */
#define ST25R3916_REG_RES_AM_MOD         (ST25R3916_SPACE_B|0x2AU)   /*!< RW Resistive AM modulation register                  */
#define ST25R3916_REG_TX_DRIVER_STATUS   (ST25R3916_SPACE_B|0x2BU)   /*!< R  TX driver timing readout Register                 */
#define ST25R3916_REG_FIELD_THRESHOLD_ACTV                  0x2AU    /*!< RW External Field Detector Activation Threshold Reg  */
#define ST25R3916_REG_FIELD_THRESHOLD_DEACTV                0x2BU    /*!< RW External Field Detector Deactivation Threshold Reg*/
#define ST25R3916_REG_REGULATOR_CONTROL                     0x2CU    /*!< RW Regulated Voltage Control Register                */
#define ST25R3916_REG_REGULATOR_RESULT   (ST25R3916_SPACE_B|0x2CU)   /*!< R Regulator Display Register                         */
#define ST25R3916_REG_RSSI_RESULT                           0x2DU    /*!< R RSSI Display Register                              */
#define ST25R3916_REG_GAIN_RED_STATE                        0x2EU    /*!< R Gain Reduction State Register                      */
#define ST25R3916_REG_CAP_SENSOR_CONTROL                    0x2FU    /*!< RW Capacitive Sensor Control Register                */
#define ST25R3916_REG_CAP_SENSOR_RESULT                     0x30U    /*!< R  Capacitive Sensor Display Register                */
#define ST25R3916_REG_AUX_DISPLAY                           0x31U    /*!< R Auxiliary Display Register                         */
#define ST25R3916_REG_OVERSHOOT_CONF1    (ST25R3916_SPACE_B|0x30U)   /*!< RW  Overshoot Protection Configuration Register 1    */
#define ST25R3916_REG_OVERSHOOT_CONF2    (ST25R3916_SPACE_B|0x31U)   /*!< RW  Overshoot Protection Configuration Register 2    */
#define ST25R3916_REG_UNDERSHOOT_CONF1   (ST25R3916_SPACE_B|0x32U)   /*!< RW  Undershoot Protection Configuration Register 1   */
#define ST25R3916_REG_UNDERSHOOT_CONF2   (ST25R3916_SPACE_B|0x33U)   /*!< RW  Undershoot Protection Configuration Register 2   */
#define ST25R3916_REG_AWS_CONF1          (ST25R3916_SPACE_B|0x2EU)   /*!< RW  AWS Configuration Register 1                     */
#define ST25R3916_REG_AWS_CONF2          (ST25R3916_SPACE_B|0x2FU)   /*!< RW  AWS Configuration Register 2                     */
#define ST25R3916_REG_AWS_TIME1          (ST25R3916_SPACE_B|0x34U)   /*!< RW  AWS Time Register 1                              */
#define ST25R3916_REG_AWS_TIME2          (ST25R3916_SPACE_B|0x35U)   /*!< RW  AWS Time Register 2                              */
#define ST25R3916_REG_AWS_TIME3          (ST25R3916_SPACE_B|0x36U)   /*!< RW  AWS Time Register 1                              */
#define ST25R3916_REG_AWS_TIME4          (ST25R3916_SPACE_B|0x37U)   /*!< RW  AWS Time Register 2                              */
#define ST25R3916_REG_AWS_TIME5          (ST25R3916_SPACE_B|0x38U)   /*!< RW  AWS Time Register 1                              */
#define ST25R3916_REG_AWS_RC_CAL         (ST25R3916_SPACE_B|0x39U)   /*!< RW  AWS Time Register 2                              */
#define ST25R3916_REG_WUP_TIMER_CONTROL                     0x32U    /*!< RW Wake-up Timer Control Register                    */
#define ST25R3916_REG_AMPLITUDE_MEASURE_CONF                0x33U    /*!< RW Amplitude Measurement Configuration Register      */
#define ST25R3916_REG_AMPLITUDE_MEASURE_REF                 0x34U    /*!< RW Amplitude Measurement Reference Register          */
#define ST25R3916_REG_AMPLITUDE_MEASURE_AA_RESULT           0x35U    /*!< R  Amplitude Measurement Auto Averaging Display Reg  */
#define ST25R3916_REG_AMPLITUDE_MEASURE_RESULT              0x36U    /*!< R  Amplitude Measurement Display Register            */
#define ST25R3916_REG_PHASE_MEASURE_CONF                    0x37U    /*!< RW Phase Measurement Configuration Register          */
#define ST25R3916_REG_PHASE_MEASURE_REF                     0x38U    /*!< RW Phase Measurement Reference Register              */
#define ST25R3916_REG_PHASE_MEASURE_AA_RESULT               0x39U    /*!< R  Phase Measurement Auto Averaging Display Register */
#define ST25R3916_REG_PHASE_MEASURE_RESULT                  0x3AU    /*!< R  Phase Measurement Display Register                */
#define ST25R3916_REG_IC_IDENTITY                           0x3FU    /*!< R  Chip Id: 0 for old silicon, v2 silicon: 0x09      */


#define ST25R3916_SPACE_B					0x40U    /*!< ST25R3916 Space-B indicator                          */

#define ST25R3916_WRITE_MODE            (0U << 6)                      /*!< ST25R3916 Operation Mode: Write                                */
#define ST25R3916_READ_MODE             (1U << 6)                      /*!< ST25R3916 Operation Mode: Read                                 */
#define ST25R3916_CMD_MODE					(3U << 6)                      /*!< ST25R3916 Operation Mode: Direct Command                       */

#define ST25R3916_REG_IO_CONF2_io_drv_lvl                     (1U<<2)
#define ST25R3916_REG_IRQ_MASK_MAIN_value                     (0x80)
#define ST25R3916_REG_OP_CONTROL_en                           (1U<<7)
#define ST25R3916_REG_AUX_DISPLAY_osc_ok                      (1U<<4)
#define ST25R3916_REG_IO_CONF2_miso_pd1                       (1U<<3)
#define ST25R3916_REG_IO_CONF2_miso_pd2                       (1U<<4)
#define ST25R3916_IRQ_MASK_DCT             (uint32_t)(0x00008000U)   /*!< ST25R3916 termination of direct command interrupt.          */
#define ST25R3916_IRQ_MASK_OSC             (uint32_t)(0x00000080U)   /*!< ST25R3916 oscillator stable interrupt                       */

#endif /* COMPONENTS_ST25R3916B_DRIVER_ST25R3916B_H_ */
