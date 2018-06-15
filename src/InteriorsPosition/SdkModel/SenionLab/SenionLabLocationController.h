// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "AppModeModel.h"
#include "InteriorsExplorer.h"
#include "ApplicationConfiguration.h"
#include "InteriorMetaDataRepository.h"
#include "ApplicationInteriorTrackingInfo.h"
#include "BidirectionalBus.h"
#import "SenionLabLocationService.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                class SenionLabLocationController
                {
                public:
                    SenionLabLocationController(SenionLabLocationService& locationService,
                                                AppModes::SdkModel::IAppModeModel& appModeModel,
                                                const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository);
                    ~SenionLabLocationController();
                    
                private:
                    SenionLabLocationService& m_locationService;
                    ExampleApp::AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    const Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                    Eegeo::Helpers::TCallback0<SenionLabLocationController> m_appModeChangedCallback;
                    const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& m_interiorMetaDataRepository;
                    
                    void OnAppModeChanged();
                };
            }
        }
    }
}
