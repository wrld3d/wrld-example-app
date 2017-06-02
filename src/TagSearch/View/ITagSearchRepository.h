// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "TagSearch.h"
#include "TagSearchModel.h"
#include "Search.h"
#include "RepositoryModel.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
            class ITagSearchRepository : public Repository::IRepositoryModel<TagSearchModel>
            {
            public:
                virtual ~ITagSearchRepository() { }

                virtual bool TryGetTagSearchNameByQuery(const std::string& query, std::string& out_name) = 0;

                virtual void ForceRefresh() = 0;
            };
            
            std::string GetTagSearchNameByQuery(const std::string& query);

            std::string GetPresentationStringForQuery(ITagSearchRepository& tagSearchRepository, const Search::SdkModel::SearchQuery& query);
        }
    }
}
