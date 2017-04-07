// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            class ICompassTouchController
            {
            public:
                ICompassTouchController() {}

                virtual void HandleRotateStart(const AppInterface::RotateData& data) const = 0;
                virtual void HandleRotateEnd(const AppInterface::RotateData& data) const = 0;
            };
        }
    }
}
