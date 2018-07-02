// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "IndoorAtlasIncludes.h"
#include "IIndoorAtlasLocationInterop.h"
#include "Types.h"

#include <string>
#include <map>

// class that communicates with the indoor atlas objective-c api
// try to scrape as much off this and only deal with callback passing-on
@interface IndoorAtlasLocationManager : NSObject

-(instancetype) init;

-(void) setLocationService: (ExampleApp::InteriorsPosition::SdkModel::IndoorAtlas::IndoorAtlasLocationService*) indoorAtlasLocationService;

-(void) startUpdating: (NSString*) apiKey
            apiSecret: (NSString*) apiSecret
             floorMap: (std::map<int, std::string>) floorMap;

-(void) stopUpdating;

@end


@class IndoorAtlasLocationManager;

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace IndoorAtlas
            {
                class IndoorAtlasLocationInterop : public IIndoorAtlasLocationInterop, private Eegeo::NonCopyable
                {
                public:
                    IndoorAtlasLocationInterop();
                    ~IndoorAtlasLocationInterop();
                                        
                    void SetLocationService(IndoorAtlasLocationService* pIndoorAtlasLocationManager) override;
                    
                    // interface implementation
                    void StartUpdating(const std::string& apiKey,
                                               const std::string& apiSecret,
                                               const std::map<int, std::string>& floorMap) override;
                    
                    void StopUpdating() override;
                private:
                    IndoorAtlasLocationManager* m_pManager;
                };
            }
        }
    }
}
