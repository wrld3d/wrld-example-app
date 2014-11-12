// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CompassViewModule.h"
#include "CompassViewController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
namespace Compass
{
CompassViewModule::CompassViewModule(
    AndroidNativeState& nativeState,
    Compass::ICompassViewModel& viewModel,
    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
    ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus
)
{
	ASSERT_UI_THREAD

	m_pController = Eegeo_NEW(CompassViewController)(
	                    nativeState,
	                    viewModel,
	                    uiToNativeMessageBus,
	                    nativeToUiMessageBus);
}

CompassViewModule::~CompassViewModule()
{
	ASSERT_UI_THREAD

	Eegeo_DELETE m_pController;
}
}
}
