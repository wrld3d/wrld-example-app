// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "VectorMathDecl.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        class ISearchResultOnMapInFocusController
        {
        public:
            virtual ~ISearchResultOnMapInFocusController() { }
            
            virtual void Update(float dt, const Eegeo::dv3& ecefInterestPoint) = 0;
        };
    }
}
