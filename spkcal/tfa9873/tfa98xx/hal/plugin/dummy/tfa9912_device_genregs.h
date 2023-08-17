/************************************************************************/
/* Copyright 2014-2017 NXP Semiconductors                               */
/* Copyright 2020 GOODIX                                                */
/*                                                                      */
/* GOODIX Confidential. This software is owned or controlled by GOODIX  */
/* and may only be used strictly in accordance with the applicable      */
/* license terms.  By expressly accepting such terms or by downloading, */
/* installing, activating and/or otherwise using the software, you are  */
/* agreeing that you have read, and that you agree to comply with and   */
/* are bound by, such license terms.                                    */
/* If you do not agree to be bound by the applicable license terms,     */
/* then you may not retain, install, activate or otherwise use the      */
/* software.                                                            */
/*                                                                      */
/************************************************************************/

#ifndef _TFA9912_DEVICE_GENREGS_H
#define _TFA9912_DEVICE_GENREGS_H

#define TFA99XX_SYS_CONTROL0              0x00
#define TFA99XX_SYS_CONTROL1              0x01
#define TFA99XX_SYS_CONTROL2              0x02
#define TFA99XX_DEVICE_REVISION           0x03
#define TFA99XX_CLOCK_CONTROL             0x04
#define TFA99XX_CLOCK_GATING_CONTROL      0x05
#define TFA99XX_HW_PATH_CFG               0x06
#define TFA99XX_CLKCHK_TH                 0x07
#define TFA99XX_SIDE_TONE_CONFIG          0x0d
#define TFA99XX_CTRL_DIGTOANA_REG         0x0e
#define TFA99XX_STATUS_FLAGS0             0x10
#define TFA99XX_STATUS_FLAGS1             0x11
#define TFA99XX_STATUS_FLAGS3             0x13
#define TFA99XX_STATUS_FLAGS4             0x14
#define TFA99XX_BATTERY_VOLTAGE           0x15
#define TFA99XX_TEMPERATURE               0x16
#define TFA99XX_VDDP_VOLTAGE              0x17
#define TFA99XX_TDM_CONFIG0               0x20
#define TFA99XX_TDM_CONFIG1               0x21
#define TFA99XX_TDM_CONFIG2               0x22
#define TFA99XX_TDM_CONFIG3               0x23
#define TFA99XX_TDM_CONFIG4               0x24
#define TFA99XX_TDM_CONFIG6               0x26
#define TFA99XX_TDM_CONFIG7               0x27
#define TFA99XX_TDM_CONFIG8               0x28
#define TFA99XX_TDM_CONFIG9               0x29
#define TFA99XX_PDM_CONFIG0               0x31
#define TFA99XX_PDM_CONFIG1               0x32
#define TFA99XX_INTERRUPT_OUT_REG1        0x40
#define TFA99XX_INTERRUPT_OUT_REG2        0x41
#define TFA99XX_INTERRUPT_OUT_REG3        0x42
#define TFA99XX_INTERRUPT_IN_REG1         0x44
#define TFA99XX_INTERRUPT_IN_REG2         0x45
#define TFA99XX_INTERRUPT_IN_REG3         0x46
#define TFA99XX_INTERRUPT_ENABLE_REG1     0x48
#define TFA99XX_INTERRUPT_ENABLE_REG2     0x49
#define TFA99XX_INTERRUPT_ENABLE_REG3     0x4a
#define TFA99XX_STATUS_POLARITY_REG1      0x4c
#define TFA99XX_STATUS_POLARITY_REG2      0x4d
#define TFA99XX_STATUS_POLARITY_REG3      0x4e
#define TFA99XX_BAT_PROT_CONFIG           0x50
#define TFA99XX_AUDIO_CONTROL             0x51
#define TFA99XX_AMPLIFIER_CONFIG          0x52
#define TFA99XX_AUDIO_CONTROL2            0x5a
#define TFA99XX_CF_TAP_STATUS_0           0x5c
#define TFA99XX_CF_TAP_STATUS_1           0x5d
#define TFA99XX_TAP_MODE                  0x5e
#define TFA99XX_TDM_SOURCE_CTRL           0x68
#define TFA99XX_DCDC_CONTROL0             0x70
#define TFA99XX_DCDC_CONTROL4             0x74
#define TFA99XX_CF_CONTROLS               0x90
#define TFA99XX_CF_MAD                    0x91
#define TFA99XX_CF_MEM                    0x92
#define TFA99XX_CF_STATUS                 0x93
#define TFA99XX_MTPKEY2_REG               0xa1
#define TFA99XX_MTP_STATUS                0xa2
#define TFA99XX_KEY_PROTECTED_MTP_CONTROL 0xa3
#define TFA99XX_MTP_DATA_OUT_MSB          0xa5
#define TFA99XX_MTP_DATA_OUT_LSB          0xa6
#define TFA99XX_TEMP_SENSOR_CONFIG        0xb1
#define TFA99XX_SOFTWARE_PROFILE          0xee
#define TFA99XX_SOFTWARE_VSTEP            0xef
#define TFA99XX_KEY2_PROTECTED_MTP0       0xf0
#define TFA99XX_KEY1_PROTECTED_MTP4       0xf4
#define TFA99XX_KEY1_PROTECTED_MTP5       0xf5
#define TFA99XX_SYS_CONTROL0_POR                                0x0645
#define TFA99XX_SYS_CONTROL1_POR                                0x900b
#define TFA99XX_SYS_CONTROL2_POR                                0x6028
#define TFA99XX_DEVICE_REVISION_POR                             0x1a13
#define TFA99XX_CLOCK_CONTROL_POR                               0x0000
#define TFA99XX_CLOCK_GATING_CONTROL_POR                        0x7f6a
#define TFA99XX_HW_PATH_CFG_POR                                 0x0000
#define TFA99XX_CLKCHK_TH_POR                                   0x6a90
#define TFA99XX_SIDE_TONE_CONFIG_POR                            0x0ebf
#define TFA99XX_CTRL_DIGTOANA_REG_POR                           0x0000
#define TFA99XX_STATUS_FLAGS0_POR                               0x021d
#define TFA99XX_STATUS_FLAGS1_POR                               0x0004
#define TFA99XX_STATUS_FLAGS3_POR                               0x000f
#define TFA99XX_STATUS_FLAGS4_POR                               0x0200
#define TFA99XX_BATTERY_VOLTAGE_POR                             0x03ff
#define TFA99XX_TEMPERATURE_POR                                 0x0100
#define TFA99XX_VDDP_VOLTAGE_POR                                0x0000
#define TFA99XX_TDM_CONFIG0_POR                                 0x2890
#define TFA99XX_TDM_CONFIG1_POR                                 0xc1f1
#define TFA99XX_TDM_CONFIG2_POR                                 0x545c
#define TFA99XX_TDM_CONFIG3_POR                                 0x0006
#define TFA99XX_TDM_CONFIG4_POR                                 0x0000
#define TFA99XX_TDM_CONFIG6_POR                                 0x0010
#define TFA99XX_TDM_CONFIG7_POR                                 0x0001
#define TFA99XX_TDM_CONFIG8_POR                                 0x0001
#define TFA99XX_TDM_CONFIG9_POR                                 0x0002
#define TFA99XX_PDM_CONFIG0_POR                                 0x0000
#define TFA99XX_PDM_CONFIG1_POR                                 0x0000
#define TFA99XX_INTERRUPT_OUT_REG1_POR                          0x0081
#define TFA99XX_INTERRUPT_OUT_REG2_POR                          0x0000
#define TFA99XX_INTERRUPT_OUT_REG3_POR                          0x0000
#define TFA99XX_INTERRUPT_IN_REG1_POR                           0x0000
#define TFA99XX_INTERRUPT_IN_REG2_POR                           0x0000
#define TFA99XX_INTERRUPT_IN_REG3_POR                           0x0000
#define TFA99XX_INTERRUPT_ENABLE_REG1_POR                       0x0001
#define TFA99XX_INTERRUPT_ENABLE_REG2_POR                       0x0000
#define TFA99XX_INTERRUPT_ENABLE_REG3_POR                       0x0000
#define TFA99XX_STATUS_POLARITY_REG1_POR                        0x7fe3
#define TFA99XX_STATUS_POLARITY_REG2_POR                        0xfe7b
#define TFA99XX_STATUS_POLARITY_REG3_POR                        0x0095
#define TFA99XX_BAT_PROT_CONFIG_POR                             0x9391
#define TFA99XX_AUDIO_CONTROL_POR                               0x0080
#define TFA99XX_AMPLIFIER_CONFIG_POR                            0x7ae8
#define TFA99XX_AUDIO_CONTROL2_POR                              0x0000
#define TFA99XX_CF_TAP_STATUS_0_POR                             0x0000
#define TFA99XX_CF_TAP_STATUS_1_POR                             0x0000
#define TFA99XX_TAP_MODE_POR                                    0x0000
#define TFA99XX_TDM_SOURCE_CTRL_POR                             0x0400
#define TFA99XX_DCDC_CONTROL0_POR                               0x06e6
#define TFA99XX_DCDC_CONTROL4_POR                               0xd823
#define TFA99XX_CF_CONTROLS_POR                                 0x0001
#define TFA99XX_CF_MAD_POR                                      0x0000
#define TFA99XX_CF_MEM_POR                                      0x0000
#define TFA99XX_CF_STATUS_POR                                   0x0000
#define TFA99XX_MTPKEY2_REG_POR                                 0x0000
#define TFA99XX_MTP_STATUS_POR                                  0x0003
#define TFA99XX_KEY_PROTECTED_MTP_CONTROL_POR                   0x0000
#define TFA99XX_MTP_DATA_OUT_MSB_POR                            0x0000
#define TFA99XX_MTP_DATA_OUT_LSB_POR                            0x0000
#define TFA99XX_TEMP_SENSOR_CONFIG_POR                          0x0000
#define TFA99XX_SOFTWARE_PROFILE_POR                            0x0000
#define TFA99XX_SOFTWARE_VSTEP_POR                              0x0000
#define TFA99XX_KEY2_PROTECTED_MTP0_POR                         0x0000
#define TFA99XX_KEY1_PROTECTED_MTP4_POR                         0x0000
#define TFA99XX_KEY1_PROTECTED_MTP5_POR                         0x0000

#endif /* _TFA9912_DEVICE_GENREGS_H */
