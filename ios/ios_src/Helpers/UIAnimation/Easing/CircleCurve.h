// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IEasingCurve.h"

#include "MathFunc.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace Helpers
    {
        namespace UIAnimation
        {
            namespace Easing
            {
                // From https://github.com/jesusgollonet/ofpennereasing/blob/master/PennerEasing/Circ.cpp
                template <typename T>
                class CircleInOut : public IEasingCurve<T>
                {
                public:
                    inline T operator()(float t, T b , T c, float d)
                    {
                        t /= d / 2;
                        if (t < 1)
                        {
                            return -c / 2 * (Eegeo::Math::Sqrtf(1 - t * t) - 1) + b;
                        }
                        
                        t -= 2;
                        return c / 2 * (Eegeo::Math::Sqrtf(1 - t * t) + 1) + b;
                    }
                };
            }
        }
    }
}