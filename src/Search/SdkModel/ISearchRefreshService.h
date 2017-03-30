// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "VectorMath.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            class ISearchRefreshService
            {
            public:
                virtual ~ISearchRefreshService() { }

                virtual void TryRefreshSearch(float deltaSeconds, const Eegeo::dv3& interestPointEcef, const Eegeo::dv3& viewpointEcef) = 0;
                virtual void SetAnchorPoint(const Eegeo::dv3& interestPointEcef) = 0;
                virtual void SetEnabled(bool enabled) = 0;
                virtual const bool IsEnabled() const = 0;
            };
        }
    }
}
