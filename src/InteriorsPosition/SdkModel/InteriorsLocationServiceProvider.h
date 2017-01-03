// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ILocationService.h"
#include "CurrentLocationService.h"
#include "InteriorsExplorerModel.h"
#include "ApplicationConfiguration.h"
#include "InteriorMetaDataRepository.h"
#include "ApplicationInteriorTrackingInfo.h"

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
                                                 Eegeo::Location::ILocationService& indoorAtlasLocationService,
                                                 Eegeo::Location::ILocationService& senionLabLocationService,
                                                 Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository);
                
                ~InteriorsLocationServiceProvider();
                
                const Eegeo::Helpers::CurrentLocationService::CurrentLocationService& GetCurrentLocationService() { return m_currentLocationService; }
                
            private:
                Eegeo::Helpers::CurrentLocationService::CurrentLocationService& m_currentLocationService;
                Eegeo::Location::ILocationService& m_defaultLocationService;
                Eegeo::Location::ILocationService& m_indoorAtlasLocationService;
                Eegeo::Location::ILocationService& m_senionLabLocationService;
                
                InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                
                void OnInteriorExplorerEntered();
                Eegeo::Helpers::TCallback0<InteriorsLocationServiceProvider> m_interiorExplorerEnteredCallback;
                void OnInteriorExplorerExit();
                Eegeo::Helpers::TCallback0<InteriorsLocationServiceProvider> m_interiorExplorerExitCallback;
                Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& m_interiorMetaDataRepository;
            };
        }
    }
}