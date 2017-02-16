// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include <map>
#include <string>
#include <vector>

#include "ApplicationInteriorTrackingInfo.h"
#include "InteriorId.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                class ISenionLabLocationManager
                {
                public:
                    virtual void StartUpdatingLocation(const std::string& apiSecret,
                                                       const Eegeo::Resources::Interiors::InteriorId currentInterior,
                                                       const std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& senionInfoMap,
                                                       const std::map<std::string, std::map<int, std::string> >& floorMaps,
                                                       const std::map<std::string, Eegeo::Resources::Interiors::InteriorId>& interiorIds) = 0;
                    virtual void StopUpdatingLocation() = 0;
                };
            }
        }
    }
}
