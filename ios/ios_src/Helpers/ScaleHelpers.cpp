// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ScaleHelpers.h"
#include "App.h"

namespace ExampleApp
{
    namespace Helpers
    {
        namespace ScaleHelpers
        {
            float GetScaleTweakValue()
            {
                float iphoneTweakScale = 1.0f;
                if (App::IsDeviceSmall())
                {
                    iphoneTweakScale = 2.f/3.f;
                }
                return iphoneTweakScale;
            }
        }
    }
}
