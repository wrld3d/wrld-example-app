// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "IndoorAtlasLocationModule.h"
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
            namespace IndoorAtlas
            {
                IndoorAtlasLocationModule::IndoorAtlasLocationModule(ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                     Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                     const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                     const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                                     Eegeo::Location::ILocationService& defaultLocationService,
                                                                     Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository,
                                                                     ExampleAppMessaging::TMessageBus& messageBus,
                                                                     AndroidNativeState& nativeState)
                : m_pLocationService(nullptr)
                , m_pLocationInterop(nullptr)
                , m_pLocationController(nullptr)
                {
                    ASSERT_NATIVE_THREAD

                    m_pLocationInterop = Eegeo_NEW(IndoorAtlasLocationInterop)(nativeState);

                    m_pLocationService = Eegeo_NEW(IndoorAtlasLocationService)(
                            *m_pLocationInterop,
                            defaultLocationService,
                            messageBus,
                            environmentFlatteningService,
                            interiorInteractionModel,
                            interiorSelectionModel,
                            interiorMetaDataRepository);

                    m_pLocationInterop->SetLocationService(m_pLocationService);

                    m_pLocationController = Eegeo_NEW(IndoorAtlasLocationController)(
                            *m_pLocationService,
                            appModeModel,
                            interiorSelectionModel,
                            interiorMetaDataRepository);
                }

                IndoorAtlasLocationModule::~IndoorAtlasLocationModule()
                {
                    ASSERT_NATIVE_THREAD

                    Eegeo_DELETE m_pLocationController;
                    Eegeo_DELETE m_pLocationService;
                    Eegeo_DELETE m_pLocationInterop;
                }

                IndoorAtlasLocationService &IndoorAtlasLocationModule::GetLocationService()
                {
                    return *m_pLocationService;
                }

                IndoorAtlasLocationInterop &IndoorAtlasLocationModule::GetLocationManager()
                {
                    return *m_pLocationInterop;
                }
            }
        }
    }
}
