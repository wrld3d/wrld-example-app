// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "AppModeModel.h"
#include "InteriorsExplorer.h"
#include "ApplicationConfiguration.h"
#include "InteriorMetaDataRepository.h"
#include "ApplicationInteriorTrackingInfo.h"
#include "BidirectionalBus.h"
#include "IndoorAtlasLocationService.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace IndoorAtlas
            {
                class IndoorAtlasLocationController
                {
                public:
                	IndoorAtlasLocationController(IndoorAtlasLocationService& indoorAtlasLocationService,
                                                  AppModes::SdkModel::IAppModeModel& appModeModel,
                                                  const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                  Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository);
                    ~IndoorAtlasLocationController();
                    
                private:
                    IndoorAtlasLocationService& m_locationService;
                    ExampleApp::AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    const Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                    Eegeo::Helpers::TCallback0<IndoorAtlasLocationController> m_appModeChangedCallback;
                    Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& m_interiorMetaDataRepository;
                    
                    void OnAppModeChanged();
                };
            }
        }
    }
}
