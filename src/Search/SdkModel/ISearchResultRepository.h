// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "IRepositoryModel.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            class ISearchResultRepository : public Repository::IRepositoryModel<SearchResultModel*>
            {
            public:
                virtual ~ISearchResultRepository() { }

                virtual void RemoveFirstResultWithIdentifier(const std::string& identifier) = 0;
            };
        }
    }
}
