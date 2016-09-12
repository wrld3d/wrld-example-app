// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "YelpSearchServiceModule.h"
#include "YelpSearchJsonParser.h"
#include "YelpBusinessJsonParser.h"
#include "YelpSearchService.h"
#include "YelpCategoryMapper.h"
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
                                                       return std::make_shared<Yelp::SdkModel::YelpCategoryMapper>(
                                                            context.resolve<Eegeo::Web::IWebLoadRequestFactory>(),
                                                            Yelp::SearchConstants::GetYelpFoundationCategoryToApplicationCategoryMap(*(context.resolve<Eegeo::Helpers::IFileIO>())),
                                                            Yelp::SearchConstants::GetDefaultCategory()
                                                       );
                                                   }).as<Yelp::SdkModel::IYelpCategoryMapper>().singleInstance();
                builder->registerType<Yelp::SdkModel::YelpSearchJsonParser>().singleInstance();
                builder->registerType<Yelp::SdkModel::YelpBusinessJsonParser>().singleInstance();
                builder->registerType<Yelp::SdkModel::YelpSearchQueryFactory>().singleInstance();
                builder->registerType<Yelp::SdkModel::YelpBusinessQueryFactory>().singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       return std::make_shared<Yelp::SdkModel::YelpSearchService>(
                                                            context.resolve<Yelp::SdkModel::YelpSearchQueryFactory>(),
                                                            context.resolve<Yelp::SdkModel::YelpBusinessQueryFactory>(),
                                                            context.resolve<Yelp::SdkModel::YelpSearchJsonParser>(),
                                                            context.resolve<Net::SdkModel::INetworkCapabilities>(),
                                                            Yelp::SearchConstants::GetCategories()
                                                       );
                                                   }).singleInstance();
            }
        }
    }
}