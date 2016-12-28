// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SenionLabLocationModule.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"
#include <map>
#include <string>

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
                                                         ExampleApp::ExampleAppMessaging::TMessageBus& messageBus,
                                                         AndroidNativeState& nativeState)
        : m_pLocationController(NULL)
        , m_pLocationManager(NULL)
        , m_pLocationService(NULL)
        {
            m_pLocationService = Eegeo_NEW(SenionLabLocationService)(defaultLocationService,
                                                                     environmentFlatteningService,
                                                                     interiorInteractionModel,
																	 messageBus);

            m_pLocationManager = Eegeo_NEW(View::SenionLabLocationManager)(m_pLocationService,
                                                                           messageBus,
                                                                           nativeState);

            m_pLocationController = Eegeo_NEW(SenionLabLocationController)(appModeModel,
                                                                           interiorSelectionModel,
                                                                           interiorMetaDataRepository,
                                                                           messageBus);
        }
        
        SenionLabLocationModule::~SenionLabLocationModule()
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
