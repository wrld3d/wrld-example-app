// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "GpsMarkerTutorialViewModule.h"

namespace ExampleApp
{
	namespace GpsMarkerTutorial
	{
		namespace View
		{
			GpsMarkerTutorialViewModule::GpsMarkerTutorialViewModule(WindowsNativeState& nativeState,
                                                                     ExampleAppMessaging::TMessageBus& messageBus,
                                                                     const GpsMarker::SdkModel::GpsMarkerModel& gpsMarkerModel,
                                                                     Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService)
			{
				m_pView = Eegeo_NEW(GpsMarkerTutorialView)();

				m_pController = Eegeo_NEW(GpsMarkerTutorialController)(*m_pView,
                                                                       messageBus,
                                                                       gpsMarkerModel,
                                                                       environmentFlatteningService);
			}

			GpsMarkerTutorialViewModule::~GpsMarkerTutorialViewModule()
			{
				Eegeo_DELETE m_pView;

				Eegeo_DELETE m_pController;
			}

			GpsMarkerTutorialController& GpsMarkerTutorialViewModule::GetController()
			{
				return *m_pController;
			}
		}
	}
}