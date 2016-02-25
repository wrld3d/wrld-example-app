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
                // From https://github.com/jesusgollonet/ofpennereasing/blob/master/PennerEasing/Back.cpp
                template <typename T>
                class BackOut : public IEasingCurve<T>
                {
                public:
                    inline T operator()(float t, T b , T c, float d)
                    {
                        float s = 1.70158f;
                        
                        t = (t / d) - 1.0f;
                        
                        return c * (t * t * ((s + 1) * t + s) + 1) + b;
                    }
                };
            }
        }
    }
}