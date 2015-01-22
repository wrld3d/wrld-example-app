// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchResultModel.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            class ISearchResultPoiView
            {
            public:
                virtual ~ISearchResultPoiView() { };

                virtual void Show(const Search::SdkModel::SearchResultModel model) = 0;
                virtual void Hide() = 0;
                virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
