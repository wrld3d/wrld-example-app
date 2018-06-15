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
        : m_pSenionInterop(nullptr)
        , m_pLocationService(nullptr)
        , m_pLocationController(nullptr)
        {
            m_pSenionInterop = Eegeo_NEW(InteriorsPosition::SdkModel::SenionLab::SenionLabLocationInterop);
            
            m_pLocationService = Eegeo_NEW(InteriorsPosition::SdkModel::SenionLab::SenionLabLocationService)(*m_pSenionInterop, defaultLocationService, messageBus, environmentFlatteningService, interiorInteractionModel, interiorSelectionModel, interiorMetaDataRepository);
            
            // bit hacky, as we've got two-phase initialisation in a public API
            // could get around this by subclassing SenionLocationService and using template method to instantiate the interop classes
            m_pSenionInterop->SetLocationService(m_pLocationService);
            
            m_pLocationController = Eegeo_NEW(InteriorsPosition::SdkModel::SenionLab::SenionLabLocationController)(*m_pLocationService,
                                                                                                                   appModeModel,
                                                                                                                   interiorSelectionModel,
                                                                                                                   interiorMetaDataRepository);
        }
        
        SenionLabLocationModule::~SenionLabLocationModule()
        {
            Eegeo_DELETE m_pLocationController;
            Eegeo_DELETE m_pLocationService;
            Eegeo_DELETE m_pSenionInterop;
        }
                             
        InteriorsPosition::SdkModel::SenionLab::SenionLabLocationService& SenionLabLocationModule::GetLocationService() const
        {
            return *m_pLocationService;
        }
    }
}
