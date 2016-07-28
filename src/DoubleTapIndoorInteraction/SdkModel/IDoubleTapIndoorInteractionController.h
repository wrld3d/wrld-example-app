// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "AppInterface.h"
namespace ExampleApp
{
    namespace DoubleTapIndoorInteraction
    {
        namespace SdkModel
        {
            
            class IDoubleTapIndoorInteractionController : public Eegeo::NonCopyable {
                
            
            public:
                virtual ~IDoubleTapIndoorInteractionController()
                {
                    
                }
                virtual void OnDoubleTap(const AppInterface::TapData& data) = 0 ;
            };
            
        }
    }
}