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
            YelpSearchServiceModule::YelpSearchServiceModule(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            : m_builder(builder)
            {
            }
            
            void YelpSearchServiceModule::Register()
            {
                m_builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       return std::make_shared<Yelp::SdkModel::YelpCategoryMapper>(
                                                            context.resolve<Eegeo::Web::IWebLoadRequestFactory>(),
                                                            Yelp::SearchConstants::GetYelpFoundationCategoryToApplicationCategoryMap(*(context.resolve<Eegeo::Helpers::IFileIO>())),
                                                            Yelp::SearchConstants::GetDefaultCategory()
                                                       );
                                                   }).singleInstance();
                m_builder->registerType<Yelp::SdkModel::YelpSearchJsonParser>().singleInstance();
                m_builder->registerType<Yelp::SdkModel::YelpBusinessJsonParser>().singleInstance();
                m_builder->registerType<Yelp::SdkModel::YelpSearchQueryFactory>().singleInstance();
                m_builder->registerType<Yelp::SdkModel::YelpBusinessQueryFactory>().singleInstance();
                m_builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
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