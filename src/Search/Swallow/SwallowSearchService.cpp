// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowSearchService.h"
#include "SearchQuery.h"


namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            SwallowSearchService::SwallowSearchService()
            {
                m_people.push_back(PersonDetails("James Smith", Eegeo::Space::LatLong::FromDegrees(51.520196, -0.085797), "", "", ""));
                m_people.push_back(PersonDetails("Emily Gray", Eegeo::Space::LatLong::FromDegrees(51.520236, -0.086151), "", "", ""));
                m_people.push_back(PersonDetails("John Brown", Eegeo::Space::LatLong::FromDegrees(51.520272, -0.086529), "", "", ""));
                m_people.push_back(PersonDetails("Jane Smith", Eegeo::Space::LatLong::FromDegrees(51.520332, -0.086951), "", "", ""));
            }
            
            void SwallowSearchService::CancelInFlightQueries()
            {
                
            }
            
            void SwallowSearchService::PerformLocationQuerySearch(const SdkModel::SearchQuery& query)
            {
                if(!query.IsCategory())
                {
                    PerformTextSearch(query);
                }
                else
                {
                    PerformCategorySearch(query);
                }
            }
                
            void SwallowSearchService::PerformIdentitySearch(const std::string& searchResultIdentifier,
                                                             Eegeo::Helpers::ICallback1<const SdkModel::IdentitySearchCallbackData&>& callback)
            {
                 Eegeo_ASSERT(false, "Identity search not implemented");
            }
            
            void SwallowSearchService::PerformTextSearch(const SdkModel::SearchQuery& query)
            {
                ExecuteQueryPerformedCallbacks(query);
                
                std::vector<SdkModel::SearchResultModel> results;
                
                for(std::vector<PersonDetails>::const_iterator it = m_people.begin(); it != m_people.end(); ++it)
                {
                    if((*it).m_name.find(query.Query()) != std::string::npos)
                    {
                        results.push_back(SdkModel::SearchResultModel(0,
                                                                      (*it).m_name,
                                                                      (*it).m_name,
                                                                      (*it).m_location,
                                                                      "",
                                                                      "",
                                                                      "",
                                                                      "",
                                                                      std::vector<std::string>(),
                                                                      "",
                                                                      "Swallow",
                                                                      "",
                                                                      "",
                                                                      std::vector<std::string>(),
                                                                      0,
                                                                      0));
                    }
                }
                
                ExecutQueryResponseReceivedCallbacks(query, results);
            }
            
            void SwallowSearchService::PerformCategorySearch(const SdkModel::SearchQuery& query)
            {
                
            }
        }
    }
}
