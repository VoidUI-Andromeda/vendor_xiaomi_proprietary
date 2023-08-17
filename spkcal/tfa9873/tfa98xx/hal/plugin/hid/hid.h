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

#ifndef HID_H_
#define HID_H_

#ifdef HAL_HID
int lxHidNrDevices(void);
int lxHidWaitOnPinEvent(int, int , unsigned int);
int lxHidNrDevices(void);
int lxHidWaitOnPinEvent(int, int, unsigned int);
#endif

#endif
