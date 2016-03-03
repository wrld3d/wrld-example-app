// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Search.h"
#include "Interiors.h"
#include "InteriorsExplorer.h"
#include "Rendering.h"
#include "InteriorsEntityIdHighlightController.h"
#include "VectorMath.h"
#include "BidirectionalBus.h"
#include "SearchResultSectionItemSelectedMessage.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                
                class InteriorsEntityIdHighlightVisibilityController : public Eegeo::Resources::Interiors::InteriorsEntityIdHighlightController
                {
                public:
                    InteriorsEntityIdHighlightVisibilityController(Search::SdkModel::ISearchService& searchService,
                                                           Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                           Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                                           const Eegeo::Resources::Interiors::InteriorsInstanceRepository& instanceRepository,
                                                           ExampleAppMessaging::TMessageBus& messageBus,
                                                           const Eegeo::v4& defaultHighlightColor);
                    
                    ~InteriorsEntityIdHighlightVisibilityController();
                    
                private:
                    void OnSearchResultsLoaded(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results);
                    void OnSearchResultCleared();
                    void OnSearchItemSelected(const SearchResultSection::SearchResultSectionItemSelectedMessage& message);
                    
                    Eegeo::Resources::Interiors::CountPerRenderable m_lastHighlightedRenderables;
                    std::map<int, std::vector<std::string> > m_lastSearchedResults;
                    
                    Search::SdkModel::ISearchService& m_searchService;
                    Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;

                    ExampleAppMessaging::TMessageBus& m_messageBus;

                    Eegeo::Helpers::TCallback1<InteriorsEntityIdHighlightVisibilityController, const SearchResultSection::SearchResultSectionItemSelectedMessage&> m_handleSearchResultSectionItemSelectedMessageBinding;
                    Eegeo::Helpers::TCallback2<InteriorsEntityIdHighlightVisibilityController, const Search::SdkModel::SearchQuery&, const std::vector<Search::SdkModel::SearchResultModel>&> m_searchResultsHandler;
                    Eegeo::Helpers::TCallback0<InteriorsEntityIdHighlightVisibilityController> m_searchResultsClearedHandler;

                    typedef Eegeo::Resources::Interiors::InteriorsEntityIdHighlightController Super;
                };
            }
        }
    }
}

