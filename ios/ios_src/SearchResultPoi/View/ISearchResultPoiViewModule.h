// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchResultPoiViewIncludes.h"
#include "SearchResultPoi.h"

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

                virtual SearchResultPoiController& GetController() const = 0;

                virtual SearchResultPoiView& GetView() const = 0;
            };
        }
    }
}
