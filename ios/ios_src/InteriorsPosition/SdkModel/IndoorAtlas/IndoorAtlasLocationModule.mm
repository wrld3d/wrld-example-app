// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "IndoorAtlasLocationModule.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"
#include "IndoorAtlasLocationController.h"
#include "IndoorAtlasLocationService.h"
#include "IndoorAtlasLocationInterop.h"

#include <map>
#include <string>

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace IndoorAtlas
            {
                IndoorAtlasLocationModule::IndoorAtlasLocationModule(ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                     Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                     const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                     const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                                     Eegeo::Location::ILocationService& defaultLocationService,
                                                                     Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository,
                                                                     ExampleAppMessaging::TMessageBus& messageBus)
                : m_pIndoorAtlasLocationInterop(nullptr)
                , m_pLocationService(nullptr)
                , m_pLocationController(nullptr)
                {
                    m_pIndoorAtlasLocationInterop = Eegeo_NEW(IndoorAtlasLocationInterop)();
                    
                    m_pLocationService = Eegeo_NEW(IndoorAtlasLocationService)(*m_pIndoorAtlasLocationInterop,
                                                                               defaultLocationService,
                                                                               messageBus,
                                                                               environmentFlatteningService,
                                                                               interiorInteractionModel,
                                                                               interiorSelectionModel,
                                                                               interiorMetaDataRepository);
                    
                    m_pIndoorAtlasLocationInterop->SetLocationService(m_pLocationService);
                    
                    m_pLocationController = Eegeo_NEW(IndoorAtlasLocationController)(*m_pLocationService,
                                                                                     appModeModel,
                                                                                     interiorSelectionModel,
                                                                                     interiorMetaDataRepository);
                }
        
                IndoorAtlasLocationModule::~IndoorAtlasLocationModule()
                {
                    Eegeo_DELETE m_pLocationController;
                    m_pLocationController = nullptr;
                    
                    Eegeo_DELETE m_pLocationService;
                    m_pLocationService = nullptr;
                    
                    Eegeo_DELETE m_pIndoorAtlasLocationInterop;
                    m_pIndoorAtlasLocationInterop = nullptr;
                }
                
                IndoorAtlasLocationService& IndoorAtlasLocationModule::GetLocationService() const
                {
                    return *m_pLocationService;                    
                }
            }
        }
    }
}
