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
                                                                   const std::vector<std::string>& handledTags,
                                                                   const std::string& serviceUrl,
                                                                   const std::string& apiKey,
                                                                   const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                   ExampleApp::PersistentSettings::IPersistentSettingsModel& persistentSettings)
                : m_pEegeoSearchQueryFactory(NULL)
                , m_pEegeoParser(NULL)
                , m_pSearchService(NULL)
                , m_pTagIconMapper(NULL)
                {
                    m_pEegeoSearchQueryFactory = Eegeo_NEW(EegeoSearchQueryFactory)(webRequestFactory,
                                                                                    urlEncoder,
                                                                                    interiorInteractionModel,
                                                                                    serviceUrl,
                                                                                    apiKey);

                    m_pTagIconMapper = TagSearch::SdkModel::CreateTagIconMapper(searchTags);

                    m_pReadableTagMapper = Eegeo_NEW(EegeoReadableTagMapper)(searchTags);

                    m_pEegeoParser = Eegeo_NEW(EegeoJsonParser)(*m_pTagIconMapper, *m_pReadableTagMapper, persistentSettings);

                    m_pSearchService = Eegeo_NEW(EegeoSearchService)(*m_pEegeoSearchQueryFactory,
                                                                     *m_pEegeoParser,
                                                                     networkCapabilities,
                                                                     handledTags);
                }
                
                EegeoSearchServiceModule::~EegeoSearchServiceModule()
                {
                    Eegeo_DELETE m_pSearchService;
                    Eegeo_DELETE m_pEegeoParser;
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
