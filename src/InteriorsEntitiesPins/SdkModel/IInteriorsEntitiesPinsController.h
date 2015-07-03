// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InteriorsEntitiesPins
    {
        namespace SdkModel
        {
            class IInteriorsEntitiesPinsController
            {
            public:
                virtual ~IInteriorsEntitiesPinsController()
                {
                    
                }
                
                virtual void Update(float dt) = 0;
            };
        }
    }
}