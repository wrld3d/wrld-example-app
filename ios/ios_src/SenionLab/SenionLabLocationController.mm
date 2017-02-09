// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SenionLabLocationController.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"
#include <map>
#include <string>

namespace ExampleApp
{
    namespace SenionLab
    {
        SenionLabLocationController::SenionLabLocationController(SenionLabLocationManager& locationManager,
                                                                 ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                 const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                 const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration)
        : m_locationManager(locationManager)
        , m_appModeModel(appModeModel)
        , m_interiorSelectionModel(interiorSelectionModel)
        , m_applicationConfiguration(applicationConfiguration)
        , m_appModeChangedCallback(this, &SenionLabLocationController::OnAppModeChanged)
        {
            m_appModeModel.RegisterAppModeChangedCallback(m_appModeChangedCallback);
        }
        
        SenionLabLocationController::~SenionLabLocationController()
        {
            m_appModeModel.UnregisterAppModeChangedCallback(m_appModeChangedCallback);
        }
        
        void SenionLabLocationController::OnAppModeChanged()
        {
            Eegeo::Resources::Interiors::InteriorId interiorId = m_interiorSelectionModel.GetSelectedInteriorId();
         
            [&m_locationManager StopUpdatingLocation];
         
            if(m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode)
            {
                const std::map<std::string, ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& trackingInfoMap = m_applicationConfiguration.InteriorTrackingInfo();
                std::map<std::string, ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>::const_iterator it;
         
                NSMutableArray<NSString*>* mutableMapKeyArray = [NSMutableArray array];
                NSString* apiSecret = nil;
                std::map<std::string, std::map<int, std::string>> floorMap;
                std::map<std::string, Eegeo::Resources::Interiors::InteriorId> interiorIdMap;
                        
                for(it = trackingInfoMap.begin(); it != trackingInfoMap.end(); ++it)
                {
                    if(it->second.GetType() == "Senion")
                    {
                        if(apiSecret == nil)
                        {
                            apiSecret = [NSString stringWithCString:it->second.GetConfig().GetApiSecret().c_str() encoding:[NSString defaultCStringEncoding]];
                        }
                                
                        std::string mapKey = it->second.GetConfig().GetApiKey();
                                
                        [mutableMapKeyArray addObject:[NSString stringWithCString:mapKey.c_str() encoding:[NSString defaultCStringEncoding]]];
                                
                        floorMap.insert(std::pair<std::string, std::map<int, std::string>>(mapKey, it->second.GetFloorIndexMap()));
                                
                        interiorIdMap.insert(std::pair<std::string, Eegeo::Resources::Interiors::InteriorId>(mapKey, it->second.GetInteriorId()));
                    }
                }
                        
                if(mutableMapKeyArray.count > 0)
                {
                    [&m_locationManager StartUpdatingLocation: mutableMapKeyArray
                                                    apiSecret: apiSecret
                                                     floorMap: floorMap
                                                interiorIdMap: interiorIdMap];
                }
            }
        }
    }
}
