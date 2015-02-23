// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"
#include "SearchResultOnMap.h"
#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace SdkModel
        {
            class ISearchResultOnMapModule
            {
            public:
                virtual ~ISearchResultOnMapModule() { }

                virtual ISearchResultOnMapModel& GetSearchResultOnMapModel() const = 0;
            };
        }
    }
}
