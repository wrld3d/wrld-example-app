// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class IWorldPinsVisibilityController
            {
            public:
                virtual ~IWorldPinsVisibilityController() { }

                virtual void Update(float deltaSeconds) = 0;

                virtual void SetModality(float modality) = 0;
                
                virtual int GetVisibilityMask() = 0;
                
                virtual void SetVisibilityMask(int visibilityMask) = 0;
                
                virtual void SetHideOutdoorPinsIndoors(bool hideOutdoorPinsIndoors) = 0;
            };
        }
    }
}
