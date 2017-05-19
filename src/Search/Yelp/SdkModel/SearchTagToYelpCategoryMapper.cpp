#include "SearchTagToYelpCategoryMapper.h"

namespace
{
    std::string GetLowerCaseString(const std::string& stringToLower)
    {
        std::string lowerCaseString = stringToLower;
        std::transform(lowerCaseString.begin(), lowerCaseString.end(), lowerCaseString.begin(), tolower);
        return lowerCaseString;
    }
}

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
                        std::string lowerCaseTag = GetLowerCaseString(it->first);
                        m_searchTagToYelpRootCategoryModel[lowerCaseTag].yelpCategoryFilter = it->second;
                        m_searchTagToYelpRootCategoryModel[lowerCaseTag].skipYelpSearch = false;
                    }
                }
                
                SearchTagToYelpCategoryMapper::~SearchTagToYelpCategoryMapper()
                {
                    m_yelpCategoryMapperUpdater.UnregisterMappingReset(m_yelpCategoryMapperResetCallback);
                    m_yelpCategoryMapperUpdater.UnregisterMappingAdded(m_yelpCategoryMapperChangedCallback);
                }
                
                void SearchTagToYelpCategoryMapper::AddMapping(const std::string& tag, const YelpCategoryModel& yelpCategoryModel)
                {
                    m_searchTagToYelpRootCategoryModel[GetLowerCaseString(tag)] = yelpCategoryModel;
                }

                void SearchTagToYelpCategoryMapper::RemoveMapping(const std::string& tag)
                {
                    m_searchTagToYelpRootCategoryModel.erase(GetLowerCaseString(tag));
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
                        std::string lowerCaseTag = GetLowerCaseString(it->first);
                        m_searchTagToYelpRootCategoryModel[lowerCaseTag].yelpCategoryFilter = it->second;
                        m_searchTagToYelpRootCategoryModel[lowerCaseTag].skipYelpSearch = false;
                    }
                }
                
                bool SearchTagToYelpCategoryMapper::TryGetBestYelpCategoryForSearchTag(const std::string& searchTag, YelpCategoryModel& out_bestMatchedYelpCategoryModel)
                {
                    std::string lowerCaseTag = GetLowerCaseString(searchTag);
                    for(int i = 0; i < m_searchTagToYelpRootCategoryModel.size(); i++)
                    {
                        YelpCategoryModel value = m_searchTagToYelpRootCategoryModel[lowerCaseTag];
                        if (!value.yelpCategoryFilter.empty() || lowerCaseTag.empty())
                        {
                            out_bestMatchedYelpCategoryModel = value;
                            return true;
                        }
                    }
                    YelpCategoryModel defaultValue { m_defaultTag, false };
                    out_bestMatchedYelpCategoryModel = defaultValue;
                    return false;
                }

            }
        }
    }
}
