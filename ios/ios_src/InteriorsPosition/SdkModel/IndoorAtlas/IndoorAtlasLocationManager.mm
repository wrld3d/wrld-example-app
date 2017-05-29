// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "IndoorAtlasLocationManager.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace IndoorAtlas
            {
                IndoorAtlasLocationManager::IndoorAtlasLocationManager(IndoorAtlasLocationService* indoorAtlasLocationService,
                                                                       ExampleAppMessaging::TMessageBus& messageBus,
                                                                       Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory& iOSAlertBoxFactory)
                {
                    m_pLocationManager = [[IndoorAtlasLocationManagerObjC alloc] init: indoorAtlasLocationService
                        messageBus: &messageBus
                        iOSAlertBoxFactory: &iOSAlertBoxFactory];
                }
                
                IndoorAtlasLocationManager::~IndoorAtlasLocationManager()
                {
                    [m_pLocationManager release];
                    m_pLocationManager = NULL;
                }
                
                void IndoorAtlasLocationManager::StartUpdatingLocation(const std::string& apiKey,
                                                                       const std::string& apiSecret,
                                                                       const std::map<int, std::string>& floorMap)
                {
                    NSString* apiKeyNSString = [NSString stringWithCString:apiKey.c_str() encoding:[NSString defaultCStringEncoding]];
                    NSString* apiSecretNSString = [NSString stringWithCString:apiSecret.c_str() encoding:[NSString defaultCStringEncoding]];
                    
                    [m_pLocationManager startUpdatingLocation: apiKeyNSString
                                                    apiSecret: apiSecretNSString
                                                     floorMap: floorMap];
                }
                
                void IndoorAtlasLocationManager::StopUpdatingLocation()
                {
                    [m_pLocationManager stopUpdatingLocation];
                }
            }
        }
    }
}
