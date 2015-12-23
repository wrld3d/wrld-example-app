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
            namespace Curves
            {
                class ICurve
                {
                public:
                    virtual ~ICurve() { }
                    
                    virtual float operator()(float t, float b , float c, float d) = 0;
                    
                    virtual Eegeo::v2 operator()(float t, const Eegeo::v2& b , const Eegeo::v2& c, float d) = 0;
                };
            }
        }
    }
}
