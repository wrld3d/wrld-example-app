// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "MyPinModel.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class SearchResultPinRemovedEvent
            {
            public:
                SearchResultPinRemovedEvent(const SdkModel::MyPinModel& pinModel,
                                            const Search::SdkModel::SearchResultModel& searchResultModel);
                
                const SdkModel::MyPinModel& GetMyPinModel() const;
                
                const Search::SdkModel::SearchResultModel& GetSearchResultModel() const;
                
            private:
                SdkModel::MyPinModel m_pinModel;
                Search::SdkModel::SearchResultModel m_searchResultModel;
            };
        }
    }
}
