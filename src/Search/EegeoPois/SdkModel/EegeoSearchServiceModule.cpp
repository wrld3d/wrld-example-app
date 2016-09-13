// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoSearchServiceModule.h"

#include "EegeoJsonParser.h"
#include "EegeoSearchQueryFactory.h"
#include "EegeoSearchService.h"
#include "EegeoTagIconMapper.h"
#include "EegeoReadableTagMapper.h"
#include "YelpSearchConstants.h"
#include "IWebLoadRequestFactory.h"
#include "InteriorInteractionModel.h"
#include "INetworkCapabilities.h"
#include "SearchTagsFactory.h"

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
                    builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                     {
                                                         auto searchTags = std::make_shared<Search::SdkModel::SearchTagRepository>();
                                                         Search::SdkModel::PopulateSearchTagsFromFile(*context.resolve<Eegeo::Helpers::IFileIO>(), "search_tags.json", *searchTags);
                                                         return searchTags;
                                                     }).singleInstance();
                    builder->registerType<EegeoTagIconMapper>().as<SearchResultPoi::SdkModel::ITagIconMapper>().singleInstance();
                    builder->registerType<EegeoReadableTagMapper>().singleInstance();
                    builder->registerType<EegeoJsonParser>().as<IEegeoParser>().singleInstance();
                    builder->registerType<EegeoSearchService>().singleInstance();
                }
            }
        }
    }
}
