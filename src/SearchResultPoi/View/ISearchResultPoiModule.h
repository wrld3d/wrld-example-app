// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchResultPoi.h"
#include "IOpenableControlViewModel.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            class ISearchResultPoiModule
            {
            public:
                virtual ~ISearchResultPoiModule() { }

                virtual ISearchResultPoiViewModel& GetSearchResultPoiViewModel() const = 0;

                virtual OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const = 0;
            };
        }
    }
}
