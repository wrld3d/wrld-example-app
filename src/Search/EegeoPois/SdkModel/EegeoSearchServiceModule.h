// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "ISearchServiceModule.h"

#include "Types.h"
#include "UrlHelpers.h"
#include "Web.h"
#include "Helpers.h"
#include "EegeoPois.h"
#include "NetIncludes.h"
#include "Search.h"
#include "Interiors.h"
#include "ITagIconMapper.h"
#include "SearchTags.h"

#include <vector>
#include <string>

#include "IPersistentSettingsModel.h"
#include "Helpers.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                class EegeoSearchServiceModule : public Search::SdkModel::ISearchServiceModule, private Eegeo::NonCopyable
                {
                private:
                    IEegeoSearchQueryFactory* m_pEegeoSearchQueryFactory;
                    IEegeoParser* m_pEegeoParser;
                    Search::SdkModel::ISearchService* m_pSearchService;

                    TagSearch::SdkModel::ITagIconMapper *m_pTagIconMapper;
                    EegeoReadableTagMapper *m_pReadableTagMapper;
                    
                public:
                    EegeoSearchServiceModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                             Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                             Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                             const Search::SdkModel::SearchTags& searchTags,
                                             const std::string& serviceUrl,
                                             const std::string& apiKey,
                                             const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                             ExampleApp::PersistentSettings::IPersistentSettingsModel& persistentSettings);
                    
                    ~EegeoSearchServiceModule();
                    
                    Search::SdkModel::ISearchService& GetSearchService() const;

                    std::vector<TagSearch::View::TagSearchModel> GetTagSearchModels() const;
                };
            }
        }
    }
}