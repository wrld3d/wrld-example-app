// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowSearchService.h"
#include "SearchQuery.h"
#include "SwallowSearchConstants.h"
#include <algorithm>
#include <cctype>

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            SwallowSearchService::SwallowSearchService()
            {
                m_people.push_back(PersonDetails("James Smith",
                                                 Eegeo::Space::LatLong::FromDegrees(51.520196, -0.085797),
                                                 Eegeo::Resources::Interiors::InteriorId("swallow_lon_citygatehouse"),
                                                 0,
                                                 "Employee Type One",
                                                 "Project Mono",
                                                 "1st Floor, City Gate House",
                                                 "CGH-1-659"));
                
                m_people.push_back(PersonDetails("Emily Gray",
                                                 Eegeo::Space::LatLong::FromDegrees(51.519898, -0.085923),
                                                 Eegeo::Resources::Interiors::InteriorId("swallow_lon_citygatehouse"),
                                                 0,
                                                 "Employee Type One",
                                                 "Project Mono",
                                                 "1st Floor, City Gate House",
                                                 "CGH-1-294"));
                
                m_people.push_back(PersonDetails("John Brown",
                                                 Eegeo::Space::LatLong::FromDegrees(51.520272, -0.086529),
                                                 Eegeo::Resources::Interiors::InteriorId("swallow_lon_citygatehouse"),
                                                 0,
                                                 "Employee Type Two",
                                                 "Project Echo",
                                                 "1st Floor, City Gate House",
                                                 "CGH-1-267"));
                
                m_people.push_back(PersonDetails("Jane Smith",
                                                 Eegeo::Space::LatLong::FromDegrees(51.520023, -0.086328),
                                                 Eegeo::Resources::Interiors::InteriorId("swallow_lon_citygatehouse"),
                                                 0,
                                                 "Employee Type Two",
                                                 "Project Helium",
                                                 "1st Floor, City Gate House",
                                                 "CGH-1-495"));
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
            
            // TODO: temporary alias to the unary version of std::tolower to stop eclipse getting confused (will be replaced when poiDB functionality added
            int ToLower( int ch )
            {
            	return std::tolower(ch);
            }

            void SwallowSearchService::PerformTextSearch(const SdkModel::SearchQuery& query)
            {
                ExecuteQueryPerformedCallbacks(query);
                
                std::vector<SdkModel::SearchResultModel> results;
                
                std::string queryLower;
                
                std::transform(query.Query().begin(), query.Query().end(), std::back_inserter(queryLower), ToLower);
                
                for(std::vector<PersonDetails>::const_iterator it = m_people.begin(); it != m_people.end(); ++it)
                {
                    std::string nameLower;
                    std::transform((*it).m_name.begin(), (*it).m_name.end(), std::back_inserter(nameLower), ToLower);
                    std::string jobTitleLower;
                    std::transform((*it).m_jobTitle.begin(), (*it).m_jobTitle.end(), std::back_inserter(jobTitleLower), ToLower);
                    std::string workingGroupLower;
                    std::transform((*it).m_workingGroup.begin(), (*it).m_workingGroup.end(), std::back_inserter(workingGroupLower), ToLower);
                    std::string officeLocationLower;
                    std::transform((*it).m_officeLocation.begin(), (*it).m_officeLocation.end(), std::back_inserter(officeLocationLower), ToLower);
                    std::string deskCodeLower;
                    std::transform((*it).m_deskCode.begin(), (*it).m_deskCode.end(), std::back_inserter(deskCodeLower), ToLower);
                    
                    bool queryMatch = false;
                    
                    if(nameLower.find(queryLower) != std::string::npos)
                    {
                        queryMatch = true;
                    }
                    else if(jobTitleLower.find(queryLower) != std::string::npos)
                    {
                        queryMatch = true;
                    }
                    else if(workingGroupLower.find(queryLower) != std::string::npos)
                    {
                        queryMatch = true;
                    }
                    else if(officeLocationLower.find(queryLower) != std::string::npos)
                    {
                        queryMatch = true;
                    }
                    else if(deskCodeLower.find(queryLower) != std::string::npos)
                    {
                        queryMatch = true;
                    }
                    
                    if(queryMatch)
                    {
                        std::map<std::string, std::string> metaData;
                        
                        metaData.insert(std::pair<std::string, std::string>(JOB_TITLE_FIELD_NAME, (*it).m_jobTitle));
                        metaData.insert(std::pair<std::string, std::string>(WORKING_GROUP_FIELD_NAME, (*it).m_workingGroup));
                        metaData.insert(std::pair<std::string, std::string>(OFFICE_LOCATION_FIELD_NAME, (*it).m_officeLocation));
                        metaData.insert(std::pair<std::string, std::string>(DESK_CODE_FIELD_NAME, (*it).m_deskCode));
                        
                        results.push_back(SdkModel::SearchResultModel(ExampleApp::Search::SdkModel::SearchResultModel::CurrentVersion,
                                                                      (*it).m_name,
                                                                      (*it).m_name,
                                                                      (*it).m_location,
                                                                      0,
                                                                      true,
                                                                      (*it).m_interiorId,
                                                                      (*it).m_floor,
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
                                                                      0,
                                                                      metaData));
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
