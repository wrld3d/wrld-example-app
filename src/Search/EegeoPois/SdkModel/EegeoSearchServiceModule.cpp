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
                EegeoSearchServiceModule::EegeoSearchServiceModule(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
                : m_builder(builder)
                {
                }
                
                void EegeoSearchServiceModule::Register()
                {
                    m_builder->registerType<EegeoSearchQueryFactory>().as<IEegeoSearchQueryFactory>().singleInstance();
                    m_builder->registerType<EegeoCategoryIconMapper>().as<SearchResultPoi::SdkModel::ICategoryIconMapper>().singleInstance();
                    m_builder->registerType<EegeoReadableTagMapper>().singleInstance();
                    m_builder->registerType<EegeoJsonParser>().as<IEegeoParser>().singleInstance();
                    m_builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
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
