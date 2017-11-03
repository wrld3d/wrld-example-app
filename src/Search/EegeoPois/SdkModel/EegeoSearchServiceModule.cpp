// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoSearchServiceModule.h"

#include "EegeoJsonParser.h"
#include "EegeoSearchQueryFactory.h"
#include "EegeoSearchService.h"
#include "EegeoTagIconMapper.h"
#include "SwallowSearchConstants.h"
#include "EegeoReadableTagMapper.h"
#include "EegeoTagIconMapperFactory.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                EegeoSearchServiceModule::EegeoSearchServiceModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                                   Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                                                   Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                                                   const Search::SdkModel::SearchTags& searchTags,
                                                                   const Search::SdkModel::SearchTags& swallowSearchTags,
                                                                   const std::vector<std::string>& handledTags,
                                                                   const std::string& serviceUrl,
                                                                   const Eegeo::Web::ApiTokenModel& apiTokenModel,
                                                                   const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel)
                : m_pEegeoSearchQueryFactory(NULL)
                , m_pEegeoParser(NULL)
                , m_pSearchService(NULL)
                , m_pTagIconMapper(NULL)
                {
                    m_pEegeoSearchQueryFactory = Eegeo_NEW(EegeoSearchQueryFactory)(webRequestFactory,
                                                                                    urlEncoder,
                                                                                    interiorInteractionModel,
                                                                                    serviceUrl,
                                                                                    apiTokenModel);

                    m_pTagIconMapper = TagSearch::SdkModel::CreateTagIconMapper(searchTags);

                    m_pReadableTagMapper = Eegeo_NEW(EegeoReadableTagMapper)(searchTags);

                    m_pSwallowTagIconMapper = TagSearch::SdkModel::CreateTagIconMapper(swallowSearchTags);

                    m_pSwallowReadableTagMapper = Eegeo_NEW(EegeoReadableTagMapper)(swallowSearchTags);

                    m_pEegeoParser = Eegeo_NEW(EegeoJsonParser)(*m_pTagIconMapper, *m_pReadableTagMapper, *m_pSwallowTagIconMapper, *m_pSwallowReadableTagMapper);

                    m_pSearchService = Eegeo_NEW(EegeoSearchService)(*m_pEegeoSearchQueryFactory,
                                                                     *m_pEegeoParser,
                                                                     networkCapabilities,
                                                                     handledTags);
                }
                
                EegeoSearchServiceModule::~EegeoSearchServiceModule()
                {
                    Eegeo_DELETE m_pSearchService;
                    Eegeo_DELETE m_pEegeoParser;
                    Eegeo_DELETE m_pSwallowTagIconMapper;
                    Eegeo_DELETE m_pSwallowReadableTagMapper;
                    Eegeo_DELETE m_pTagIconMapper;
                    Eegeo_DELETE m_pReadableTagMapper;
                    Eegeo_DELETE m_pEegeoSearchQueryFactory;
                }
                
                Search::SdkModel::ISearchService& EegeoSearchServiceModule::GetSearchService() const
                {
                    return *m_pSearchService;
                }

                std::vector<TagSearch::View::TagSearchModel> EegeoSearchServiceModule::GetTagSearchModels() const
                {
                    return std::vector<TagSearch::View::TagSearchModel>();
                }
            }
        }
    }
}
