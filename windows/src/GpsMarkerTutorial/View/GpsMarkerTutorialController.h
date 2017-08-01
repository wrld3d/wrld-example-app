// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "GpsMarkerTutorialViewIncludes.h"
#include "CompassModeChangedMessage.h"
#include "Location.h"
#include "GpsMarker.h"

namespace ExampleApp
{
	namespace GpsMarkerTutorial
	{
		namespace View
		{
			class GpsMarkerTutorialController : private Eegeo::NonCopyable
			{
			public:
				GpsMarkerTutorialController(GpsMarkerTutorialView& gpsMarkerTutorialView,
                                            ExampleAppMessaging::TMessageBus& messageBus,
                                            const GpsMarker::SdkModel::GpsMarkerModel& gpsMarkerModel,
                                            Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService);
				~GpsMarkerTutorialController();

				void UpdateScreenLocation(const Eegeo::Camera::RenderCamera& renderCamera,
                                          const float screenOversampleScale);

			private:
				GpsMarkerTutorialView& m_gpsMarkerTutorialView;

				ExampleAppMessaging::TMessageBus& m_messageBus;

				AppModes::SdkModel::AppMode m_currAppMode;
				bool m_shouldShowTutorial;
				bool m_isInInterior;
				Eegeo::dv3 m_oldCameraPosition;
				bool m_cameraIsMoving;
				ExampleApp::Compass::GpsMode::Values m_oldGpsMode;

				const GpsMarker::SdkModel::GpsMarkerModel& m_gpsMarkerModel;
				Eegeo::dv3 m_markerLocationEcef;
				Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;

				Eegeo::dv3 GetScaledMarkerPoint();

				Eegeo::Helpers::TCallback1<GpsMarkerTutorialController, const ExampleApp::Compass::CompassModeChangedMessage&> m_compassModeChangedHandler;
				void OnCompassModeChangedMessage(const ExampleApp::Compass::CompassModeChangedMessage& message);

				Eegeo::Helpers::TCallback1<GpsMarkerTutorialController, const AppModes::AppModeChangedMessage&> m_appModeChangedHandler;
				void OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message);

				Eegeo::Helpers::TCallback1<GpsMarkerTutorialController, const InteriorsExplorer::InteriorsExplorerStateChangedMessage&> m_interiorStateChangedCallback;
				void OnInteriorStateChanged(const InteriorsExplorer::InteriorsExplorerStateChangedMessage& message);
			};
		}
	}
}