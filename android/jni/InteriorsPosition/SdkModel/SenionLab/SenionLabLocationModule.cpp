// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "AndroidAppThreadAssertionMacros.h"
#include "AndroidNativeState.h"
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
                SenionLabLocationModule::SenionLabLocationModule(ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                 Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                 const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                 const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                                 Eegeo::Location::ILocationService& defaultLocationService,
                                                                 Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository,
                                                                 ExampleAppMessaging::TMessageBus& messageBus,
                                                                 AndroidNativeState& nativeState)
                : m_locationService(defaultLocationService,
                                    environmentFlatteningService,
                                    interiorInteractionModel)
                , m_locationManager(m_locationService, messageBus, nativeState)
                , m_locationController(m_locationManager,
                                       appModeModel,
                                       interiorSelectionModel,
                                       interiorMetaDataRepository,
                                       messageBus)
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
