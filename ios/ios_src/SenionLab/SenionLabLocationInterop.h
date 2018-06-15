// Copyright eeGeo Ltd (2012-2016), All Rights Reserved
#pragma once

#include "Location.h"
#include "LatLongAltitude.h"
#include "InteriorMetaData.h"
#include "Rendering.h"
#include "BidirectionalBus.h"
#include "ISenionLabLocationInterop.h"

#include <string>
#include <map>

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                class SenionLabLocationService;
            }
        }
    }
}

// class that communicates with the senion objective-c api
// try to scrape as much off this and only deal with callback passing-on
@interface SenionLabLocationManager : NSObject

-(instancetype) init;

-(void) setLocationService: (ExampleApp::InteriorsPosition::SdkModel::SenionLab::SenionLabLocationService*) senionLocationService;

-(void) startUpdating: (NSString*) apiKey
            apiSecret: (NSString*) apiSecret
             floorMap: (std::map<int, std::string>) floorMap;

-(void) stopUpdating;

@end

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                class SenionLabLocationInterop : public ISenionLabLocationInterop, private Eegeo::NonCopyable
                {
                public:
                    SenionLabLocationInterop();
                    ~SenionLabLocationInterop();
                    
                    // non-interface
                    void SetLocationService(SenionLabLocationService* pSenionLabLocationService);
                    
                    // interface implementation
                    void StartUpdatingLocation(const std::string& apiKey,
                                               const std::string& apiSecret,
                                               const std::map<int, std::string>& floorMap) override;
                    
                    void StopUpdatingLocation() override;
                private:
                    SenionLabLocationManager* m_pManager;
                };
            }
        }
    }
}
