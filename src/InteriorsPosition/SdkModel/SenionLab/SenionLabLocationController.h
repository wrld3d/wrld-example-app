// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ISenionLabLocationManager.h"
#include "ICallback.h"
#include "AppModeModel.h"
#include "InteriorsExplorer.h"
#include "ApplicationConfiguration.h"
#include "InteriorMetaDataRepository.h"
#include "ApplicationInteriorTrackingInfo.h"
#include "BidirectionalBus.h"
#include "AboutPageSenionSettingsTypeMessage.h"
#include "ApplicationInteriorTrackingInfo.h"

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
                    SenionLabLocationController(ISenionLabLocationManager& locationManager,
                                                AppModes::SdkModel::IAppModeModel& appModeModel,
                                                const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                const std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& trackingInfoMap);
                    ~SenionLabLocationController();
                    
                private:
                    ISenionLabLocationManager& m_locationManager;
                    ExampleApp::AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    const Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                    std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo> m_trackingInfoMap;
                    Eegeo::Helpers::TCallback0<SenionLabLocationController> m_appModeChangedCallback;
                    std::map<std::string, std::map<int, std::string> > m_floorMaps;
                    std::map<std::string, Eegeo::Resources::Interiors::InteriorId> m_interiorIds;

                    void OnAppModeChanged();
                };
            }
        }
    }
}
