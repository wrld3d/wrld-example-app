// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include <utility>

#include "AndroidAppThreadAssertionMacros.h"
#include "AndroidNativeState.h"
#include "ApplicationConfiguration.h"
#include "BidirectionalBus.h"
#include "InteriorInteractionModel.h"
#include "InteriorSelectionModel.h"
#include "SenionLabLocationModule.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                SenionLabLocationModule::SenionLabLocationModule(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                 const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                                 Eegeo::Location::ILocationService& defaultLocationService,
                                                                 const std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& trackingInfoMap,
                                                                 ExampleAppMessaging::TMessageBus& messageBus,
                                                                 AndroidNativeState& nativeState)
                : m_locationService(defaultLocationService,
                                    environmentFlatteningService,
                                    interiorInteractionModel)
                , m_locationManager(m_locationService, messageBus, nativeState)
                , m_locationController(m_locationManager,
                                       trackingInfoMap)
                {
                    ASSERT_NATIVE_THREAD
                }

                SenionLabLocationModule::~SenionLabLocationModule()
                {
                    ASSERT_NATIVE_THREAD
                }
            }
        }
    }
}
