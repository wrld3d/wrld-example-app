// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SizeHelpers.h"

#include <algorithm>

namespace ExampleApp
{
    namespace Helpers
    {
        namespace SizeHelpers
        {
            Eegeo::v2 CalculateFitMaintain(Eegeo::v2 availableSize, Eegeo::v2 originalSize)
            {
                if(originalSize.x <= 0.0 || originalSize.y <= 0.0)
                {
                    return originalSize;
                }
                float xScale = availableSize.x/originalSize.x;
                float yScale = availableSize.y/originalSize.y;
                float scale = std::min(xScale,yScale);
                
                return originalSize*scale;
            }
        }
    }
}