// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <map>

#include "ILocationService.h"
#include "CurrentLocationService.h"
#include "InteriorsExplorerModel.h"
#include "ApplicationConfiguration.h"
#include "ApplicationInteriorTrackingInfo.h"
#include "AboutPageViewModel.h"
#include "ILocationProvider.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            class InteriorsLocationServiceProvider
            {
            public:
                InteriorsLocationServiceProvider(InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                                 Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                 ExampleApp::LocationProvider::ILocationProvider& locationProvider,
                                                 std::map<std::string, Eegeo::Location::ILocationService&> interiorLocationServices,
                                                 const Eegeo::Resources::Interiors::MetaData::IInteriorMetaDataService& interiorMetaDataService,
                                                 ExampleAppMessaging::TMessageBus& messageBus);
                
                ~InteriorsLocationServiceProvider();

            private:
                ExampleApp::LocationProvider::ILocationProvider& m_locationProvider;
                std::map<std::string, Eegeo::Location::ILocationService&> m_interiorLocationServices;

                InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                void OnInteriorExplorerEntered();
                Eegeo::Helpers::TCallback0<InteriorsLocationServiceProvider> m_interiorExplorerEnteredCallback;
                void OnInteriorExplorerExit();
                Eegeo::Helpers::TCallback0<InteriorsLocationServiceProvider> m_interiorExplorerExitCallback;
                const Eegeo::Resources::Interiors::MetaData::IInteriorMetaDataService& m_interiorMetaDataService;
            };
        }
    }
}
