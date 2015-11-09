// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WindowsAppThreadAssertions.h"

#define ASSERT_UI_THREAD //ExampleApp::WindowsAppThreadAssertions::AssertCurrentlyRunningOnNominatedUiThread(__FILE__, __LINE__);

#define ASSERT_NATIVE_THREAD //ExampleApp::WindowsAppThreadAssertions::AssertCurrentlyRunningOnNominatedNativeThread(__FILE__, __LINE__);
