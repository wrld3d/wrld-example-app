#include "SearchTagToYelpCategoryMapper.h"


namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {                
                SearchTagToYelpCategoryMapper::SearchTagToYelpCategoryMapper(const std::map<std::string, std::string>& appTagToYelpCategoryMap,
                                                                             Search::Yelp::SdkModel::YelpCategoryMapperUpdater& yelpCategoryMapperUpdater,
                                                                             const std::string& defaultTag)
                : m_yelpCategoryMapperUpdater(yelpCategoryMapperUpdater)
                , m_yelpCategoryMapperChangedCallback(this, &SearchTagToYelpCategoryMapper::OnYelpCategoryMapperAdded)
                , m_yelpCategoryMapperResetCallback(this, &SearchTagToYelpCategoryMapper::OnYelpCategoryMapperReset)
                , m_appTagToYelpCategoryMap(appTagToYelpCategoryMap)
                , m_defaultTag(defaultTag)
                {
                    m_yelpCategoryMapperUpdater.RegisterMappingAdded(m_yelpCategoryMapperChangedCallback);
                    m_yelpCategoryMapperUpdater.RegisterMappingReset(m_yelpCategoryMapperResetCallback);
                    
                    for(auto it = m_appTagToYelpCategoryMap.begin(); it != m_appTagToYelpCategoryMap.end(); ++it)
                    {
                        m_searchTagToYelpRootCategoryModel[it->first].yelpCategoryFilter = it->second;
                        m_searchTagToYelpRootCategoryModel[it->first].performYelpSearch = true;
                    }
                }
                
                SearchTagToYelpCategoryMapper::~SearchTagToYelpCategoryMapper()
                {
                    m_yelpCategoryMapperUpdater.UnregisterMappingReset(m_yelpCategoryMapperResetCallback);
                    m_yelpCategoryMapperUpdater.UnregisterMappingAdded(m_yelpCategoryMapperChangedCallback);
                }
                
                void SearchTagToYelpCategoryMapper::AddMapping(const std::string& tag, const YelpCategoryModel& yelpCategoryModel)
                {
                    m_searchTagToYelpRootCategoryModel[tag] = yelpCategoryModel;
                }

                void SearchTagToYelpCategoryMapper::RemoveMapping(const std::string& tag)
                {
                    m_searchTagToYelpRootCategoryModel.erase(tag);
                }
                
                void SearchTagToYelpCategoryMapper::OnYelpCategoryMapperAdded(const std::string& tag, const YelpCategoryModel& yelpCategoryModel)
                {
                    AddMapping(tag, yelpCategoryModel);
                }
                
                void SearchTagToYelpCategoryMapper::OnYelpCategoryMapperReset()
                {
                    m_searchTagToYelpRootCategoryModel.clear();
                    for(auto it = m_appTagToYelpCategoryMap.begin(); it != m_appTagToYelpCategoryMap.end(); ++it)
                    {
                        m_searchTagToYelpRootCategoryModel[it->first].yelpCategoryFilter = it->second;
                        m_searchTagToYelpRootCategoryModel[it->first].performYelpSearch = true;
                    }
                }
                
                bool SearchTagToYelpCategoryMapper::TryGetBestYelpCategoryForSearchTag(const std::string& searchTag, YelpCategoryModel& out_bestMatchedYelpCategoryModel)
                {
                    for(int i = 0; i < m_searchTagToYelpRootCategoryModel.size(); i++)
                    {
                        YelpCategoryModel value = m_searchTagToYelpRootCategoryModel[searchTag];
                        if (std::strcmp(value.yelpCategoryFilter.c_str(), "") != 0)
                        {
                            out_bestMatchedYelpCategoryModel = value;
                            return true;
                        }
                    }
                    YelpCategoryModel defaultValue { m_defaultTag, true };
                    out_bestMatchedYelpCategoryModel = defaultValue;
                    return false;
                }

            }
        }
    }
}