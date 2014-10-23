// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultOnMapIconCategoryMapper.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        SearchResultOnMapIconCategoryMapper::SearchResultOnMapIconCategoryMapper()
        {
        	m_categoryToIconIndex["caf\u00E9/pub"] = 1;
            m_categoryToIconIndex["restaurant"] = 2;
            m_categoryToIconIndex["fast food"] = 2;
            m_categoryToIconIndex["night life"] = 3;
            m_categoryToIconIndex["nightlife"] = 3;

            m_categoryToIconIndex["park"] = 4;
            m_categoryToIconIndex["theatre"] = 5;
            m_categoryToIconIndex["theater"] = 5;
            m_categoryToIconIndex["hotel"] = 6;
            m_categoryToIconIndex["hotel/motel"] = 6;
            m_categoryToIconIndex["bank"] = 7;

            m_categoryToIconIndex["museum"] = 8;
        }
        
        SearchResultOnMapIconCategoryMapper::~SearchResultOnMapIconCategoryMapper()
        {
            
        }
        
        int SearchResultOnMapIconCategoryMapper::GetIconIndexFromSearchResult(const Search::SearchResultModel& searchResultModel) const
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
