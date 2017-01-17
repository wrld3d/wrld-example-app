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
                                                         const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
                                                         Eegeo::Location::ILocationService& defaultLocationService,
                                                         ExampleAppMessaging::TMessageBus& messageBus)
        : m_pLocationController(NULL)
        , m_pLocationManager(NULL)
        , m_pLocationService(NULL)
        {
            m_pLocationService = Eegeo_NEW(SenionLabLocationService)(defaultLocationService,
                                                                     environmentFlatteningService,
                                                                     interiorInteractionModel);
            m_pLocationManager = [[SenionLabLocationManager alloc] Init: m_pLocationService messageBus: &messageBus];
            
            m_pLocationController = Eegeo_NEW(SenionLabLocationController)(*m_pLocationManager,
                                                                           appModeModel,
                                                                           interiorSelectionModel,
                                                                           applicationConfiguration,
                                                                           messageBus);
        }
        
        SenionLabLocationModule::~SenionLabLocationModule()
        {
            Eegeo_DELETE m_pLocationController;
            m_pLocationController = NULL;
            
            [m_pLocationManager release];
            m_pLocationManager = NULL;
            
            Eegeo_DELETE m_pLocationService;
            m_pLocationService = NULL;
        }
    }
}