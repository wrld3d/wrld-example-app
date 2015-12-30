// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MathFunc.h"
#include "VectorMathDecl.h"

namespace ExampleApp
{
    namespace Helpers
    {
        namespace UIAnimation
        {
            namespace Easing
            {
                template <typename T>
                class IEasingCurve
                {
                public:
                    virtual ~IEasingCurve() { }
                    
                    virtual T operator()(float t, T b , T c, float d) = 0;
                };
            }
        }
    }
}
