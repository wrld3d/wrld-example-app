/*
 * Logger.h
 *
 *  Created on: Nov 6, 2013
 *      Author: kimbleoperations
 */

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
