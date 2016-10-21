// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ILocationService.h"
#include "CurrentLocationService.h"
#include "InteriorsExplorerModel.h"
#include "TestLocationService.h"

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
                                                 Eegeo::Helpers::CurrentLocationService::CurrentLocationService& currentLocationService,
                                                 Eegeo::Location::ILocationService& defaultLocationService,
                                                 InteriorsPosition::SdkModel::TestLocationService& testLocationService);
                
                ~InteriorsLocationServiceProvider();
                
                const Eegeo::Helpers::CurrentLocationService::CurrentLocationService& GetCurrentLocationService() { return m_currentLocationService; }
                
            private:
                Eegeo::Helpers::CurrentLocationService::CurrentLocationService& m_currentLocationService;
                //Eegeo::Location::ILocationService& m_defaultLocationService;
                //InteriorsPosition::SdkModel::TestLocationService& m_testLocationService;
                
                InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel;
                //Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                
                void OnInteriorExplorerEntered();
                Eegeo::Helpers::TCallback0<InteriorsLocationServiceProvider> m_interiorExplorerEnteredCallback;
                void OnInteriorExplorerExit();
                Eegeo::Helpers::TCallback0<InteriorsLocationServiceProvider> m_interiorExplorerExitCallback;
            };
        }
    }
}