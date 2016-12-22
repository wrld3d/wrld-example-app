// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "IndoorAtlasLocationController.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"
#include <map>
#include <string>

namespace ExampleApp
{
    namespace IndoorAtlas
    {
        const std::string InteriorId = "interior_id";
        const std::string Type = "type";
        const std::string Config = "config";
        const std::string FloorMapping = "floor_mapping";
        const std::string ApiKey = "api_key";
        const std::string ApiSecret = "api_secret";
        const std::string BuildingFloorIndex = "building_floor_index";
        const std::string TrackedFloorIndex = "tracked_floor_index";
        const std::string IpsConfig = "ips_config";
        
        IndoorAtlasLocationController::IndoorAtlasLocationController(IndoorAtlasLocationManager& locationManager,
                                                                     ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                     Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                     const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                     Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository)
        : m_locationManager(locationManager)
        , m_appModeModel(appModeModel)
        , m_interiorInteractionModel(interiorInteractionModel)
        , m_interiorSelectionModel(interiorSelectionModel)
        , m_appModeChangedCallback(this, &IndoorAtlasLocationController::OnAppModeChanged)
        , m_floorSelectedCallback(this, &IndoorAtlasLocationController::OnFloorSelected)
        , m_interiorMetaDataRepository(interiorMetaDataRepository)
        {
            m_appModeModel.RegisterAppModeChangedCallback(m_appModeChangedCallback);
            m_interiorInteractionModel.RegisterInteractionStateChangedCallback(m_floorSelectedCallback);
        }
        
        IndoorAtlasLocationController::~IndoorAtlasLocationController()
        {
            m_appModeModel.UnregisterAppModeChangedCallback(m_appModeChangedCallback);
            m_interiorInteractionModel.UnregisterModelChangedCallback(m_floorSelectedCallback);

        }
        
        void IndoorAtlasLocationController::OnAppModeChanged()
        {
            Eegeo::Resources::Interiors::InteriorId interiorId = m_interiorSelectionModel.GetSelectedInteriorId();
            std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo> interiorTrackingInfoList;

            if(interiorId.IsValid())
            {
                // check if data exists
                const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataDto* dto = m_interiorMetaDataRepository.Get(interiorId);
                std::string user_data = "";
                user_data = dto->GetUserData();
                rapidjson::Document document;
                if (document.Parse<0>(user_data.c_str()).HasParseError())
                {
                    return;
                }
                
                if(document.HasMember(IpsConfig.c_str()) && !document[IpsConfig.c_str()].IsNull())
                {
                    const rapidjson::Value& indoorTrackedBuildingsArray = document[IpsConfig.c_str()];
                    ParseIndoorTrackingInfo(interiorTrackingInfoList, indoorTrackedBuildingsArray);
                }
            }
            else
            {
                return;
            }
            
            int currentFloorIndex = m_interiorInteractionModel.GetSelectedFloorIndex();
         
            [&m_locationManager StopUpdatingLocation];
         
            if(m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode)
            {
                const std::map<std::string, ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& trackingInfoMap = interiorTrackingInfoList;
                const std::map<std::string, ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>::const_iterator it = trackingInfoMap.find(interiorId.Value());
         
                if(it != trackingInfoMap.end())
                {
                    const ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo& trackingInfo = it->second;
         
                    if(trackingInfo.GetType() == "IndoorAtlas")
                    {
                        NSString* apiKey = [NSString stringWithCString:trackingInfo.GetConfig().GetApiKey().c_str() encoding:[NSString defaultCStringEncoding]];
                        NSString* apiSecret = [NSString stringWithCString:trackingInfo.GetConfig().GetApiSecret().c_str() encoding:[NSString defaultCStringEncoding]];
                        std::map<int, std::string> floorMap = trackingInfo.GetFloorIndexMap();
         
                        [&m_locationManager StartUpdatingLocation: apiKey
                                                        apiSecret: apiSecret
                                                         floorMap: floorMap
                                                       floorIndex: currentFloorIndex];
                    }
                }
            }
        }
        
        void IndoorAtlasLocationController::OnFloorSelected()
        {
            int currentFloorIndex = m_interiorInteractionModel.GetSelectedFloorIndex();
            [&m_locationManager SetFloorIndex:currentFloorIndex];
        }
        
        void IndoorAtlasLocationController::ParseIndoorTrackingInfo(std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& interiorTrackingInfoList,
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
    }
}