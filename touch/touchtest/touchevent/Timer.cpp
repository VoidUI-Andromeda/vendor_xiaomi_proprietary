/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Timer.h"
#include <string.h>
#include <utils/Log.h>
#include <utils/String8.h>
#include "TouchMain.h"

Timer::Timer() {
  mTimerId = 0;
  mCb = NULL;
}

bool Timer::set(int us, TIMER_FUNC cb) {
  if (mTimerId == 0) {
    if (cb == NULL) return false;

    if (!create(cb)) return false;
  }
  if (cb != mCb) {
    kill();
    if (!create(cb)) return false;
  }

  int stat = 0;
  struct itimerspec ts;
  ts.it_value.tv_sec = us / 1000000;
  ts.it_value.tv_nsec = (us % 1000000) * 1000;

  ts.it_interval.tv_sec = 0;
  ts.it_interval.tv_nsec = 0;

  stat = timer_settime(mTimerId, 0, &ts, 0);
  if (stat == -1)
    ALOGE("fail set timer");
  return stat == 0;
}

bool Timer::set(int us, int interval, TIMER_FUNC cb) {
  if (mTimerId == 0) {
    if (cb == NULL) return false;

    if (!create(cb)) return false;
  }
  if (cb != mCb) {
    kill();
    if (!create(cb)) return false;
  }

  int stat = 0;
  struct itimerspec ts;
  ts.it_value.tv_sec = us / 1000000;
  ts.it_value.tv_nsec = (us % 1000000) * 1000;

  ts.it_interval.tv_sec = interval / 1000000;
  ts.it_interval.tv_nsec = (interval % 1000000) * 1000;

  stat = timer_settime(mTimerId, 0, &ts, 0);
  if (stat == -1)
    ALOGE("fail set timer");
  return stat == 0;
}

bool Timer::stop() {
  if (mTimerId == 0 || mCb == NULL) {
    return false;
  }

  int stat = 0;
  struct itimerspec ts;
  ts.it_value.tv_sec = 0;
  ts.it_value.tv_nsec = 0;

  ts.it_interval.tv_sec = 0;
  ts.it_interval.tv_nsec = 0;

  stat = timer_settime(mTimerId, 0, &ts, 0);
  if (stat == -1)
    ALOGE("fail set timer");
  return stat == 0;
}

Timer::~Timer() { kill(); }

void Timer::kill() {
  if (mTimerId == 0) return;

  timer_delete(mTimerId);
  mTimerId = 0;
  mCb = NULL;
}

bool Timer::create(TIMER_FUNC cb) {
  struct sigevent se;
  memset(&se, 0, sizeof(struct sigevent));
  int stat = 0;

  /*
   * Set the sigevent structure to cause the signal to be
   * delivered by creating a new thread.
   */
  se.sigev_notify = SIGEV_THREAD;
  se.sigev_value.sival_ptr = &mTimerId;
  se.sigev_notify_function = cb;
  se.sigev_notify_attributes = NULL;
  mCb = cb;
  stat = timer_create(CLOCK_MONOTONIC, &se, &mTimerId);
  if (stat == -1)
    ALOGE("fail create timer");
  return stat == 0;
}

bool Timer::isRunning(void) {
  if (mTimerId == 0) return false;

  int stat = 0;
  struct itimerspec ts;

  stat = timer_gettime(mTimerId, &ts);
  if (stat != 0) return false;
  return ((ts.it_value.tv_sec > 0 || ts.it_value.tv_nsec > 0) ? true : false);
}
