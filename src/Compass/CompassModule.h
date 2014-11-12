// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Compass.h"
#include "ICompassModule.h"
#include "Rendering.h"
#include "GlobeCamera.h"
#include "IIdentity.h"
#include "Location.h"
#include "CompassModeObserver.h"
#include "CompassViewCycledObserver.h"
#include "NativeToUiMessageBus.h"
#include "UiToNativeMessageBus.h"

namespace ExampleApp
{
namespace Compass
{
class CompassModule : public ICompassModule, private Eegeo::NonCopyable
{
private:
	CompassViewModel* m_pViewModel;
	ICompassModel* m_pModel;
	ICompassUpdateController* m_pCompassUpdateController;
	CompassModeObserver* m_pCompassModeObserver;
	CompassViewCycledObserver* m_pCompassViewCycledObserver;

public:
	CompassModule(Eegeo::Location::NavigationService& navigationService,
	              Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& cameraController,
	              Eegeo::Helpers::IIdentityProvider& identityProvider,
	              ExampleApp::ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
	              ExampleApp::ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus
	             );

	~CompassModule();

	ICompassModel& GetCompassModel() const;

	ICompassViewModel& GetCompassViewModel() const;

	ICompassUpdateController& GetCompassUpdateController() const;

	ScreenControlViewModel::IScreenControlViewModel& GetScreenControlViewModel() const;
};

}
}
