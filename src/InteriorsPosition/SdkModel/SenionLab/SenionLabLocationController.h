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
                                                const std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& trackingInfoMap);
                    ~SenionLabLocationController();
                    
                    void StartUpdatingLocation();
                    void StopUpdatingLocation();
                    
                private:
                    ISenionLabLocationManager& m_locationManager;
                    std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo> m_trackingInfoMap;
                    std::map<std::string, std::map<int, std::string> > m_floorMaps;
                    std::map<std::string, Eegeo::Resources::Interiors::InteriorId> m_interiorIds;
                };
            }
        }
    }
}
