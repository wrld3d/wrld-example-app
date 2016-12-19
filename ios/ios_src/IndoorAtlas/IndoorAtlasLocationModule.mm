// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "IndoorAtlasLocationModule.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"
#include "IndoorAtlasLocationManagerInterop.h"
#include <map>
#include <string>

namespace ExampleApp
{
    namespace IndoorAtlas
    {
        IndoorAtlasLocationModule::IndoorAtlasLocationModule(ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                             Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                             const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                             const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                             const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
                                                             Eegeo::Location::ILocationService& defaultLocationService,
                                                             ExampleApp::ExampleAppMessaging::TMessageBus& messageBus)
        : m_pLocationController(NULL)
        , m_pLocationManager(NULL)
        , m_pLocationService(NULL)
        {
            m_pLocationService = Eegeo_NEW(IndoorAtlasLocationService)(defaultLocationService,
                                                                       environmentFlatteningService,
                                                                       interiorInteractionModel,
                                                                       messageBus);
            
            m_pLocationManager = [[IndoorAtlasLocationManager alloc] Init: m_pLocationService ndMessageBus: messageBus];
            
            m_pLocationController = Eegeo_NEW(IndoorAtlasLocationController)(*[m_pLocationManager getInterop],
                                                                             appModeModel,
                                                                             interiorInteractionModel,
                                                                             interiorSelectionModel,
                                                                             applicationConfiguration);
        }
        
        IndoorAtlasLocationModule::~IndoorAtlasLocationModule()
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