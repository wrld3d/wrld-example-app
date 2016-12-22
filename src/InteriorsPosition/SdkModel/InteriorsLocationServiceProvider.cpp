// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "InteriorsLocationServiceProvider.h"
#include "InteriorSelectionModel.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
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
            
            InteriorsLocationServiceProvider::InteriorsLocationServiceProvider(InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                                                               Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                               Eegeo::Helpers::CurrentLocationService::CurrentLocationService& currentLocationService,
                                                                               Eegeo::Location::ILocationService& defaultLocationService,
                                                                               Eegeo::Location::ILocationService& indoorAtlasLocationService,
                                                                               Eegeo::Location::ILocationService& senionLabLocationService,
                                                                               Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository)
            : m_currentLocationService(currentLocationService)
            , m_defaultLocationService(defaultLocationService)
            , m_indoorAtlasLocationService(indoorAtlasLocationService)
            , m_senionLabLocationService(senionLabLocationService)
            , m_interiorsExplorerModel(interiorsExplorerModel)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_interiorExplorerEnteredCallback(this, &InteriorsLocationServiceProvider::OnInteriorExplorerEntered)
            , m_interiorExplorerExitCallback(this, &InteriorsLocationServiceProvider::OnInteriorExplorerExit)
            , m_interiorMetaDataRepository(interiorMetaDataRepository)
            {
                m_interiorsExplorerModel.InsertInteriorExplorerEnteredCallback(m_interiorExplorerEnteredCallback);
                m_interiorsExplorerModel.InsertInteriorExplorerExitedCallback(m_interiorExplorerExitCallback);
            }
            
            InteriorsLocationServiceProvider::~InteriorsLocationServiceProvider()
            {
                m_interiorsExplorerModel.RemoveInteriorExplorerEnteredCallback(m_interiorExplorerEnteredCallback);
                m_interiorsExplorerModel.RemoveInteriorExplorerExitedCallback(m_interiorExplorerExitCallback);
            }
            
            void InteriorsLocationServiceProvider::OnInteriorExplorerEntered()
            {
                Eegeo::Resources::Interiors::InteriorId interiorId = m_interiorSelectionModel.GetSelectedInteriorId();
                
                const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataDto* dto = m_interiorMetaDataRepository.Get(interiorId);
                std::string user_data = "";
                user_data = dto->GetUserData(); 
                rapidjson::Document document;
                if (document.Parse<0>(user_data.c_str()).HasParseError())
                {
                    return;
                }
                std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo> interiorTrackingInfoList;
                if(document.HasMember(IpsConfig.c_str()) && !document[IpsConfig.c_str()].IsNull())
                {
                    const rapidjson::Value& indoorTrackedBuildingsArray = document[IpsConfig.c_str()];
                    ParseIndoorTrackingInfo(interiorTrackingInfoList, indoorTrackedBuildingsArray);
                }
                
                const std::map<std::string, ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& trackingInfoMap = interiorTrackingInfoList;
                const std::map<std::string, ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>::const_iterator it = trackingInfoMap.find(interiorId.Value());
                
                if(it != trackingInfoMap.end())
                {
                    const ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo& trackingInfo = it->second;
                
                    if(trackingInfo.GetType() == "IndoorAtlas")
                    {
                        Eegeo_TTY("using IndoorAtlas location service");
                        m_currentLocationService.SetLocationService(m_indoorAtlasLocationService);
                    }
                    else if(trackingInfo.GetType() == "Senion")
                    {
                        Eegeo_TTY("using SenionLab location service");
                        m_currentLocationService.SetLocationService(m_senionLabLocationService);
                    }
                }
            }
            
            void InteriorsLocationServiceProvider::OnInteriorExplorerExit()
            {
                Eegeo_TTY("using default location service");
                m_currentLocationService.SetLocationService(m_defaultLocationService);
            }
            
            void InteriorsLocationServiceProvider::ParseIndoorTrackingInfo(std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& interiorTrackingInfoList,
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
}