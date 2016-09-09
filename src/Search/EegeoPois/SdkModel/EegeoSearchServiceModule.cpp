// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoSearchServiceModule.h"

#include "EegeoJsonParser.h"
#include "EegeoSearchQueryFactory.h"
#include "EegeoSearchService.h"
#include "EegeoCategoryIconMapper.h"
#include "EegeoReadableTagMapper.h"
#include "YelpSearchConstants.h"
#include "IWebLoadRequestFactory.h"
#include "InteriorInteractionModel.h"
#include "INetworkCapabilities.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                void EegeoSearchServiceModule::Register(const TContainerBuilder& builder)
                {
                    builder->registerType<EegeoSearchQueryFactory>().as<IEegeoSearchQueryFactory>().singleInstance();
                    builder->registerType<EegeoCategoryIconMapper>().as<SearchResultPoi::SdkModel::ICategoryIconMapper>().singleInstance();
                    builder->registerType<EegeoReadableTagMapper>().singleInstance();
                    builder->registerType<EegeoJsonParser>().as<IEegeoParser>().singleInstance();
                    builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                       {
                                                           std::vector<std::string> supportedCategories = Search::Yelp::SearchConstants::GetCategories();
                                                           return std::make_shared<EegeoSearchService>(
                                                                context.resolve<IEegeoSearchQueryFactory>(),
                                                                context.resolve<IEegeoParser>(),
                                                                context.resolve<Net::SdkModel::INetworkCapabilities>(),
                                                                supportedCategories
                                                           );
                                                       }).singleInstance();
                }
            }
        }
    }
}
