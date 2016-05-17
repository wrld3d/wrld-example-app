// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchResultPoiViewIncludes.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            class ISearchResultPoiViewModule
            {
            public:
                virtual ~ISearchResultPoiViewModule() { }

                virtual SearchResultPoiView& GetView() const = 0;
                virtual SearchResultPoiController& GetController() const = 0;
            };
        }
    }
}
