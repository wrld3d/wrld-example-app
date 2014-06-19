// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef LOGGER_H_
#define LOGGER_H_

#include "Types.h"

#if defined(EEGEO_DROID)
#include <android/log.h>
#define EXAMPLE_LOG(...) __android_log_print(ANDROID_LOG_INFO,"Eegeo_Examples",__VA_ARGS__)
#else
#define EXAMPLE_LOG(...) printf(__VA_ARGS__)
#endif

#endif /* LOGGER_H_ */
