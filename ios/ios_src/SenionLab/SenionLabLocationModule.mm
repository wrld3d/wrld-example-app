// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SenionLabLocationModule.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"
#include <map>
#include <string>
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace SenionLab
    {
        SenionLabLocationModule::SenionLabLocationModule(ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                         Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                         const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                         const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                         Eegeo::Location::ILocationService& defaultLocationService,
                                                         Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository,
                                                         Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory& iOSAlertBoxFactory,
                                                         ExampleAppMessaging::TMessageBus& messageBus)
        : m_locationService(defaultLocationService, environmentFlatteningService, interiorInteractionModel)
        , m_locationManager(m_locationService, iOSAlertBoxFactory, messageBus)
        , m_locationController(m_locationManager,
                               appModeModel,
                               interiorSelectionModel,
                               interiorMetaDataRepository,
                               messageBus)
        {
        }
        
        SenionLabLocationModule::~SenionLabLocationModule()
        {
        }
    }
}
