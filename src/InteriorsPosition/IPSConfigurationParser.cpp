// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "IPSConfigurationParser.h"

namespace
{
    const std::string InteriorId = "interior_id";
    const std::string Type = "type";
    const std::string Config = "config";
    const std::string FloorMapping = "floor_mapping";
    const std::string ApiKey = "api_key";
    const std::string ApiSecret = "api_secret";
    const std::string BuildingFloorIndex = "building_floor_index";
    const std::string TrackedFloorIndex = "tracked_floor_index";
}
namespace ExampleApp
{
    namespace InteriorsPosition
    {
        void ParseIndoorTrackingInfo(std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& interiorTrackingInfoList,
                                                                    const rapidjson::Value& indoorTrackedBuildingsArray)
        {
            const rapidjson::Value& building = indoorTrackedBuildingsArray;
            
            Eegeo_ASSERT(building.HasMember(InteriorId.c_str()), "Interior Id not found");
            const std::string& id = building[InteriorId.c_str()].GetString();
            const Eegeo::Resources::Interiors::InteriorId& interiorId(id);
            
            Eegeo_ASSERT(building.HasMember(Type.c_str()), "Type not found");
            const std::string& type = building[Type.c_str()].GetString();
            
            
            Eegeo_ASSERT(building.HasMember(Config.c_str()), "Config not found");
            const std::string& apiKey = building[Config.c_str()][0][ApiKey.c_str()].GetString();
            const std::string& apiSecret = building[Config.c_str()][0][ApiSecret.c_str()].GetString();
            ApplicationConfig::SdkModel::ApplicationInteriorTrackingConfig interiorTrackingConfig(apiKey, apiSecret);
            
            Eegeo_ASSERT(building.HasMember(FloorMapping.c_str()), "FloorMapping not found");
            const rapidjson::Value& floorMappingArray = building[FloorMapping.c_str()];
            
            std::map<int, std::string> floorMapping;
            for(rapidjson::SizeType j = 0; j < floorMappingArray.Size(); ++j)
            {
                floorMapping[floorMappingArray[j][BuildingFloorIndex.c_str()].GetInt()] = floorMappingArray[j][TrackedFloorIndex.c_str()].GetString();
            }
            
            ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo interiorTrackingInfo(interiorId,
                                                                                              type,
                                                                                              interiorTrackingConfig,
                                                                                              floorMapping);
            
            interiorTrackingInfoList.insert(std::pair<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>(interiorId.Value(),interiorTrackingInfo));
        }
        
        void TryAndGetInteriorTrackingInfo(std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& interiorTrackingInfoList, Eegeo::Resources::Interiors::InteriorId& interiorId, Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository)
        {
            if(!interiorMetaDataRepository.Contains(interiorId))
            {
                // This will return when trying to enter building before web request can be proccessed.
                // Will need a proper fix. Talk to Tim or Michael.
                return;
            }
            const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataDto* dto = interiorMetaDataRepository.Get(interiorId);
            std::string user_data = "";
            user_data = dto->GetUserData();
            rapidjson::Document document;
            if (document.Parse<0>(user_data.c_str()).HasParseError())
            {
                return;
            }
            
            if(document.HasMember(InteriorsPosition::IpsConfig.c_str()) && !document[InteriorsPosition::IpsConfig.c_str()].IsNull())
            {
                const rapidjson::Value& indoorTrackedBuildingsArray = document[InteriorsPosition::IpsConfig.c_str()];
                InteriorsPosition::ParseIndoorTrackingInfo(interiorTrackingInfoList, indoorTrackedBuildingsArray);
            }
        }

    }
}