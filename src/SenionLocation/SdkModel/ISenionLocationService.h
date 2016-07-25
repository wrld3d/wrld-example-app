// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ILocationService.h"
#include "IIndoorLocationDeviceModel.h"
namespace ExampleApp
{
    
    namespace SenionLocation
    {
        
        namespace SdkModel
        {
            class ISenionLocationService : public Eegeo::Location::ILocationService
            {
                
            public:
                virtual ~ISenionLocationService(){}
                                
                
                virtual void UpdateSenionLatLong(const Eegeo::Space::LatLong &latLong) = 0;
                virtual void UpdateAvatarVisiblityStatus(bool status) = 0;
                virtual bool isSenionMode() = 0;
                
                
            };
        }
    }
}