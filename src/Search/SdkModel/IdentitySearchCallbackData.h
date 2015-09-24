// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            class IdentitySearchCallbackData
            {
                bool m_success;
                SearchResultModel m_searchResultModel;
                
                IdentitySearchCallbackData(bool success,
                                           const SearchResultModel& searchResultModel)
                : m_success(success)
                , m_searchResultModel(searchResultModel)
                {
                }
                
            public:
                static IdentitySearchCallbackData CreateFailed(const SearchResultModel& searchResultModel)
                {
                    return IdentitySearchCallbackData(false, searchResultModel);
                }
                
                static IdentitySearchCallbackData CreateSucceeded(const SearchResultModel& searchResultModel)
                {
                    return IdentitySearchCallbackData(true, searchResultModel);;
                }
                
                bool IsSuccess() const { return m_success; }
                
                const std::string& GetLocationIdentifier() const { return m_searchResultModel.GetIdentifier(); }
                
                const SearchResultModel& GetSearchResultModel() const { return m_searchResultModel; }
            };
        }
    }
}
