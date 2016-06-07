// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WorldPins.h"
#include "IWorldPinIconMappingFactory.h"
#include "Types.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinIconMappingFactory : public IWorldPinIconMappingFactory, private Eegeo::NonCopyable
            {
            public:
                WorldPinIconMappingFactory();
                virtual ~WorldPinIconMappingFactory() { }
                
                virtual IWorldPinIconMapping* Create() const;
                
            };
        }
    }
}