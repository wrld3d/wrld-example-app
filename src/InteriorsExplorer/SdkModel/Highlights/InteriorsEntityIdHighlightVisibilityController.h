// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Search.h"
#include "Interiors.h"
#include "InteriorsExplorer.h"
#include "Rendering.h"
#include "InteriorsEntityIdHighlightController.h"
#include "VectorMath.h"

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
                    InteriorsEntityIdHighlightVisibilityController(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                           Search::SdkModel::ISearchService& searchService,
                                                           Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                           Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                                           const Eegeo::Resources::Interiors::InteriorsInstanceRepository& instanceRepository,
                                                           const Eegeo::v4& defaultHighlightColor);
                    
                    ~InteriorsEntityIdHighlightVisibilityController();
                    
                private:
                    void OnSearchPerformed(const Search::SdkModel::SearchQuery& query);
                    void OnSearchResultsLoaded(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results);
                    void OnSearchResultCleared();
                    
                    void OnInteriorVisibilityChanged();
                    
                    Eegeo::Resources::Interiors::InteriorController& m_interiorController;
                    Search::SdkModel::ISearchService& m_searchService;
                    Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                    Search::SdkModel::ISearchResultRepository& m_searchResultRepository;

                    Eegeo::Helpers::TCallback1<InteriorsEntityIdHighlightVisibilityController, const Search::SdkModel::SearchQuery&> m_searchPerformedHandler;
                    Eegeo::Helpers::TCallback2<InteriorsEntityIdHighlightVisibilityController, const Search::SdkModel::SearchQuery&, const std::vector<Search::SdkModel::SearchResultModel>&> m_searchResultsHandler;
                    Eegeo::Helpers::TCallback0<InteriorsEntityIdHighlightVisibilityController> m_searchResultsClearedHandler;
                    Eegeo::Helpers::TCallback0<InteriorsEntityIdHighlightVisibilityController> m_interiorVisibilityChangedHandler;

                    typedef Eegeo::Resources::Interiors::InteriorsEntityIdHighlightController Super;
                };
            }
        }
    }
}

