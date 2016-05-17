// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AndroidAppThreadAssertions.h"

#define ASSERT_UI_THREAD ExampleApp::AndroidAppThreadAssertions::AssertCurrentlyRunningOnNominatedUiThread(__FILE__, __LINE__);

#define ASSERT_NATIVE_THREAD ExampleApp::AndroidAppThreadAssertions::AssertCurrentlyRunningOnNominatedNativeThread(__FILE__, __LINE__);
