// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "ISearchTagToYelpCategoryMapper.h"
#include "YelpCategoryMapperUpdater.h"
#include "YelpCategoryModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                class SearchTagToYelpCategoryMapper : public ISearchTagToYelpCategoryMapper
                {
                public:
                    SearchTagToYelpCategoryMapper(const std::map<std::string, std::string>& appTagToYelpCategoryMap,
                                                  Search::Yelp::SdkModel::YelpCategoryMapperUpdater& yelpCategoryMapperUpdater,
                                                  const std::string& defaultTag);
                    ~SearchTagToYelpCategoryMapper();

                    bool TryGetBestYelpCategoryForSearchTag(const std::string& searchTag,
                                                            YelpCategoryModel& out_bestMatchingYelpCategory);
                    
                    void AddMapping(const std::string& tag, const YelpCategoryModel& yelpCategoryModel);
                    void RemoveMapping(const std::string& tag);
                    void OnYelpCategoryMapperAdded(const std::string& tag, const YelpCategoryModel& yelpCategoryModel);
                    void OnYelpCategoryMapperReset();

                private:
                    const std::map<std::string, std::string> m_appTagToYelpCategoryMap;
                    std::map<std::string, YelpCategoryModel> m_searchTagToYelpRootCategoryModel;
                    Eegeo::Helpers::TCallback2<SearchTagToYelpCategoryMapper, const std::string, const YelpCategoryModel> m_yelpCategoryMapperChangedCallback;
                    Eegeo::Helpers::TCallback0<SearchTagToYelpCategoryMapper> m_yelpCategoryMapperResetCallback;
                    Search::Yelp::SdkModel::YelpCategoryMapperUpdater& m_yelpCategoryMapperUpdater;
                    const std::string m_defaultTag;
                };
            }
        }
    }
}
