/*
 * Copyright (C) 2017 The Android Open Source Project
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

#define LOG_TAG "android.hardware.power@1.1-service.rpi4"

#include <android/log.h>
#include <hidl/HidlTransportSupport.h>
#include <hardware/power.h>
#include "Power.h"

using android::sp;
using android::status_t;
using android::OK;

// libhwbinder:
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;

// Generated HIDL files
using android::hardware::power::V1_1::IPower;
using android::hardware::power::V1_1::implementation::Power;

int main() {

    status_t status;
    android::sp<IPower> service = nullptr;

    ALOGI("starting");

    service = new Power();
    if (service == nullptr) {
        ALOGE("Can not create an instance of Power HAL Iface, exiting.");

        goto shutdown;
    }

    configureRpcThreadpool(1, true /*callerWillJoin*/);

    status = service->registerAsService();
    if (status != OK) {
        ALOGE("Could not register service for Power HAL Iface (%d).", status);
        goto shutdown;
    }

    ALOGI("ready");
    joinRpcThreadpool();
    //Should not pass this line

shutdown:
    // In normal operation, we don't expect the thread pool to exit

    return 1;
}
