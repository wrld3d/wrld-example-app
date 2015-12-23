// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICurve.h"
#include "MathFunc.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace Helpers
    {
        namespace UIAnimation
        {
            namespace Curves
            {
                // From http://gizma.com/easing/#circ3
                class CircleInOut : public ICurve
                {
                public:
                    inline float operator()(float t, float b , float c, float d)
                    {
                        t /= d / 2;
                        if (t < 1)
                        {
                            return -c / 2 * (Eegeo::Math::Sqrtf(1 - t * t) - 1) + b;
                        }
                        
                        t -= 2;
                        return c / 2 * (Eegeo::Math::Sqrtf(1 - t * t) + 1) + b;
                    }
                    
                    inline Eegeo::v2 operator()(float t, const Eegeo::v2& b , const Eegeo::v2& c, float d)
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