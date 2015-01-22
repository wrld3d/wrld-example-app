// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            class ICompassUpdateController
            {
            public:
                virtual ~ICompassUpdateController() { }

                virtual void Update(float deltaSeconds) = 0;
            };
        }
    }
}
