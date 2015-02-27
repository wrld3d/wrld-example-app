// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace SdkModel
        {
            class ISearchResultPoiViewImageFetcher
            {
            public:
                virtual ~ISearchResultPoiViewImageFetcher() { }
                
                virtual void FetchImageForSearchResult(const std::string& imageUrl) = 0;
            };
        }
    }
}
