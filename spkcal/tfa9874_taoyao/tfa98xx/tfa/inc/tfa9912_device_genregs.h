/*
* Copyright 2014-2020 NXP Semiconductors
* Copyright 2020 GOODIX  
* NOT A CONTRIBUTION.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/** Filename: tfa9912_device_genregs.h
 *  This file was generated automatically on 04/19/17 at 12:26:46.
 *  Source file: TFA9912_N1A_I2C_regmap_V1.39.xlsx
 */

#ifndef _TFA9912_DEVICE_GENREGS_H
#define _TFA9912_DEVICE_GENREGS_H


#define TFA99XX_SYS_CONTROL0                      0x00
#define TFA99XX_SYS_CONTROL1                      0x01
#define TFA99XX_SYS_CONTROL2                      0x02
#define TFA99XX_DEVICE_REVISION                   0x03
#define TFA99XX_CLOCK_CONTROL                     0x04
#define TFA99XX_CLOCK_GATING_CONTROL              0x05
#define TFA99XX_HW_PATH_CFG                       0x06
#define TFA99XX_CLKCHK_TH                         0x07
#define TFA99XX_AMP_CTRL                          0x08
#define TFA99XX_SIDE_TONE_CONFIG                  0x0d
#define TFA99XX_CTRL_DIGTOANA_REG                 0x0e
#define TFA99XX_STATUS_FLAGS0                     0x10
#define TFA99XX_STATUS_FLAGS1                     0x11
#define TFA99XX_STATUS_FLAGS3                     0x13
#define TFA99XX_STATUS_FLAGS4                     0x14
#define TFA99XX_BATTERY_VOLTAGE                   0x15
#define TFA99XX_TEMPERATURE                       0x16
#define TFA99XX_VDDP_VOLTAGE                      0x17
#define TFA99XX_TDM_CONFIG0                       0x20
#define TFA99XX_TDM_CONFIG1                       0x21
#define TFA99XX_TDM_CONFIG2                       0x22
#define TFA99XX_TDM_CONFIG3                       0x23
#define TFA99XX_TDM_CONFIG4                       0x24
#define TFA99XX_TDM_CONFIG5                       0x25
#define TFA99XX_TDM_CONFIG6                       0x26
#define TFA99XX_TDM_CONFIG7                       0x27
#define TFA99XX_TDM_CONFIG8                       0x28
#define TFA99XX_TDM_CONFIG9                       0x29
#define TFA99XX_PDM_CONFIG0                       0x31
#define TFA99XX_PDM_CONFIG1                       0x32
#define TFA99XX_INTERRUPT_OUT_REG1                0x40
#define TFA99XX_INTERRUPT_OUT_REG2                0x41
#define TFA99XX_INTERRUPT_OUT_REG3                0x42
#define TFA99XX_INTERRUPT_IN_REG1                 0x44
#define TFA99XX_INTERRUPT_IN_REG2                 0x45
#define TFA99XX_INTERRUPT_IN_REG3                 0x46
#define TFA99XX_INTERRUPT_ENABLE_REG1             0x48
#define TFA99XX_INTERRUPT_ENABLE_REG2             0x49
#define TFA99XX_INTERRUPT_ENABLE_REG3             0x4a
#define TFA99XX_STATUS_POLARITY_REG1              0x4c
#define TFA99XX_STATUS_POLARITY_REG2              0x4d
#define TFA99XX_STATUS_POLARITY_REG3              0x4e
#define TFA99XX_BAT_PROT_CONFIG                   0x50
#define TFA99XX_AUDIO_CONTROL                     0x51
#define TFA99XX_AMPLIFIER_CONFIG                  0x52
#define TFA99XX_KEY1_PROTECTED_AMPLIFIER_CONTROL0 0x53
#define TFA99XX_KEY1_PROTECTED_AMPLIFIER_CONTROL1 0x54
#define TFA99XX_KEY1_PROTECTED_AMPLIFIER_CONTROL2 0x55
#define TFA99XX_KEY1_PROTECTED_AMPLIFIER_CONTROL4 0x57
#define TFA99XX_KEY1_PROTECTED_PWM_CONFIG         0x58
#define TFA99XX_CF_TAP_STATUS_0                   0x5c
#define TFA99XX_CF_TAP_STATUS_1                   0x5d
#define TFA99XX_TAP_CONTROL                       0x5f
#define TFA99XX_PGA_CONTROL0                      0x60
#define TFA99XX_GAIN_ATT                          0x61
#define TFA99XX_LOW_NOISE_GAIN1                   0x62
#define TFA99XX_LOW_NOISE_GAIN2                   0x63
#define TFA99XX_MODE1_DETECTOR1                   0x64
#define TFA99XX_MODE1_DETECTOR2                   0x65
#define TFA99XX_BST_PFM_CTRL                      0x66
#define TFA99XX_LOW_POWER_CTRL                    0x67
#define TFA99XX_TDM_SOURCE_CTRL                   0x68
#define TFA99XX_SAM_CTRL                          0x69
#define TFA99XX_RST_MIN_VBAT_CTRL                 0x6a
#define TFA99XX_SYS_CONTROL3                      0x6b
#define TFA99XX_STATUS_FLAGS5                     0x6e
#define TFA99XX_DCDC_CONTROL0                     0x70
#define TFA99XX_KEY1_PROTECTED_DCDC_CONTROL3      0x73
#define TFA99XX_DCDC_CONTROL4                     0x74
#define TFA99XX_DCDC_CONTROL5                     0x75
#define TFA99XX_DCDC_CONTROL6                     0x76
#define TFA99XX_KEY2_PROTECTED_DCDC_CONTROL7      0x77
#define TFA99XX_KEY2_PROTECTED_CURSENSE_CONFIG0   0x80
#define TFA99XX_KEY2_PROTECTED_CURSENSE_CONFIG2   0x82
#define TFA99XX_KEY2_PROTECTED_CURSENSE_CONFIG3   0x83
#define TFA99XX_KEY2_PROTECTED_CURSENSE_CONFIG4   0x84
#define TFA99XX_KEY2_PROTECTED_CURSENSE_CONFIG5   0x85
#define TFA99XX_KEY2_PROTECTED_CURSENSE_CONFIG7   0x87
#define TFA99XX_KEY2_PROTECTED_VOLSENSE_CONFIG    0x88
#define TFA99XX_CURSENSE_CONFIG                   0x89
#define TFA99XX_CF_CONTROLS                       0x90
#define TFA99XX_CF_MAD                            0x91
#define TFA99XX_CF_MEM                            0x92
#define TFA99XX_CF_STATUS                         0x93
#define TFA99XX_MTPKEY1_REG                       0xa0
#define TFA99XX_MTPKEY2_REG                       0xa1
#define TFA99XX_MTP_STATUS                        0xa2
#define TFA99XX_KEY_PROTECTED_MTP_CONTROL         0xa3
#define TFA99XX_KEY1_PROTECTED_FAIM_CONTROL       0xa4
#define TFA99XX_MTP_DATA_OUT_MSB                  0xa5
#define TFA99XX_MTP_DATA_OUT_LSB                  0xa6
#define TFA99XX_KEY1_PROTECTED_PROTECTION_CONFIG  0xb0
#define TFA99XX_TEMP_SENSOR_CONFIG                0xb1
#define TFA99XX_KEY1_PROTECTED_DIRECT_CONTROL0    0xc0
#define TFA99XX_KEY1_PROTECTED_DIRECT_CONTROL1    0xc1
#define TFA99XX_KEY1_PROTECTED_TEST_CONFIG0       0xc3
#define TFA99XX_KEY1_PROTECTED_TEST_CONFIG1       0xc4
#define TFA99XX_KEY1_PROTECTED_TEST_CONFIG2       0xc5
#define TFA99XX_KEY1_PROTECTED_TEST_CONFIG3       0xc6
#define TFA99XX_KEY1_PROTECTED_DIGIMUX_CONTROL1   0xc8
#define TFA99XX_KEY1_PROTECTED_ANAMUX_CONTROL0    0xca
#define TFA99XX_KEY1_PROTECTED_ANAMUX_CONTROL1    0xcb
#define TFA99XX_KEY1_PROTECTED_PLL_TEST0          0xcd
#define TFA99XX_KEY1_PROTECTED_PLL_TEST3          0xd0
#define TFA99XX_KEY1_PROTECTED_TSIG_CONTROL1      0xd2
#define TFA99XX_KEY1_PROTECTED_ADC10_CONTROL      0xd3
#define TFA99XX_KEY1_PROTECTED_ADC10_DATA         0xd4
#define TFA99XX_KEY2_PROTECTED_CTRL_DIGTOANA      0xd5
#define TFA99XX_KEY1_PROTECTED_CLKDIV_CONTROL     0xd6
#define TFA99XX_KEY1_PROTECTED_IO_CONFIG2         0xd7
#define TFA99XX_KEY1_PROTECTED_TEST_CTRL1         0xd8
#define TFA99XX_KEY1_PROTECTED_MODE_OVERRULE      0xd9
#define TFA99XX_KEY1_PROTECTED_FRO8_CALIB_CTRL    0xed
#define TFA99XX_SOFTWARE_PROFILE                  0xee
#define TFA99XX_SOFTWARE_VSTEP                    0xef
#define TFA99XX_KEY2_PROTECTED_MTP0               0xf0
#define TFA99XX_KEY1_PROTECTED_MTP2               0xf2
#define TFA99XX_KEY2_PROTECTED_MTP4               0xf4
#define TFA99XX_KEY1_PROTECTED_MTP6               0xf6
#define TFA99XX_KEY1_PROTECTED_MTP7               0xf7
#define TFA99XX_KEY1_PROTECTED_MTP9               0xf9
#define TFA99XX_KEY1_PROTECTED_MTPF               0xff
#define TFA99XX_SYS_CONTROL0_POR
#define TFA99XX_SYS_CONTROL1_POR
#define TFA99XX_SYS_CONTROL2_POR
#define TFA99XX_DEVICE_REVISION_POR
#define TFA99XX_CLOCK_CONTROL_POR
#define TFA99XX_CLOCK_GATING_CONTROL_POR
#define TFA99XX_HW_PATH_CFG_POR
#define TFA99XX_CLKCHK_TH_POR
#define TFA99XX_AMP_CTRL_POR
#define TFA99XX_SIDE_TONE_CONFIG_POR
#define TFA99XX_CTRL_DIGTOANA_REG_POR
#define TFA99XX_STATUS_FLAGS0_POR
#define TFA99XX_STATUS_FLAGS1_POR
#define TFA99XX_STATUS_FLAGS3_POR
#define TFA99XX_STATUS_FLAGS4_POR
#define TFA99XX_BATTERY_VOLTAGE_POR
#define TFA99XX_TEMPERATURE_POR
#define TFA99XX_VDDP_VOLTAGE_POR
#define TFA99XX_TDM_CONFIG0_POR
#define TFA99XX_TDM_CONFIG1_POR
#define TFA99XX_TDM_CONFIG2_POR
#define TFA99XX_TDM_CONFIG3_POR
#define TFA99XX_TDM_CONFIG4_POR
#define TFA99XX_TDM_CONFIG5_POR
#define TFA99XX_TDM_CONFIG6_POR
#define TFA99XX_TDM_CONFIG7_POR
#define TFA99XX_TDM_CONFIG8_POR
#define TFA99XX_TDM_CONFIG9_POR
#define TFA99XX_PDM_CONFIG0_POR
#define TFA99XX_PDM_CONFIG1_POR
#define TFA99XX_INTERRUPT_OUT_REG1_POR
#define TFA99XX_INTERRUPT_OUT_REG2_POR
#define TFA99XX_INTERRUPT_OUT_REG3_POR
#define TFA99XX_INTERRUPT_IN_REG1_POR
#define TFA99XX_INTERRUPT_IN_REG2_POR
#define TFA99XX_INTERRUPT_IN_REG3_POR
#define TFA99XX_INTERRUPT_ENABLE_REG1_POR
#define TFA99XX_INTERRUPT_ENABLE_REG2_POR
#define TFA99XX_INTERRUPT_ENABLE_REG3_POR
#define TFA99XX_STATUS_POLARITY_REG1_POR
#define TFA99XX_STATUS_POLARITY_REG2_POR
#define TFA99XX_STATUS_POLARITY_REG3_POR
#define TFA99XX_BAT_PROT_CONFIG_POR
#define TFA99XX_AUDIO_CONTROL_POR
#define TFA99XX_AMPLIFIER_CONFIG_POR
#define TFA99XX_KEY1_PROTECTED_AMPLIFIER_CONTROL0_POR
#define TFA99XX_KEY1_PROTECTED_AMPLIFIER_CONTROL1_POR
#define TFA99XX_KEY1_PROTECTED_AMPLIFIER_CONTROL2_POR
#define TFA99XX_KEY1_PROTECTED_AMPLIFIER_CONTROL4_POR
#define TFA99XX_KEY1_PROTECTED_PWM_CONFIG_POR
#define TFA99XX_CF_TAP_STATUS_0_POR
#define TFA99XX_CF_TAP_STATUS_1_POR
#define TFA99XX_TAP_CONTROL_POR
#define TFA99XX_PGA_CONTROL0_POR
#define TFA99XX_GAIN_ATT_POR
#define TFA99XX_LOW_NOISE_GAIN1_POR
#define TFA99XX_LOW_NOISE_GAIN2_POR
#define TFA99XX_MODE1_DETECTOR1_POR
#define TFA99XX_MODE1_DETECTOR2_POR
#define TFA99XX_BST_PFM_CTRL_POR
#define TFA99XX_LOW_POWER_CTRL_POR
#define TFA99XX_TDM_SOURCE_CTRL_POR
#define TFA99XX_SAM_CTRL_POR
#define TFA99XX_RST_MIN_VBAT_CTRL_POR
#define TFA99XX_SYS_CONTROL3_POR
#define TFA99XX_STATUS_FLAGS5_POR
#define TFA99XX_DCDC_CONTROL0_POR
#define TFA99XX_KEY1_PROTECTED_DCDC_CONTROL3_POR
#define TFA99XX_DCDC_CONTROL4_POR
#define TFA99XX_DCDC_CONTROL5_POR
#define TFA99XX_DCDC_CONTROL6_POR
#define TFA99XX_KEY2_PROTECTED_DCDC_CONTROL7_POR
#define TFA99XX_KEY2_PROTECTED_CURSENSE_CONFIG0_POR
#define TFA99XX_KEY2_PROTECTED_CURSENSE_CONFIG2_POR
#define TFA99XX_KEY2_PROTECTED_CURSENSE_CONFIG3_POR
#define TFA99XX_KEY2_PROTECTED_CURSENSE_CONFIG4_POR
#define TFA99XX_KEY2_PROTECTED_CURSENSE_CONFIG5_POR
#define TFA99XX_KEY2_PROTECTED_CURSENSE_CONFIG7_POR
#define TFA99XX_KEY2_PROTECTED_VOLSENSE_CONFIG_POR
#define TFA99XX_CURSENSE_CONFIG_POR
#define TFA99XX_CF_CONTROLS_POR
#define TFA99XX_CF_MAD_POR
#define TFA99XX_CF_MEM_POR
#define TFA99XX_CF_STATUS_POR
#define TFA99XX_MTPKEY1_REG_POR
#define TFA99XX_MTPKEY2_REG_POR
#define TFA99XX_MTP_STATUS_POR
#define TFA99XX_KEY_PROTECTED_MTP_CONTROL_POR
#define TFA99XX_KEY1_PROTECTED_FAIM_CONTROL_POR
#define TFA99XX_MTP_DATA_OUT_MSB_POR
#define TFA99XX_MTP_DATA_OUT_LSB_POR
#define TFA99XX_KEY1_PROTECTED_PROTECTION_CONFIG_POR
#define TFA99XX_TEMP_SENSOR_CONFIG_POR
#define TFA99XX_KEY1_PROTECTED_DIRECT_CONTROL0_POR
#define TFA99XX_KEY1_PROTECTED_DIRECT_CONTROL1_POR
#define TFA99XX_KEY1_PROTECTED_TEST_CONFIG0_POR
#define TFA99XX_KEY1_PROTECTED_TEST_CONFIG1_POR
#define TFA99XX_KEY1_PROTECTED_TEST_CONFIG2_POR
#define TFA99XX_KEY1_PROTECTED_TEST_CONFIG3_POR
#define TFA99XX_KEY1_PROTECTED_DIGIMUX_CONTROL1_POR
#define TFA99XX_KEY1_PROTECTED_ANAMUX_CONTROL0_POR
#define TFA99XX_KEY1_PROTECTED_ANAMUX_CONTROL1_POR
#define TFA99XX_KEY1_PROTECTED_PLL_TEST0_POR
#define TFA99XX_KEY1_PROTECTED_PLL_TEST3_POR
#define TFA99XX_KEY1_PROTECTED_TSIG_CONTROL1_POR
#define TFA99XX_KEY1_PROTECTED_ADC10_CONTROL_POR
#define TFA99XX_KEY1_PROTECTED_ADC10_DATA_POR
#define TFA99XX_KEY2_PROTECTED_CTRL_DIGTOANA_POR
#define TFA99XX_KEY1_PROTECTED_CLKDIV_CONTROL_POR
#define TFA99XX_KEY1_PROTECTED_IO_CONFIG2_POR
#define TFA99XX_KEY1_PROTECTED_TEST_CTRL1_POR
#define TFA99XX_KEY1_PROTECTED_MODE_OVERRULE_POR
#define TFA99XX_KEY1_PROTECTED_FRO8_CALIB_CTRL_POR
#define TFA99XX_SOFTWARE_PROFILE_POR
#define TFA99XX_SOFTWARE_VSTEP_POR
#define TFA99XX_KEY2_PROTECTED_MTP0_POR
#define TFA99XX_KEY1_PROTECTED_MTP2_POR
#define TFA99XX_KEY2_PROTECTED_MTP4_POR
#define TFA99XX_KEY1_PROTECTED_MTP6_POR
#define TFA99XX_KEY1_PROTECTED_MTP7_POR
#define TFA99XX_KEY1_PROTECTED_MTP9_POR
#define TFA99XX_KEY1_PROTECTED_MTPF_POR

#endif /* _TFA9912_DEVICE_GENREGS_H */
