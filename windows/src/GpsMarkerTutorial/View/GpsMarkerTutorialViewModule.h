// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "GpsMarkerTutorialView.h"
#include "GpsMarkerTutorialController.h"

namespace ExampleApp
{
	namespace GpsMarkerTutorial
	{
		namespace View
		{
			class GpsMarkerTutorialViewModule: private Eegeo::NonCopyable
			{
			private:
				GpsMarkerTutorialView* m_pView;
				GpsMarkerTutorialController* m_pController;

			public:
				GpsMarkerTutorialViewModule(WindowsNativeState& nativeState,
                                            ExampleAppMessaging::TMessageBus& messageBus,
                                            const GpsMarker::SdkModel::GpsMarkerModel& gpsMarkerModel,
                                            Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService);

				~GpsMarkerTutorialViewModule();

				GpsMarkerTutorialController& GetController();
			};
		}
	}
}