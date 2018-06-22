// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "SenionLabLocationModule.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "AndroidNativeState.h"
#include "BidirectionalBus.h"
#include "InteriorInteractionModel.h"
#include "InteriorSelectionModel.h"

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
                : m_pLocationInterop(nullptr)
                , m_pLocationService(nullptr)
                , m_pLocationController(nullptr)
                {
                    ASSERT_NATIVE_THREAD

                    m_pLocationInterop = Eegeo_NEW(SenionLabLocationInterop)(messageBus, nativeState);

                    m_pLocationService = Eegeo_NEW(SenionLabLocationService)(
                            *m_pLocationInterop,
                            defaultLocationService,
                            messageBus,
                            environmentFlatteningService,
                            interiorInteractionModel,
                            interiorSelectionModel,
                            interiorMetaDataRepository);

                    m_pLocationInterop->SetLocationService(m_pLocationService);

                    m_pLocationController = Eegeo_NEW(SenionLabLocationController)(
                            *m_pLocationService,
                            appModeModel,
                            interiorSelectionModel,
                            interiorMetaDataRepository);
                }

                SenionLabLocationModule::~SenionLabLocationModule()
                {
                    ASSERT_NATIVE_THREAD

                    Eegeo_DELETE m_pLocationController;
                    Eegeo_DELETE m_pLocationService;
                    Eegeo_DELETE m_pLocationInterop;
                }

                SenionLabLocationService& SenionLabLocationModule::GetLocationService()
                {
                    return *m_pLocationService;
                }

                SenionLabLocationInterop& SenionLabLocationModule::GetLocationManager()
                {
                    return *m_pLocationInterop;
                }
            }
        }
    }
}
