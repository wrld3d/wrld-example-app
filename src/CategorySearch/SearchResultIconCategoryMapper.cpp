// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultIconCategoryMapper.h"
#include "SearchResultModel.h"
#include "SwallowSearchConstants.h"
#include "SwallowSearchParser.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        SearchResultIconCategoryMapper::SearchResultIconCategoryMapper()
        {
            m_categoryToIconIndex["caf\u00E9/pub"] = 1;
            m_categoryToIconIndex["coffee"] = 1;
            
            m_categoryToIconIndex["restaurant"] = 2;
            m_categoryToIconIndex["restaurants"] = 2;
            m_categoryToIconIndex["fast food"] = 2;
            m_categoryToIconIndex["food"] = 2;
            
            m_categoryToIconIndex["night life"] = 3;
            m_categoryToIconIndex["nightlife"] = 3;
            m_categoryToIconIndex["nightlife"] = 3;
            
            m_categoryToIconIndex["park"] = 4;
            m_categoryToIconIndex["parks"] = 4;
            
            m_categoryToIconIndex["theatre"] = 5;
            m_categoryToIconIndex["theater"] = 5;
            
            m_categoryToIconIndex["hotel"] = 6;
            m_categoryToIconIndex["hotels"] = 6;
            m_categoryToIconIndex["hotel/motel"] = 6;
            
            m_categoryToIconIndex["bank"] = 7;
            m_categoryToIconIndex["banks"] = 7;
            
            m_categoryToIconIndex["museum"] = 8;
            m_categoryToIconIndex["museums"] = 8;
            m_categoryToIconIndex["arts"] = 8;
            
            m_categoryToIconIndex[Search::Swallow::SearchConstants::PERSON_CATEGORY_NAME] = 12;
            m_categoryToIconIndex[Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME] = 13;
            m_categoryToIconIndex[Search::Swallow::SearchConstants::WORKING_GROUP_CATEGORY_NAME] = 14;
            m_categoryToIconIndex[Search::Swallow::SearchConstants::DEPARTMENT_CATEGORY_NAME] = 14;
            m_categoryToIconIndex[Search::Swallow::SearchConstants::OFFICE_CATEGORY_NAME] = 15;
            m_categoryToIconIndex[Search::Swallow::SearchConstants::STATIONERY_CATEGORY_NAME] = 16;
            m_categoryToIconIndex[Search::Swallow::SearchConstants::TOILETS_CATEGORY_NAME] = 17;
            m_categoryToIconIndex[Search::Swallow::SearchConstants::PRINT_STATION_CATEGORY_NAME] = 18;
            m_categoryToIconIndex[Search::Swallow::SearchConstants::EMERGENCY_EXIT_CATEGORY_NAME] = 19;
            
            m_categoryToIconIndex[Search::Swallow::SearchConstants::TRANSITION_CATEGORY_NAME] = 23;
        }
        
        SearchResultIconCategoryMapper::~SearchResultIconCategoryMapper()
        {
            
        }
        
        int SearchResultIconCategoryMapper::GetIconIndexFromSearchResult(const Search::SdkModel::SearchResultModel& searchResultModel) const
        {
            std::map<std::string, int>::const_iterator it = m_categoryToIconIndex.find(searchResultModel.GetCategory());
            
            if(it == m_categoryToIconIndex.end())
            {
                return 0;
            }
            else
            {
                return it->second;
            }
        }
    }
}
