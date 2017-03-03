// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "SenionLabLocationManager.h"
#include "SenionLabLocationManagerInterop.h"

namespace ExampleApp
{
    namespace SenionLab
    {
        SenionLabLocationManagerInterop::SenionLabLocationManagerInterop(InteriorsPosition::SdkModel::SenionLab::SenionLabLocationService& senionLabLocationService,
                                                                         Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory& alertBoxFactory,
                                                                         ExampleAppMessaging::TMessageBus& messageBus)
        : m_pImpl([[SenionLabLocationManager alloc] Init: &senionLabLocationService
                                      iOSAlertBoxFactory: &alertBoxFactory
                                              messageBus: &messageBus])
        {
        }
        
        SenionLabLocationManagerInterop::~SenionLabLocationManagerInterop()
        {
            [m_pImpl release];
            m_pImpl = nullptr;
        }
        
        void SenionLabLocationManagerInterop::StartUpdatingLocation(const std::string& apiSecret,
                                                                    const std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& senionInfoMap,
                                                                    const std::map<std::string, std::map<int, std::string> >& floorMaps,
                                                                    const std::map<std::string, Eegeo::Resources::Interiors::InteriorId>& interiorIds)
        {
            std::map<std::string, ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>::const_iterator it;
            
            NSMutableArray<NSString*>* mutableMapKeyArray = [NSMutableArray array];
            std::map<std::string, std::map<int, std::string>> floorMap;
            std::map<std::string, Eegeo::Resources::Interiors::InteriorId> interiorIdMap;
            
            for(it = senionInfoMap.begin(); it != senionInfoMap.end(); ++it)
            {
                if(it->second.GetType() == "Senion")
                {
                    std::string mapKey = it->second.GetConfig().GetApiKey();
                    
                    [mutableMapKeyArray addObject:[NSString stringWithCString:mapKey.c_str() encoding:[NSString defaultCStringEncoding]]];
                    
                    floorMap.insert(std::pair<std::string, std::map<int, std::string>>(mapKey, it->second.GetFloorIndexMap()));
                    
                    interiorIdMap.insert(std::pair<std::string, Eegeo::Resources::Interiors::InteriorId>(mapKey, it->second.GetInteriorId()));
                }
            }
            
            if(mutableMapKeyArray.count > 0)
            {
                [m_pImpl StartUpdatingLocation: mutableMapKeyArray
                                                apiSecret: [NSString stringWithCString:apiSecret.c_str() encoding:[NSString defaultCStringEncoding]]
                                                 floorMap: floorMap
                                            interiorIdMap: interiorIdMap];
            }
        }
        
        void SenionLabLocationManagerInterop::StopUpdatingLocation()
        {
            [m_pImpl StopUpdatingLocation];
        }
    }
}
