// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <string>
#include <map>
#include "document.h"
#include "ApplicationInteriorTrackingInfo.h"
#include "InteriorMetaDataRepository.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        void ParseIndoorTrackingInfo(std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& interiorTrackingInfoList,
                                     const rapidjson::Value& indoorTrackedBuildingsArray);
        
        void TryAndGetInteriorTrackingInfo(std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& interiorTrackingInfoList, Eegeo::Resources::Interiors::InteriorId& interiorId, Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository);
        
        const std::string IpsConfig = "ips_config";
    }
}