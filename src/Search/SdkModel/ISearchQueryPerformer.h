// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "ICallback.h"
#include "Space.h"
#include "SearchQuery.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            class ISearchQueryPerformer
            {
            public:
                virtual ~ISearchQueryPerformer() { }

                virtual bool HasQuery() const = 0;

                virtual const SearchQuery& GetPreviousSearchQuery() const = 0;

                virtual void PerformSearchQuery(const std::string& query, bool isCategory, bool tryInteriorSearch) = 0;

                virtual void PerformSearchQuery(const std::string& query, bool isCategory, bool tryInteriorSearch, float radius) = 0;

                virtual void PerformSearchQuery(const std::string& query, bool isCategory, bool tryInteriorSearch, const Eegeo::Space::LatLongAltitude& location) = 0;
                
                virtual void PerformSearchQuery(const std::string& query, bool isCategory, bool tryInteriorSearch, const Eegeo::Space::LatLongAltitude& location, float radius) = 0;

                virtual void RemoveSearchQueryResults() = 0;

                virtual void InsertOnSearchResultsClearedCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void RemoveOnSearchResultsClearedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
