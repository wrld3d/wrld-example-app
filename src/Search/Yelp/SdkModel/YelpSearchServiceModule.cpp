// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "YelpSearchServiceModule.h"
#include "YelpSearchJsonParser.h"
#include "YelpBusinessJsonParser.h"
#include "YelpSearchService.h"
#include "YelpCategoryToTagMapper.h"
#include "YelpSearchConstants.h"
#include "YelpSearchQueryFactory.h"
#include "YelpBusinessQueryFactory.h"
#include "INetworkCapabilities.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            void YelpSearchServiceModule::Register(const TContainerBuilder& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto yelpData = std::make_shared<SearchConstants::YelpCategoryMappingData>();
                                                     const std::vector<std::string> appTags; //TODO: replace...
                                                     SearchConstants::ParseYelpDataInPlace(*context.resolve<Eegeo::Helpers::IFileIO>(), appTags, "yelp_map.json", *yelpData);
                                                     return yelpData;
                                                 }).singleInstance();
                builder->registerType<Yelp::SdkModel::YelpCategoryToTagMapper>().as<Yelp::SdkModel::IYelpCategoryToTagMapper>().singleInstance();
                builder->registerType<Yelp::SdkModel::YelpSearchJsonParser>().singleInstance();
                builder->registerType<Yelp::SdkModel::YelpBusinessJsonParser>().singleInstance();
                builder->registerType<Yelp::SdkModel::YelpSearchQueryFactory>().singleInstance();
                builder->registerType<Yelp::SdkModel::YelpBusinessQueryFactory>().singleInstance();
                builder->registerType<Yelp::SdkModel::YelpSearchService>().singleInstance();
            }
        }
    }
}