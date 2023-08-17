//#define LOG_NDEBUG 0
#define LOG_TAG "audio_hw_cspl_spkcal"
#include <log/log.h>
#include <utils/Log.h>

#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <tinyalsa/asoundlib.h>
#include <audio_utils/format.h>
#include <hardware/hardware.h>
#include <media/AudioSystem.h>
#include <cutils/str_parms.h>
//#include <cirrus_cal.h>
#include <media/mediaplayer.h>
#include <media/IMediaHTTPService.h>
#include <utils/threads.h>
#include <binder/ProcessState.h>
#include <cutils/properties.h>
#include <time.h>
#include "spkcal.h"

using namespace android;

//#ifndef FACTORY_BUILD
#define MEDIA_PLAY
//#endif

#define THERMALSNS "/sys/class/thermal/thermal_zone%d/temp"
#define THERMALTXT "/data/vendor/cit/thermals_%s.txt"

#if defined(CONFIG_TARGET_PRODUCT_APOLLO)
static int thermal_idx[] = {41, 42, 48, 49, 78, 81, 84};
#endif
#if defined(CONFIG_TARGET_PRODUCT_CAS) || defined (CONFIG_TARGET_PRODUCT_ALIOTH) || defined (CONFIG_TARGET_PRODUCT_PSYCHE) || defined(CONFIG_TARGET_PRODUCT_VENUS) || defined(CONFIG_TARGET_PRODUCT_STAR) || defined(CONFIG_TARGET_PRODUCT_HAYDN) || defined(CONFIG_TARGET_PRODUCT_ODIN) || defined(CONFIG_TARGET_PRODUCT_VILI)
static int thermal_idx[] = {41, 42, 48, 49, 75, 76, 78, 79, 80, 81, 82, 84};
#endif

#if defined(CONFIG_TARGET_PRODUCT_CAS) || defined(CONFIG_TARGET_PRODUCT_APOLLO) || defined (CONFIG_TARGET_PRODUCT_ALIOTH) || defined(CONFIG_TARGET_PRODUCT_VENUS) || defined(CONFIG_TARGET_PRODUCT_STAR) || defined(CONFIG_TARGET_PRODUCT_HAYDN) || defined(CONFIG_TARGET_PRODUCT_ODIN) || defined(CONFIG_TARGET_PRODUCT_VILI)
const int  THERMALNUM =  sizeof(thermal_idx)/sizeof(thermal_idx[0]);
static int thermals[THERMALNUM];
#endif

static struct cal_result cal_pack;
const char * const support_cmd[] {
	"-c",
	"-m",
	"-s",
	"-d",
};

static void list_cmd(void)
{
	unsigned long i = 0;
	unsigned long cmds = ARRAY_SIZE(support_cmd);

	fprintf(stdout, "support cmd is:\n");

	for (i = 0; i < cmds; i++) {
		fprintf(stdout, "\t%s\n", support_cmd[i]);
	}

	return;
}

static int check_cmd(const char *cmd)
{
	unsigned long i = 0;
	unsigned long cmds = ARRAY_SIZE(support_cmd);

	for (i = 0; i < cmds; i++) {
		if (!strcmp(support_cmd[i], cmd)) {
			return i;
		}
	}

	fprintf(stdout, "%s: no support cmd: %s \n", __func__, cmd);

	//list_cmd();

	return 0;
}

// Check whether calibration files has been created
static int cstool_check_files()
{
	int res = 0;

#if defined(CONFIG_TARGET_PRODUCT_ENUMA) || defined(CONFIG_TARGET_PRODUCT_ELISH) || defined(CONFIG_TARGET_PRODUCT_DAGU)
	fprintf(stdout, "--------enuma check calib files status ------\n");
	// SPK1 & SPK2
	if((access(CALIB_FILE_BIN, F_OK)) == -1) {
		fprintf(stdout, "%s 	  : FAIL, ERROR: %s \n",
				CALIB_FILE_BIN, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s 	  : OK \n", CALIB_FILE_BIN);
	}

	if((access(CALIB_FILE_TXT, F_OK)) == -1) {
		fprintf(stdout, "%s 	  : FAIL, ERROR: %s \n",
				CALIB_FILE_TXT, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s 	  : OK \n", CALIB_FILE_TXT);
	}

	if((access(CALIB_FILE_BIN_RIGHT, F_OK)) == -1) {
		fprintf(stdout, "%s : FAIL, ERROR: %s \n",
				CALIB_FILE_BIN_RIGHT, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s : OK \n", CALIB_FILE_BIN_RIGHT);
	}

	if((access(CALIB_FILE_TXT_RIGHT, F_OK)) == -1) {
		fprintf(stdout, "%s : FAIL, ERROR: %s \n",
				CALIB_FILE_TXT_RIGHT, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s : OK \n", CALIB_FILE_TXT_RIGHT);
	}

	// SPK3 & SPK4
	if((access(CALIB_FILE_BIN2, F_OK)) == -1) {
		fprintf(stdout, "%s 	  : FAIL, ERROR: %s \n",
				CALIB_FILE_BIN2, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s 	  : OK \n", CALIB_FILE_BIN2);
	}

	if((access(CALIB_FILE_TXT2, F_OK)) == -1) {
		fprintf(stdout, "%s 	  : FAIL, ERROR: %s \n",
				CALIB_FILE_TXT2, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s 	  : OK \n", CALIB_FILE_TXT2);
	}

	if((access(CALIB_FILE_BIN_RIGHT2, F_OK)) == -1) {
		fprintf(stdout, "%s : FAIL, ERROR: %s \n",
				CALIB_FILE_BIN_RIGHT2, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s : OK \n", CALIB_FILE_BIN_RIGHT2);
	}

	if((access(CALIB_FILE_TXT_RIGHT2, F_OK)) == -1) {
		fprintf(stdout, "%s : FAIL, ERROR: %s \n",
				CALIB_FILE_TXT_RIGHT2, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s : OK \n", CALIB_FILE_TXT_RIGHT2);
	}

#ifndef CONFIG_TARGET_PRODUCT_DAGU
	// SPK5 & SPK6
	if((access(CALIB_FILE_BIN3, F_OK)) == -1) {
		fprintf(stdout, "%s 	  : FAIL, ERROR: %s \n",
				CALIB_FILE_BIN3, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s 	  : OK \n", CALIB_FILE_BIN3);
	}

	if((access(CALIB_FILE_TXT3, F_OK)) == -1) {
		fprintf(stdout, "%s 	  : FAIL, ERROR: %s \n",
				CALIB_FILE_TXT3, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s 	  : OK \n", CALIB_FILE_TXT3);
	}

	if((access(CALIB_FILE_BIN_RIGHT3, F_OK)) == -1) {
		fprintf(stdout, "%s : FAIL, ERROR: %s \n",
				CALIB_FILE_BIN_RIGHT3, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s : OK \n", CALIB_FILE_BIN_RIGHT3);
	}

	if((access(CALIB_FILE_TXT_RIGHT3, F_OK)) == -1) {
		fprintf(stdout, "%s : FAIL, ERROR: %s \n",
				CALIB_FILE_TXT_RIGHT3, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s : OK \n", CALIB_FILE_TXT_RIGHT3);
	}

	// SPK7 & SPK8
	if((access(CALIB_FILE_BIN4, F_OK)) == -1) {
		fprintf(stdout, "%s 	  : FAIL, ERROR: %s \n",
				CALIB_FILE_BIN4, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s 	  : OK \n", CALIB_FILE_BIN4);
	}

	if((access(CALIB_FILE_TXT4, F_OK)) == -1) {
		fprintf(stdout, "%s 	  : FAIL, ERROR: %s \n",
				CALIB_FILE_TXT4, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s 	  : OK \n", CALIB_FILE_TXT4);
	}

	if((access(CALIB_FILE_BIN_RIGHT4, F_OK)) == -1) {
		fprintf(stdout, "%s : FAIL, ERROR: %s \n",
				CALIB_FILE_BIN_RIGHT, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s : OK \n", CALIB_FILE_BIN_RIGHT4);
	}

	if((access(CALIB_FILE_TXT_RIGHT4, F_OK)) == -1) {
		fprintf(stdout, "%s : FAIL, ERROR: %s \n",
				CALIB_FILE_TXT_RIGHT4, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s : OK \n", CALIB_FILE_TXT_RIGHT4);
	}
#endif

#else
	fprintf(stdout, "--------check calib files status ------\n");
	if((access(CALIB_FILE_BIN, F_OK)) == -1) {
		fprintf(stdout, "%s       : FAIL, ERROR: %s \n",
				CALIB_FILE_BIN, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s       : OK \n", CALIB_FILE_BIN);
	}

	if((access(CALIB_FILE_TXT, F_OK)) == -1) {
		fprintf(stdout, "%s       : FAIL, ERROR: %s \n",
				CALIB_FILE_TXT, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s       : OK \n", CALIB_FILE_TXT);
	}

#if defined(CONFIG_TARGET_PRODUCT_UMI) || defined(CONFIG_TARGET_PRODUCT_CMI) || defined(CONFIG_TARGET_PRODUCT_APOLLO) || defined(CONFIG_TARGET_PRODUCT_CAS) || defined (CONFIG_TARGET_PRODUCT_ALIOTH) || defined(CONFIG_TARGET_PRODUCT_VENUS) || defined(CONFIG_TARGET_PRODUCT_STAR) || defined(CONFIG_TARGET_PRODUCT_HAYDN) || defined(CONFIG_TARGET_PRODUCT_ODIN) || defined(CONFIG_TARGET_PRODUCT_VILI)
	if((access(CALIB_FILE_BIN_RIGHT, F_OK)) == -1) {
		fprintf(stdout, "%s : FAIL, ERROR: %s \n",
				CALIB_FILE_BIN_RIGHT, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s : OK \n", CALIB_FILE_BIN_RIGHT);
	}

	if((access(CALIB_FILE_TXT_RIGHT, F_OK)) == -1) {
		fprintf(stdout, "%s : FAIL, ERROR: %s \n",
				CALIB_FILE_TXT_RIGHT, strerror(errno));
		res = ERR_CHECK_FILES;
	} else {
		fprintf(stdout, "%s : OK \n", CALIB_FILE_TXT_RIGHT);
	}
#endif
#endif
	fprintf(stdout, "-------------------------------------\n\n");

	return res;
}

static void cstool_print_error(int enumber)
{
	if(enumber & ERR_MIXER)
		fprintf(stdout, "diagnostic failed: open mixer failed - ecode: 0x%x\n", enumber);
#ifdef NEED_DIAG_F0
	if(enumber & ERR_F0_RANGE)
		fprintf(stdout, "diagnostic failed: f0 out of range - ecode: 0x%x\n", enumber);
	if(enumber & ERR_F0_STATUS)
		fprintf(stdout, "diagnostic failed: f0 status error - ecode: 0x%x\n", enumber);
#endif
	if(enumber & ERR_Z_RANGE)
		fprintf(stdout, "diagnostic failed: cal z out of range - ecode: 0x%x\n", enumber);
	if(enumber & ERR_Z_STATUS)
		fprintf(stdout, "diagnostic failed: cal z status error - ecode: 0x%x\n", enumber);
	if(enumber & ERR_STORE)
		fprintf(stdout, "diagnostic failed: store cal value error - ecode: 0x%x\n", enumber);
	if(enumber & ERR_CTRLS)
		fprintf(stdout, "diagnostic failed: get/set controls error - ecode: 0x%x\n", enumber);
	if(enumber & ERR_MEDIA_RES)
		fprintf(stdout, "diagnostic failed: get media resource error - ecode: 0x%x\n", enumber);
	if(enumber & ERR_MEDIA_NEW)
		fprintf(stdout, "diagnostic failed: get media handle error - ecode: 0x%x\n", enumber);
	if(enumber & ERR_CHECK_FILES)
		fprintf(stdout, "diagnostic failed: check calib files error - ecode: 0x%x\n", enumber);
	if(enumber == 0)
		fprintf(stdout, "spkcal -c success!\n");

}

static void cstool_print_cal_value(struct cal_result *result)
{
#if defined(CONFIG_TARGET_PRODUCT_ENUMA) || defined(CONFIG_TARGET_PRODUCT_ELISH) || defined(CONFIG_TARGET_PRODUCT_DAGU)
	fprintf(stdout, "\n\n");

	fprintf(stdout, "-------- SPK1 calibraion status ------\n");
	fprintf(stdout, "cal_z	  : %d (%.2f ohm)\n", result->l_calz, Z_TO_OHM(result->l_calz));
	fprintf(stdout, "status   : %d\n", result->l_status);
	fprintf(stdout, "checksum : %d\n", result->l_checksum);
	fprintf(stdout, "-------------------------------------\n\n");
	// show on logcat
	ALOGD("\n\n");
	ALOGD("-------- SPK1 calibraion status ------\n");
	ALOGD("cal_z    : %d (%.2f ohm)\n", result->l_calz, Z_TO_OHM(result->l_calz));
	ALOGD("status   : %d\n", result->l_status);
	ALOGD("checksum : %d\n", result->l_checksum);
	ALOGD("-------------------------------------\n\n");

	fprintf(stdout, "-------- SPK2 calibraion status ------\n");
	fprintf(stdout, "cal_z    : %d (%.2f ohm)\n", result->r_calz, Z_TO_OHM(result->r_calz));
	fprintf(stdout, "status   : %d\n", result->r_status);
	fprintf(stdout, "checksum : %d\n", result->r_checksum);
	fprintf(stdout, "-------------------------------------\n\n");
	// show on logcat
	ALOGD("\n\n");
	ALOGD("-------- SPK2 calibraion status ------\n");
	ALOGD("cal_z    : %d (%.2f ohm)\n", result->r_calz, Z_TO_OHM(result->r_calz));
	ALOGD("status   : %d\n", result->r_status);
	ALOGD("checksum : %d\n", result->r_checksum);
	ALOGD("-------------------------------------\n\n");

	fprintf(stdout, "-------- SPK3 calibraion status ------\n");
	fprintf(stdout, "cal_z	  : %d (%.2f ohm)\n", result->l2_calz, Z_TO_OHM(result->l2_calz));
	fprintf(stdout, "status   : %d\n", result->l2_status);
	fprintf(stdout, "checksum : %d\n", result->l2_checksum);
	fprintf(stdout, "-------------------------------------\n\n");
	// show on logcat
	ALOGD("\n\n");
	ALOGD("-------- SPK3 calibraion status ------\n");
	ALOGD("cal_z    : %d (%.2f ohm)\n", result->l2_calz, Z_TO_OHM(result->l2_calz));
	ALOGD("status   : %d\n", result->l2_status);
	ALOGD("checksum : %d\n", result->l2_checksum);
	ALOGD("-------------------------------------\n\n");

	fprintf(stdout, "-------- SPK4 calibraion status ------\n");
	fprintf(stdout, "cal_z    : %d (%.2f ohm)\n", result->r2_calz, Z_TO_OHM(result->r2_calz));
	fprintf(stdout, "status   : %d\n", result->r2_status);
	fprintf(stdout, "checksum : %d\n", result->r2_checksum);
	fprintf(stdout, "-------------------------------------\n\n");
	// show on logcat
	ALOGD("\n\n");
	ALOGD("-------- SPK4 calibraion status ------\n");
	ALOGD("cal_z    : %d (%.2f ohm)\n", result->r2_calz, Z_TO_OHM(result->r2_calz));
	ALOGD("status   : %d\n", result->r2_status);
	ALOGD("checksum : %d\n", result->r2_checksum);
	ALOGD("-------------------------------------\n\n");

#ifndef CONFIG_TARGET_PRODUCT_DAGU
	fprintf(stdout, "-------- SPK5 calibraion status ------\n");
	fprintf(stdout, "cal_z	  : %d (%.2f ohm)\n", result->l3_calz, Z_TO_OHM(result->l3_calz));
	fprintf(stdout, "status   : %d\n", result->l3_status);
	fprintf(stdout, "checksum : %d\n", result->l3_checksum);
	fprintf(stdout, "-------------------------------------\n\n");
	// show on logcat
	ALOGD("\n\n");
	ALOGD("-------- SPK5 calibraion status ------\n");
	ALOGD("cal_z    : %d (%.2f ohm)\n", result->l3_calz, Z_TO_OHM(result->l3_calz));
	ALOGD("status   : %d\n", result->l3_status);
	ALOGD("checksum : %d\n", result->l3_checksum);
	ALOGD("-------------------------------------\n\n");

	fprintf(stdout, "-------- SPK6 calibraion status ------\n");
	fprintf(stdout, "cal_z    : %d (%.2f ohm)\n", result->r3_calz, Z_TO_OHM(result->r3_calz));
	fprintf(stdout, "status   : %d\n", result->r3_status);
	fprintf(stdout, "checksum : %d\n", result->r3_checksum);
	fprintf(stdout, "-------------------------------------\n\n");
	// show on logcat
	ALOGD("\n\n");
	ALOGD("-------- SPK6 calibraion status ------\n");
	ALOGD("cal_z    : %d (%.2f ohm)\n", result->r3_calz, Z_TO_OHM(result->r3_calz));
	ALOGD("status   : %d\n", result->r3_status);
	ALOGD("checksum : %d\n", result->r3_checksum);
	ALOGD("-------------------------------------\n\n");

	fprintf(stdout, "-------- SPK7 calibraion status ------\n");
	fprintf(stdout, "cal_z	  : %d (%.2f ohm)\n", result->l4_calz, Z_TO_OHM(result->l4_calz));
	fprintf(stdout, "status   : %d\n", result->l4_status);
	fprintf(stdout, "checksum : %d\n", result->l4_checksum);
	fprintf(stdout, "-------------------------------------\n\n");
	// show on logcat
	ALOGD("\n\n");
	ALOGD("-------- SPK7 calibraion status ------\n");
	ALOGD("cal_z    : %d (%.2f ohm)\n", result->l4_calz, Z_TO_OHM(result->l4_calz));
	ALOGD("status   : %d\n", result->l4_status);
	ALOGD("checksum : %d\n", result->l4_checksum);
	ALOGD("-------------------------------------\n\n");

	fprintf(stdout, "-------- SPK8 calibraion status ------\n");
	fprintf(stdout, "cal_z    : %d (%.2f ohm)\n", result->r4_calz, Z_TO_OHM(result->r4_calz));
	fprintf(stdout, "status   : %d\n", result->r4_status);
	fprintf(stdout, "checksum : %d\n", result->r4_checksum);
	fprintf(stdout, "-------------------------------------\n\n");
	// show on logcat
	ALOGD("\n\n");
	ALOGD("-------- SPK8 calibraion status ------\n");
	ALOGD("cal_z    : %d (%.2f ohm)\n", result->r4_calz, Z_TO_OHM(result->r4_calz));
	ALOGD("status   : %d\n", result->r4_status);
	ALOGD("checksum : %d\n", result->r4_checksum);
	ALOGD("-------------------------------------\n\n");
#endif

#else
	fprintf(stdout, "\n\n");
	fprintf(stdout, "--------bottom spk calibraion status ------\n");
	fprintf(stdout, "cal_z    : %d (%.2f ohm)\n", result->l_calz, Z_TO_OHM(result->l_calz));
	fprintf(stdout, "status   : %d\n", result->l_status);
	fprintf(stdout, "checksum : %d\n", result->l_checksum);
#ifdef NEED_DIAG_F0
	fprintf(stdout, "f0       : %d\n", result->l_f0_value);
	fprintf(stdout, "f0 status: %d\n", result->l_f0_status);
	fprintf(stdout, "f0 diff  : %d\n", result->l_f0_low_diff);
#endif
	fprintf(stdout, "-------------------------------------\n\n");
	

	// show on logcat
	ALOGD("\n\n");
	ALOGD("--------bottom spk calibraion status ------\n");
	ALOGD("cal_z    : %d (%.2f ohm)\n", result->l_calz, Z_TO_OHM(result->l_calz));
	ALOGD("status   : %d\n", result->l_status);
	ALOGD("checksum : %d\n", result->l_checksum);
#ifdef NEED_DIAG_F0
	ALOGD("f0       : %d\n", result->l_f0_value);
	ALOGD("f0 status: %d\n", result->l_f0_status);
	ALOGD("f0 diff  : %d\n", result->l_f0_low_diff);
#endif
	ALOGD("-------------------------------------\n\n");
#if defined(CONFIG_TARGET_PRODUCT_UMI) || defined(CONFIG_TARGET_PRODUCT_CMI) || defined(CONFIG_TARGET_PRODUCT_APOLLO) || defined(CONFIG_TARGET_PRODUCT_CAS) || defined (CONFIG_TARGET_PRODUCT_ALIOTH) || defined(CONFIG_TARGET_PRODUCT_VENUS) || defined(CONFIG_TARGET_PRODUCT_STAR) || defined(CONFIG_TARGET_PRODUCT_HAYDN) || defined(CONFIG_TARGET_PRODUCT_ODIN) || defined(CONFIG_TARGET_PRODUCT_VILI)
	fprintf(stdout, "--------top spk calibraion status ------\n");
	fprintf(stdout, "cal_z    : %d (%.2f ohm)\n", result->r_calz, Z_TO_OHM(result->r_calz));
	fprintf(stdout, "status   : %d\n", result->r_status);
	fprintf(stdout, "checksum : %d\n", result->r_checksum);
#ifdef NEED_DIAG_F0
	fprintf(stdout, "f0       : %d\n", result->r_f0_value);
	fprintf(stdout, "f0 status: %d\n", result->r_f0_status);
	fprintf(stdout, "f0 diff  : %d\n", result->r_f0_low_diff);
#endif
	fprintf(stdout, "-------------------------------------\n\n");
	// show on logcat
	ALOGD("\n\n");
	ALOGD("--------top spk calibraion status ------\n");
	ALOGD("cal_z    : %d (%.2f ohm)\n", result->r_calz, Z_TO_OHM(result->r_calz));
	ALOGD("status   : %d\n", result->r_status);
	ALOGD("checksum : %d\n", result->r_checksum);
#ifdef NEED_DIAG_F0
	ALOGD("f0       : %d\n", result->r_f0_value);
	ALOGD("f0 status: %d\n", result->r_f0_status);
	ALOGD("f0 diff  : %d\n", result->r_f0_low_diff);
#endif
	ALOGD("-------------------------------------\n\n");
#endif
#endif
}
// store the calibration to fs node
static int cstool_cal_store(struct cal_result *result)
{
	FILE *fp_bin = NULL;
	FILE *fp_txt = NULL;
	int write_length = 0;

#if defined(CONFIG_TARGET_PRODUCT_ENUMA) || defined(CONFIG_TARGET_PRODUCT_ELISH) || defined(CONFIG_TARGET_PRODUCT_DAGU)
	// To store SPK1 ReDC
	fp_bin = fopen(CALIB_FILE_BIN, "wb+");
	if (fp_bin == NULL) {
		fprintf(stdout, "can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_BIN, errno, strerror(errno));
		return ERR_STORE;
	}
	// Update calibraion result to persist slot
	write_length = fwrite(&result->l_calz, sizeof(int32_t), 1, fp_bin);
	if (write_length <= 0) {
		fprintf(stdout, "can't write calib cal_r to persist slot:\n");
	}
	// Update calibraion result to HAL
	//memcpy(&cal_pack, result, sizeof(struct cal_result));
	fclose(fp_bin);

	fp_txt = fopen(CALIB_FILE_TXT, "w+");
	fprintf(fp_txt, "status = %d, Impedance = %.2f, cal_r = %d, ambient = %d, checksum = %d \n",
			result->l_status, Z_TO_OHM(result->l_calz),
			result->l_calz, result->l_ambient, result->l_checksum);
	fclose(fp_txt);

	// To store SPK2 ReDC
	fp_bin = fopen(CALIB_FILE_BIN_RIGHT, "wb+");
	if (fp_bin == NULL) {
		fprintf(stdout, "can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_BIN_RIGHT, errno, strerror(errno));
		return ERR_STORE;
	}
	write_length = fwrite(&result->r_calz, sizeof(int32_t), 1, fp_bin);
	if (write_length <= 0) {
		fprintf(stdout, "can't write calib cal_r to persist slot:\n");
	}
	fclose(fp_bin);

	fp_txt = fopen(CALIB_FILE_TXT_RIGHT, "w+");
	fprintf(fp_txt, "status = %d, Impedance = %.2f, cal_r = %d, ambient = %d, checksum = %d \n",
			result->r_status, Z_TO_OHM(result->r_calz),
			result->r_calz, result->r_ambient, result->r_checksum);
	fclose(fp_txt);

	// To store SPK3 ReDC
	fp_bin = fopen(CALIB_FILE_BIN2, "wb+");
	if (fp_bin == NULL) {
		fprintf(stdout, "can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_BIN2, errno, strerror(errno));
		return ERR_STORE;
	}
	// Update calibraion result to persist slot
	write_length = fwrite(&result->l2_calz, sizeof(int32_t), 1, fp_bin);
	if (write_length <= 0) {
		fprintf(stdout, "can't write calib cal_r to persist slot:\n");
	}
	// Update calibraion result to HAL
	//memcpy(&cal_pack, result, sizeof(struct cal_result));
	fclose(fp_bin);

	fp_txt = fopen(CALIB_FILE_TXT2, "w+");
	fprintf(fp_txt, "status = %d, Impedance = %.2f, cal_r = %d, ambient = %d, checksum = %d \n",
			result->l2_status, Z_TO_OHM(result->l2_calz),
			result->l2_calz, result->l2_ambient, result->l2_checksum);
	fclose(fp_txt);

	// To store SPK4 ReDC
	fp_bin = fopen(CALIB_FILE_BIN_RIGHT2, "wb+");
	if (fp_bin == NULL) {
		fprintf(stdout, "can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_BIN_RIGHT2, errno, strerror(errno));
		return ERR_STORE;
	}
	write_length = fwrite(&result->r2_calz, sizeof(int32_t), 1, fp_bin);
	if (write_length <= 0) {
		fprintf(stdout, "can't write calib cal_r to persist slot:\n");
	}
	fclose(fp_bin);

	fp_txt = fopen(CALIB_FILE_TXT_RIGHT2, "w+");
	fprintf(fp_txt, "status = %d, Impedance = %.2f, cal_r = %d, ambient = %d, checksum = %d \n",
			result->r2_status, Z_TO_OHM(result->r2_calz),
			result->r2_calz, result->r2_ambient, result->r2_checksum);
	fclose(fp_txt);

#ifndef CONFIG_TARGET_PRODUCT_DAGU
	// To store SPK5 ReDC
	fp_bin = fopen(CALIB_FILE_BIN3, "wb+");
	if (fp_bin == NULL) {
		fprintf(stdout, "can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_BIN3, errno, strerror(errno));
		return ERR_STORE;
	}
	// Update calibraion result to persist slot
	write_length = fwrite(&result->l3_calz, sizeof(int32_t), 1, fp_bin);
	if (write_length <= 0) {
		fprintf(stdout, "can't write calib cal_r to persist slot:\n");
	}
	// Update calibraion result to HAL
	//memcpy(&cal_pack, result, sizeof(struct cal_result));
	fclose(fp_bin);

	fp_txt = fopen(CALIB_FILE_TXT3, "w+");
	fprintf(fp_txt, "status = %d, Impedance = %.2f, cal_r = %d, ambient = %d, checksum = %d \n",
			result->l3_status, Z_TO_OHM(result->l3_calz),
			result->l3_calz, result->l3_ambient, result->l3_checksum);
	fclose(fp_txt);

	// To store SPK6 ReDC
	fp_bin = fopen(CALIB_FILE_BIN_RIGHT3, "wb+");
	if (fp_bin == NULL) {
		fprintf(stdout, "can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_BIN_RIGHT3, errno, strerror(errno));
		return ERR_STORE;
	}
	write_length = fwrite(&result->r3_calz, sizeof(int32_t), 1, fp_bin);
	if (write_length <= 0) {
		fprintf(stdout, "can't write calib cal_r to persist slot:\n");
	}
	fclose(fp_bin);

	fp_txt = fopen(CALIB_FILE_TXT_RIGHT3, "w+");
	fprintf(fp_txt, "status = %d, Impedance = %.2f, cal_r = %d, ambient = %d, checksum = %d \n",
			result->r3_status, Z_TO_OHM(result->r3_calz),
			result->r3_calz, result->r3_ambient, result->r3_checksum);
	fclose(fp_txt);

	// To store SPK7 ReDC
	fp_bin = fopen(CALIB_FILE_BIN4, "wb+");
	if (fp_bin == NULL) {
		fprintf(stdout, "can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_BIN4, errno, strerror(errno));
		return ERR_STORE;
	}
	// Update calibraion result to persist slot
	write_length = fwrite(&result->l4_calz, sizeof(int32_t), 1, fp_bin);
	if (write_length <= 0) {
		fprintf(stdout, "can't write calib cal_r to persist slot:\n");
	}
	// Update calibraion result to HAL
	//memcpy(&cal_pack, result, sizeof(struct cal_result));
	fclose(fp_bin);

	fp_txt = fopen(CALIB_FILE_TXT4, "w+");
	fprintf(fp_txt, "status = %d, Impedance = %.2f, cal_r = %d, ambient = %d, checksum = %d \n",
			result->l4_status, Z_TO_OHM(result->l4_calz),
			result->l4_calz, result->l4_ambient, result->l4_checksum);
	fclose(fp_txt);

	// To store SPK8 ReDC
	fp_bin = fopen(CALIB_FILE_BIN_RIGHT4, "wb+");
	if (fp_bin == NULL) {
		fprintf(stdout, "can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_BIN_RIGHT4, errno, strerror(errno));
		return ERR_STORE;
	}
	write_length = fwrite(&result->r4_calz, sizeof(int32_t), 1, fp_bin);
	if (write_length <= 0) {
		fprintf(stdout, "can't write calib cal_r to persist slot:\n");
	}
	fclose(fp_bin);

	fp_txt = fopen(CALIB_FILE_TXT_RIGHT4, "w+");
	fprintf(fp_txt, "status = %d, Impedance = %.2f, cal_r = %d, ambient = %d, checksum = %d \n",
			result->r4_status, Z_TO_OHM(result->r4_calz),
			result->r4_calz, result->r4_ambient, result->r4_checksum);
	fclose(fp_txt);
#endif

#else
	fp_bin = fopen(CALIB_FILE_BIN, "wb+");
	//fprintf(stdout, "open calib file in %s: \n", __func__);
	if (fp_bin == NULL) {
		fprintf(stdout, "can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_BIN, errno, strerror(errno));
		return ERR_STORE;
	}

	//fprintf(stdout, "write cal_r %d to calib file in %s: \n",
	//		result->l_calz,  __func__);

	// Update calibraion result to persist slot
	write_length = fwrite(&result->l_calz, sizeof(int32_t), 1, fp_bin);
	//fprintf(stdout, "write %d value to calib file in %s: \n",
	//		write_length,  __func__);
	if (write_length <= 0) {
		fprintf(stdout, "can't write calib cal_r to persist slot:\n");
	}

	// Update calibraion result to HAL
	//memcpy(&cal_pack, result, sizeof(struct cal_result));
	fclose(fp_bin);

	fp_txt = fopen(CALIB_FILE_TXT, "w+");
	fprintf(fp_txt, "status = %d, Impedance = %.2f, cal_r = %d, ambient = %d, checksum = %d \n",
			result->l_status, Z_TO_OHM(result->l_calz),
			result->l_calz, result->l_ambient, result->l_checksum);
#ifdef NEED_DIAG_F0
	fprintf(fp_txt, "f0_status = %d, f0 = %d, low_diff = %d\n",
			result->l_f0_status , result->l_f0_value, result->l_f0_low_diff);
#endif
	fclose(fp_txt);
#if defined(CONFIG_TARGET_PRODUCT_UMI) || defined(CONFIG_TARGET_PRODUCT_CMI) || defined(CONFIG_TARGET_PRODUCT_APOLLO) || defined(CONFIG_TARGET_PRODUCT_CAS) || defined (CONFIG_TARGET_PRODUCT_ALIOTH) || defined(CONFIG_TARGET_PRODUCT_VENUS) || defined(CONFIG_TARGET_PRODUCT_STAR) || defined(CONFIG_TARGET_PRODUCT_HAYDN) || defined(CONFIG_TARGET_PRODUCT_ODIN) || defined(CONFIG_TARGET_PRODUCT_VILI)
	fp_bin = fopen(CALIB_FILE_BIN_RIGHT, "wb+");
	if (fp_bin == NULL) {
		fprintf(stdout, "can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_BIN, errno, strerror(errno));
		return ERR_STORE;
	}
	write_length = fwrite(&result->r_calz, sizeof(int32_t), 1, fp_bin);
	if (write_length <= 0) {
		fprintf(stdout, "can't write calib cal_r to persist slot:\n");
	}
	fclose(fp_bin);

	fp_txt = fopen(CALIB_FILE_TXT_RIGHT, "w+");
	fprintf(fp_txt, "status = %d, Impedance = %.2f, cal_r = %d, ambient = %d, checksum = %d \n",
			result->r_status, Z_TO_OHM(result->r_calz),
			result->r_calz, result->r_ambient, result->r_checksum);
#ifdef NEED_DIAG_F0
	fprintf(fp_txt, "f0_status = %d, f0 = %d, low_diff = %d\n",
			result->r_f0_status , result->r_f0_value, result->r_f0_low_diff);
#endif
	fclose(fp_txt);
#endif
#endif

	return 0;
}

static int cstool_cal_show(void)
{
	FILE *fp_txt = NULL;
	char line[100];

#if defined(CONFIG_TARGET_PRODUCT_ENUMA) || defined(CONFIG_TARGET_PRODUCT_ELISH) || defined(CONFIG_TARGET_PRODUCT_DAGU)
	fprintf(stdout, "-------- SPK1 calibraion status ------\n");
	fp_txt = NULL;
	fp_txt = fopen(CALIB_FILE_TXT, "r");
	if (fp_txt == NULL) {
		fprintf(stdout, "need check calib result, can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_TXT, errno, strerror(errno));
		return 0;
	}
	while(fgets(line, 100, fp_txt)) {
		fprintf(stdout, "%s", line);
	}
	fclose(fp_txt);

	fp_txt = NULL;
	fprintf(stdout, "-------- SPK2 calibraion status ------\n");
	fp_txt = fopen(CALIB_FILE_TXT_RIGHT, "r");
	if (fp_txt == NULL) {
		fprintf(stdout, "need check right calib result, can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_TXT_RIGHT, errno, strerror(errno));
		return 0;
	}
	while(fgets(line, 100, fp_txt)) {
		fprintf(stdout, "%s", line);
	}
	fclose(fp_txt);

	fprintf(stdout, "-------- SPK3 calibraion status ------\n");
	fp_txt = NULL;
	fp_txt = fopen(CALIB_FILE_TXT2, "r");
	if (fp_txt == NULL) {
		fprintf(stdout, "need check calib result, can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_TXT2, errno, strerror(errno));
		return 0;
	}
	while(fgets(line, 100, fp_txt)) {
		fprintf(stdout, "%s", line);
	}
	fclose(fp_txt);

	fp_txt = NULL;
	fprintf(stdout, "-------- SPK4 calibraion status ------\n");
	fp_txt = fopen(CALIB_FILE_TXT_RIGHT2, "r");
	if (fp_txt == NULL) {
		fprintf(stdout, "need check right calib result, can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_TXT_RIGHT2, errno, strerror(errno));
		return 0;
	}
	while(fgets(line, 100, fp_txt)) {
		fprintf(stdout, "%s", line);
	}
	fclose(fp_txt);

#ifndef CONFIG_TARGET_PRODUCT_DAGU
	fprintf(stdout, "-------- SPK5 calibraion status ------\n");
	fp_txt = NULL;
	fp_txt = fopen(CALIB_FILE_TXT3, "r");
	if (fp_txt == NULL) {
		fprintf(stdout, "need check calib result, can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_TXT3, errno, strerror(errno));
		return 0;
	}
	while(fgets(line, 100, fp_txt)) {
		fprintf(stdout, "%s", line);
	}
	fclose(fp_txt);

	fp_txt = NULL;
	fprintf(stdout, "-------- SPK6 calibraion status ------\n");
	fp_txt = fopen(CALIB_FILE_TXT_RIGHT3, "r");
	if (fp_txt == NULL) {
		fprintf(stdout, "need check right calib result, can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_TXT_RIGHT3, errno, strerror(errno));
		return 0;
	}
	while(fgets(line, 100, fp_txt)) {
		fprintf(stdout, "%s", line);
	}
	fclose(fp_txt);

	fprintf(stdout, "-------- SPK7 calibraion status ------\n");
	fp_txt = NULL;
	fp_txt = fopen(CALIB_FILE_TXT4, "r");
	if (fp_txt == NULL) {
		fprintf(stdout, "need check calib result, can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_TXT4, errno, strerror(errno));
		return 0;
	}
	while(fgets(line, 100, fp_txt)) {
		fprintf(stdout, "%s", line);
	}
	fclose(fp_txt);

	fp_txt = NULL;
	fprintf(stdout, "-------- SPK8 calibraion status ------\n");
	fp_txt = fopen(CALIB_FILE_TXT_RIGHT4, "r");
	if (fp_txt == NULL) {
		fprintf(stdout, "need check right calib result, can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_TXT_RIGHT4, errno, strerror(errno));
		return 0;
	}
	while(fgets(line, 100, fp_txt)) {
		fprintf(stdout, "%s", line);
	}
	fclose(fp_txt);
#endif

#else
	fprintf(stdout, "--------bottom spk calibraion status ------\n");
	fp_txt = fopen(CALIB_FILE_TXT, "r");

	if (fp_txt == NULL) {
		fprintf(stdout, "need check calib result, can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_TXT, errno, strerror(errno));
		return 0;
	}

	while(fgets(line, 100, fp_txt)) {
		fprintf(stdout, "%s", line);
	}
	fclose(fp_txt);
        fp_txt = NULL;
#if defined(CONFIG_TARGET_PRODUCT_UMI) || defined(CONFIG_TARGET_PRODUCT_CMI) || defined(CONFIG_TARGET_PRODUCT_APOLLO) || defined(CONFIG_TARGET_PRODUCT_CAS) || defined (CONFIG_TARGET_PRODUCT_ALIOTH) || defined(CONFIG_TARGET_PRODUCT_VENUS) || defined(CONFIG_TARGET_PRODUCT_STAR) || defined(CONFIG_TARGET_PRODUCT_HAYDN) || defined(CONFIG_TARGET_PRODUCT_ODIN) || defined(CONFIG_TARGET_PRODUCT_VILI)
	fprintf(stdout, "--------top spk calibraion status ------\n");
	fp_txt = fopen(CALIB_FILE_TXT_RIGHT, "r");
	if (fp_txt == NULL) {
		fprintf(stdout, "need check right calib result, can't open %s, errno = %d reason: %s \n",
				CALIB_FILE_TXT_RIGHT, errno, strerror(errno));
		return 0;
	}

	while(fgets(line, 100, fp_txt)) {
		fprintf(stdout, "%s", line);
	}
	fclose(fp_txt);
        fp_txt = NULL;
#endif
#endif

	return 0;
}

#ifdef MEDIA_PLAY
static int media_play(sp<MediaPlayer> mp, const char *fileName)
{
	mp->reset();
	if (mp->setDataSource(NULL, fileName, NULL) == NO_ERROR) {
		mp->prepare();
	} else {
		fprintf(stdout, "can't get resource from %s\n", fileName);
		return ERR_MEDIA_RES;
	}

	fprintf(stdout, "start playback: %s\n", fileName);

	mp->seekTo(0);
	mp->start();

	return 0;
}
#endif
#if 0
static int cstool_read_params(const char* params, const char* dest)
{
	char *p = NULL;
	char *buff;
	char *sstr = NULL;
	char *sval = NULL;
	int ival = 0;

	buff = (char *)malloc(400);
	strncpy(buff, params, 400);
	p = strtok(buff, ";");

	while(p != NULL) {
		//fprintf(stdout, "1: %s: %s\n", __func__, p);
		if (strstr(p, dest)) {
			sstr = strdup(p);
			//fprintf(stdout, "2: %s: %s\n", __func__, sstr);
			sval = strchr(sstr, '=');
			//fprintf(stdout, "3: %s: %s\n", __func__, sval);
			if (sval) {
				ival = atoi(++sval);
				//fprintf(stdout, "4: %s: %d\n", __func__, ival);
			}
			free(sstr);
			break;
		}
		p = strtok(NULL, ";");
	}

	free(buff);

	return ival;
}
#endif
static int cstool_read_params(const char* params, const char* dest)
{
	char *p = NULL;
	char *buff= NULL;
	char *buff_tmp = NULL;
	char *sstr = NULL;
	char *sval = NULL;
	int ival = 0;

	buff = strdup(params);
	buff_tmp = buff; //save original pointer
	p = strsep(&buff, ";"); //this function will change "buff" pointer addr

	while(p != NULL) {
		//fprintf(stdout, "1: %s: %s\n", __func__, p);
		if (strstr(p, dest)) {
			sstr = strdup(p);
			//fprintf(stdout, "2: %s: %s\n", __func__, sstr);
			sval = strchr(sstr, '=');
			//fprintf(stdout, "3: %s: %s\n", __func__, sval);
			if (sval) {
				ival = atoi(++sval);
				//fprintf(stdout, "4: %s: %d\n", __func__, ival);
			}
			free(sstr);
			break;
		}
		p = strsep(&buff, ";");
	}

	free(buff_tmp);

	return ival;
}
//e_number=0;f0_low_diff=178;f0_status=2;f0_value=861;z_calz=9286;z_checksum=9289;z_status=3
static void cstool_get_params(const char *cmd, struct cal_result *pack)
{
	String8 params = android::AudioSystem::getParameters(String8(cmd));
	const char *str = params.string();

	if (pack) {
#if defined(CONFIG_TARGET_PRODUCT_ENUMA) || defined(CONFIG_TARGET_PRODUCT_ELISH) || defined(CONFIG_TARGET_PRODUCT_DAGU)
		pack->e_number = cstool_read_params(str, "e_number");

		//fprintf(stdout, "SPK1 & SPK2 get params= %s\n", params.string());
		pack->l_status = cstool_read_params(str, "l_status");
		pack->l_calz = cstool_read_params(str, "l_calz");
		pack->l_checksum = cstool_read_params(str, "l_checksum");
		pack->l_ambient = cstool_read_params(str, "l_ambient");
		pack->r_status = cstool_read_params(str, "r_status");
		pack->r_calz = cstool_read_params(str, "r_calz");
		pack->r_checksum = cstool_read_params(str, "r_checksum");
		pack->r_ambient = cstool_read_params(str, "r_ambient");

		//fprintf(stdout, "SPK3 & SPK4 get params= %s\n", params.string());
		pack->l2_status = cstool_read_params(str, "l2_status");
		pack->l2_calz = cstool_read_params(str, "l2_calz");
		pack->l2_checksum = cstool_read_params(str, "l2_checksum");
		pack->l2_ambient = cstool_read_params(str, "l2_ambient");
		pack->r2_status = cstool_read_params(str, "r2_status");
		pack->r2_calz = cstool_read_params(str, "r2_calz");
		pack->r2_checksum = cstool_read_params(str, "r2_checksum");
		pack->r2_ambient = cstool_read_params(str, "r2_ambient");

#ifndef CONFIG_TARGET_PRODUCT_DAGU
		//fprintf(stdout, "SPK5 & SPK6 get params= %s\n", params.string());
		pack->l3_status = cstool_read_params(str, "l3_status");
		pack->l3_calz = cstool_read_params(str, "l3_calz");
		pack->l3_checksum = cstool_read_params(str, "l3_checksum");
		pack->l3_ambient = cstool_read_params(str, "l3_ambient");
		pack->r3_status = cstool_read_params(str, "r3_status");
		pack->r3_calz = cstool_read_params(str, "r3_calz");
		pack->r3_checksum = cstool_read_params(str, "r3_checksum");
		pack->r3_ambient = cstool_read_params(str, "r3_ambient");

		//fprintf(stdout, "SPK7 & SPK8 get params= %s\n", params.string());
		pack->l4_status = cstool_read_params(str, "l4_status");
		pack->l4_calz = cstool_read_params(str, "l4_calz");
		pack->l4_checksum = cstool_read_params(str, "l4_checksum");
		pack->l4_ambient = cstool_read_params(str, "l4_ambient");
		pack->r4_status = cstool_read_params(str, "r4_status");
		pack->r4_calz = cstool_read_params(str, "r4_calz");
		pack->r4_checksum = cstool_read_params(str, "r4_checksum");
		pack->r4_ambient = cstool_read_params(str, "r4_ambient");
#endif
#else
		//fprintf(stdout, "get params= %s\n", params.string());
		pack->e_number = cstool_read_params(str, "e_number");
		pack->l_status = cstool_read_params(str, "l_status");
		pack->l_calz = cstool_read_params(str, "l_calz");
		pack->l_checksum = cstool_read_params(str, "l_checksum");
		pack->l_ambient = cstool_read_params(str, "l_ambient");
#ifdef NEED_DIAG_F0
		pack->l_f0_status = cstool_read_params(str, "l_f0_status");
		pack->l_f0_value = cstool_read_params(str, "l_f0_value");
		pack->l_f0_low_diff = cstool_read_params(str, "l_f0_low_diff");
#endif
#if defined(CONFIG_TARGET_PRODUCT_UMI) || defined(CONFIG_TARGET_PRODUCT_CMI) || defined(CONFIG_TARGET_PRODUCT_APOLLO) || defined(CONFIG_TARGET_PRODUCT_CAS) || defined (CONFIG_TARGET_PRODUCT_ALIOTH) || defined(CONFIG_TARGET_PRODUCT_VENUS) || defined(CONFIG_TARGET_PRODUCT_STAR) || defined(CONFIG_TARGET_PRODUCT_HAYDN) || defined(CONFIG_TARGET_PRODUCT_ODIN) || defined(CONFIG_TARGET_PRODUCT_VILI)
		//fprintf(stdout, "right get params= %s\n", params.string());
		pack->r_status = cstool_read_params(str, "r_status");
		pack->r_calz = cstool_read_params(str, "r_calz");
		pack->r_checksum = cstool_read_params(str, "r_checksum");
		pack->r_ambient = cstool_read_params(str, "r_ambient");
#ifdef NEED_DIAG_F0
		pack->r_f0_status = cstool_read_params(str, "r_f0_status");
		pack->r_f0_value = cstool_read_params(str, "r_f0_value");
		pack->r_f0_low_diff = cstool_read_params(str, "r_f0_low_diff");
#endif
#endif
#endif
	}

	return;
}

static bool cstool_pull_msg(const char *cmd, int msg)
{
	String8 params = android::AudioSystem::getParameters(String8(cmd));
	const char *str = params.string();
	int msg_t = cstool_read_params(str, "message");

	//fprintf(stdout, "wait msg <%d -- %d> \n", msg, msg_t);

	if(msg == msg_t)
		return true;

	return false;
}

static bool cstool_wait_for_msg(int message, int timeout)
{
	bool ret = false;
	int period = 200000; //us

	while(timeout-=period) {
		ret = cstool_pull_msg(CMD_PARAMS_CAL_MSG, message);
		if(ret == true) {
			//fprintf(stdout, "got message <%d>\n", message);
			break;
		} else {
			usleep(period);
		}
	}

	if (ret == false) {
		fprintf(stdout, "can't get message <%d>\n", message);
	}

	return ret;
}


static void cstool_set_params(const char *cmd)
{
	android::AudioSystem::setParameters(String8(cmd));

	return;
}


static bool cstool_set_params_wait(const char *cmd, int message)
{
	android::AudioSystem::setParameters(String8(cmd));

	if (message == MSG_RET_NONE)
		return true;

	return cstool_wait_for_msg(message, WAIT_TIMEOUT);
}
static void cstool_run_calibration(void)
{

	int trys = 3;
	bool ret = false;

#ifdef NEED_DIAG_F0
		cstool_set_params("diag_f0=true");
#else
		cstool_set_params("diag_f0=false");
#endif

#ifdef MEDIA_PLAY
#ifdef TARGET_PRODUCT_DRACO
	cstool_set_params("cal_rcv=true");
#endif
	sp<MediaPlayer> mplay = NULL;
	mplay = new MediaPlayer();
	if (mplay == NULL) {
		fprintf(stdout, "failed to create MediaPlayer\n");
		cal_pack.e_number = ERR_MEDIA_NEW;
		goto exit;
	}
#endif
	while (trys--) {
		fprintf(stdout, "trys 3, %d time left\n", trys);

		ret = cstool_set_params_wait("cal_start=wait", MSG_INIT_DONE);
		if(ret == false)
			continue;
		ret = cstool_set_params_wait("cal_diag_fw=wait", MSG_DIAG_FW_DONE);
		if(ret == false)
			continue;
#ifdef MEDIA_PLAY
		media_play(mplay, "/vendor/etc/cs35l41_cal.wav");
		usleep(1500000);
		ret = cstool_set_params_wait("cal_chkval=wait", MSG_VALUE_DONE);
		if(ret == false)
			continue;
		mplay->stop();
#else
		system("tinyplay /vendor/etc/cs35l41_cal.wav");
#endif

		cstool_get_params(CMD_PARAMS_GET_VALUE, &cal_pack);
		if (cal_pack.e_number)
			continue;

		cstool_cal_store(&cal_pack);
		break;
	}

	cstool_print_cal_value(&cal_pack);

#ifdef MEDIA_PLAY
	cstool_set_params_wait("cal_scheck=wait", MSG_STREAM_CLOSED);
#endif
	cstool_set_params_wait("cal_def_fw=wait", MSG_DEF_FW_DONE);
	cstool_set_params_wait("cal_end=nowait", MSG_RET_NONE);
#ifdef MEDIA_PLAY
exit:
#ifdef TARGET_PRODUCT_DRACO
	cstool_set_params("cal_rcv=false");
#endif
#endif

	cal_pack.e_number |= cstool_check_files();
	cstool_print_error(cal_pack.e_number);
	return;
}

#if defined(CONFIG_TARGET_PRODUCT_CAS) || defined(CONFIG_TARGET_PRODUCT_APOLLO) || defined (CONFIG_TARGET_PRODUCT_ALIOTH) || defined(CONFIG_TARGET_PRODUCT_VENUS) || defined(CONFIG_TARGET_PRODUCT_STAR) || defined(CONFIG_TARGET_PRODUCT_HAYDN) || defined(CONFIG_TARGET_PRODUCT_ODIN) || defined(CONFIG_TARGET_PRODUCT_VILI)
int get_thermals()
{
	FILE *fp_get = NULL;
	char result[8];

	ALOGD("%s: enter ", __func__);
	for(int i = 0; i < THERMALNUM; i++){
		char *path = (char *)malloc(strlen(THERMALSNS) - 2 + sizeof(thermal_idx[i]) + 1);

		sprintf(path, THERMALSNS, thermal_idx[i]);
		fp_get = fopen(path, "r");
		if(fp_get == NULL){
			ALOGE("%s: can not open %s", __func__, path);
			if (path)
				free(path);
			return -1;
		}else{
			fgets(result, 8, fp_get);
			thermals[i] = atoi(result);
		}
		fclose(fp_get);
		free(path);
	}
	ALOGD("%s: leave ", __func__);
	return 0;
}

int save_thermals()
{
	FILE *fp_save = NULL;
	time_t tick;
	struct tm tm;
	char s[20];

	ALOGD("%s: enter", __func__);
	tick = time(NULL);
	tm = *localtime(&tick);
	strftime(s, sizeof(s), "%Y%m%d%H%M%S", &tm);
	char *path = (char*)malloc(strlen(THERMALTXT) - 2 + sizeof(s) +1);
	sprintf(path, THERMALTXT, s);
	fp_save = fopen(path, "w+");
	if(fp_save == NULL){
		if (path)
			free(path);
		return -1;
	}else{
		fprintf(fp_save, "index \t thermal \n");
		for(int i = 0; i < THERMALNUM; i++)
			fprintf(fp_save, "%-5d \t %.3f \n", thermal_idx[i], (float)thermals[i]/1000);
	}
	fclose(fp_save);
	if (path)
		free(path);

	ALOGD("%s: leave", __func__);
	return 0;
}
#endif

#ifdef TARGET_PRODUCT_DRACO
int spkcal_crus(int argc, const char *argv[], int nDev)
#else
int main(int argc, char **argv)
#endif
{
	char cmd[128] = {0};
	int ret = 0;
	String8 param;

	if (argc != 2) {
		fprintf(stdout, "Usage: %s {command}\n", argv[0]);
		list_cmd();
		return 1;
	}

	if (check_cmd(argv[1]) < 0) {
		return 1;
	}
#ifdef TARGET_PRODUCT_DRACO
	ALOGE("spkcal on Device %d", nDev);
#endif
#if defined(CONFIG_TARGET_PRODUCT_CAS) || defined(CONFIG_TARGET_PRODUCT_APOLLO) || defined (CONFIG_TARGET_PRODUCT_ALIOTH) || defined(CONFIG_TARGET_PRODUCT_VENUS) || defined(CONFIG_TARGET_PRODUCT_STAR) || defined(CONFIG_TARGET_PRODUCT_HAYDN) || defined(CONFIG_TARGET_PRODUCT_ODIN) || defined(CONFIG_TARGET_PRODUCT_VILI)
	ALOGD("%s: get and save thermals", __func__);
	get_thermals();
	save_thermals();
#endif

	if (!strncmp(argv[1], "-c", 2)) {
		sprintf(cmd, "%s", argv[1]);
		fprintf(stdout, "execute: %s\n", cmd);
		cstool_run_calibration();
	} else if (!strncmp(argv[1], "-m", 2)) {
		sprintf(cmd, "%s", argv[1]);
		fprintf(stdout, "execute: %s\n", cmd);
		cstool_cal_show();
	} else if (!strncmp(argv[1], "-d", 2)) {
		sprintf(cmd, "%s", argv[1]);
		fprintf(stdout, "execute: %s\n", cmd);
	} else {
		sprintf(cmd, "cirrus_sp=%s", argv[1]);
		fprintf(stdout, "execute: %s\n", cmd);
		//android::AudioSystem::setParameters(String8(cmd));
	}

	return ret;
}
