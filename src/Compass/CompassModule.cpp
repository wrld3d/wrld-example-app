// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CompassModule.h"
#include "CompassViewModel.h"
#include "CompassModel.h"
#include "CompassUpdateController.h"

namespace ExampleApp
{
	namespace Compass
	{
		CompassModule::CompassModule(Eegeo::Location::NavigationService& navigationService,
		                             Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& cameraController,
		                             Eegeo::Helpers::IIdentityProvider& identityProvider,
		                             ExampleApp::ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
		                             ExampleApp::ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus
		                            )
		{
			m_pModel = Eegeo_NEW(CompassModel)(navigationService, cameraController);
			m_pViewModel = Eegeo_NEW(CompassViewModel)(identityProvider.GetNextIdentity(), false);
			m_pCompassUpdateController = Eegeo_NEW(CompassUpdateController)(*m_pModel, navigationService, nativeToUiMessageBus);
			m_pCompassModeObserver = Eegeo_NEW(CompassModeObserver)(*m_pModel, nativeToUiMessageBus);
			m_pCompassViewCycledObserver = Eegeo_NEW(CompassViewCycledObserver)(*m_pModel, uiToNativeMessageBus);
		}

		CompassModule::~CompassModule()
		{
			Eegeo_DELETE m_pCompassViewCycledObserver;
			Eegeo_DELETE m_pCompassModeObserver;
			Eegeo_DELETE m_pCompassUpdateController;
			Eegeo_DELETE m_pViewModel;
			Eegeo_DELETE m_pModel;
		}

		ICompassModel& CompassModule::GetCompassModel() const
		{
			return *m_pModel;
		}

		ICompassViewModel& CompassModule::GetCompassViewModel() const
		{
			return *m_pViewModel;
		}

		ICompassUpdateController& CompassModule::GetCompassUpdateController() const
		{
			return *m_pCompassUpdateController;
		}

		ScreenControlViewModel::IScreenControlViewModel& CompassModule::GetScreenControlViewModel() const
		{
			return m_pViewModel->GetScreenControlViewModel();
		}
	}
}
