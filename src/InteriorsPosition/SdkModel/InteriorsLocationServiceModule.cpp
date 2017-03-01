// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "InteriorsLocationServiceModule.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            InteriorsLocationServiceModule::InteriorsLocationServiceModule(InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                                                           Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                           Eegeo::Helpers::CurrentLocationService::CurrentLocationService& currentLocationService,
                                                                           Eegeo::Location::ILocationService& defaultLocationService,
                                                                           std::map<std::string, Eegeo::Location::ILocationService&> interiorLocationServices,
                                                                           Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository,
                                                                           Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                           CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                           Compass::SdkModel::ICompassModel& compassModel,
                                                                           ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pController = Eegeo_NEW(InteriorsLocationServiceController)(currentLocationService,
                                                                              interiorInteractionModel,
                                                                              cameraTransitionController,
                                                                              compassModel);
                
                m_pProvider = Eegeo_NEW(InteriorsLocationServiceProvider)(interiorsExplorerModel,
                                                                          interiorSelectionModel,
                                                                          currentLocationService,
                                                                          defaultLocationService,
                                                                          interiorLocationServices,
                                                                          interiorMetaDataRepository,
                                                                          messageBus);
            }
            
            InteriorsLocationServiceModule::~InteriorsLocationServiceModule()
            {
                Eegeo_DELETE m_pController;
                m_pController = NULL;
                
                Eegeo_DELETE m_pProvider;
                m_pProvider = NULL;
            }
        }
    }
}
