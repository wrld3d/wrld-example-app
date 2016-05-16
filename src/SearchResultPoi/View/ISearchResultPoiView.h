// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
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

                virtual void Show(const Search::SdkModel::SearchResultModel& model,
                                  bool isPinned) = 0;
                
                virtual void Hide() = 0;
                
                virtual void UpdateImage(const std::string& url,
                                         bool hasImage,
                                         const std::vector<Byte>* pImageBytes) = 0;
                
                virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                
                virtual void InsertTogglePinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback) = 0;
                virtual void RemoveTogglePinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback) = 0;
            };
        }
    }
}
