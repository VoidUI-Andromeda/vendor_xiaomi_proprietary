/**
 * @file		dev_detector.h
 * @brief
 * @details
 * @author
 * @date        2019.07.03
 * @version		0.1
 * @note
 * @warning
 * @par			History:
 *
 */

#ifndef __DEV_DETECTOR_H__
#define __DEV_DETECTOR_H__
#include "dev_type.h"

typedef struct __Dev_Detector Dev_Detector;
struct __Dev_Detector
{
    S64 (*Init)(void);
    S64 (*Uninit)(void);
    S64 (*Create)(void);
    S64 (*Destroy)(S64 *id);
    S64 (*Begin)(S64 id);
    S64 (*End)(S64 id, const char *str);
    S64 (*Reset)(S64 id);
    S64 (*Fps)(S64 id, const char *str);
};

extern const Dev_Detector m_dev_detector;

#endif // __DEV_DETECTOR_H__
