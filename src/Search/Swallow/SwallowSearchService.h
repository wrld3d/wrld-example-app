// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include <string>
#include "Search.h"
#include "SearchServiceBase.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            class SwallowSearchService : public SdkModel::SearchServiceBase, private Eegeo::NonCopyable
            {
            public:
                SwallowSearchService();
                
                void CancelInFlightQueries();
                
                void PerformLocationQuerySearch(const SdkModel::SearchQuery& query);
                
                void PerformIdentitySearch(const std::string& searchResultIdentifier,
                                           Eegeo::Helpers::ICallback1<const SdkModel::IdentitySearchCallbackData&>& callback);
            private:
                struct PersonDetails
                {
                    std::string m_name;
                    Eegeo::Space::LatLong m_location;
                    std::string m_officeCode;
                    std::string m_deskNumber;
                    std::string m_department;
                    
                    PersonDetails(const std::string& name,
                                  const Eegeo::Space::LatLong& location,
                                  const std::string& officeCode,
                                  const std::string& deskNumber,
                                  const std::string& department)
                    : m_name(name)
                    , m_location(location)
                    , m_officeCode(officeCode)
                    , m_deskNumber(deskNumber)
                    , m_department(department)
                    {
                        
                    }
                };
                
                void PerformTextSearch(const SdkModel::SearchQuery& query);
                
                void PerformCategorySearch(const SdkModel::SearchQuery& query);
                
                std::vector<PersonDetails> m_people;
            };
        }
    }
}
