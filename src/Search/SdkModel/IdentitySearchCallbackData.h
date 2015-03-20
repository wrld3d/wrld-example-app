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
                std::string m_locationIdentifier;
                SearchResultModel m_searchResultModel;
                
                IdentitySearchCallbackData(bool success,
                                           const std::string& locationIdentifier)
                : m_success(success)
                , m_locationIdentifier(locationIdentifier)
                {
                }
                
            public:
                static IdentitySearchCallbackData CreateFailed(const std::string& locationIdentifier)
                {
                    return IdentitySearchCallbackData(false, locationIdentifier);
                }
                
                static IdentitySearchCallbackData CreateSucceeded(const std::string& locationIdentifier,
                                                                  const SearchResultModel& model)
                {
                    IdentitySearchCallbackData result(true, locationIdentifier);
                    result.m_searchResultModel = model;
                    return result;
                }
                
                bool IsSuccess() const { return m_success; }
                
                const std::string& GetLocationIdentifier() const { return m_locationIdentifier; }
                
                const SearchResultModel& GetSearchResultModel() const { return m_searchResultModel; }
            };
        }
    }
}
