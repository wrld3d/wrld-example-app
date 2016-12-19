// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "IndoorAtlasLocationModule.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"
#include "IndoorAtlasLocationManager.h"
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
                                                             AndroidNativeState& nativeState,
                                                             ExampleAppMessaging::TMessageBus& messageBus)
        : m_pLocationController(NULL)
        , m_pLocationManager(NULL)
        , m_pLocationService(NULL)
        {
            m_pLocationService = Eegeo_NEW(IndoorAtlasLocationService)(defaultLocationService,
                                                                       environmentFlatteningService,
                                                                       interiorInteractionModel,
                                                                       messageBus);
            
            m_pLocationManager = Eegeo_NEW(ExampleApp::IndoorAtlas::View::IndoorAtlasLocationManager)(m_pLocationService, nativeState, messageBus);

            m_pLocationController = Eegeo_NEW(IndoorAtlasLocationController)(*m_pLocationManager,
                                                                             appModeModel,
                                                                             interiorInteractionModel,
                                                                             interiorSelectionModel,
																			 applicationConfiguration);
        }
        
        IndoorAtlasLocationModule::~IndoorAtlasLocationModule()
        {
            Eegeo_DELETE m_pLocationController;
            m_pLocationController = NULL;
            
            Eegeo_DELETE m_pLocationManager;
            m_pLocationManager = NULL;
            
            Eegeo_DELETE m_pLocationService;
            m_pLocationService = NULL;
        }
    }
}
