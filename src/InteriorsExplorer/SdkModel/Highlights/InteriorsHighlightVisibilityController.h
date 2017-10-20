// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Search.h"
#include "Interiors.h"
#include "IPersistentSettingsModel.h"
#include "InteriorsExplorer.h"
#include "Rendering.h"
#include "BidirectionalBus.h"
#include "ILabelAnchorFilter.h"
#include "HighlightColorMapper.h"
#include "VectorMath.h"

#include <string>
#include <vector>
#include <map>
#include <unordered_set>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                
                class InteriorsHighlightVisibilityController : protected Eegeo::NonCopyable
                {
                public:
                    InteriorsHighlightVisibilityController(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                           Eegeo::Resources::Interiors::InteriorsCellResourceObserver& interiorsCellResourceObserver,
                                                           Search::SdkModel::ISearchService& searchService,
                                                           Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                           Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                                           Eegeo::Labels::ILabelAnchorFilterModel& labelHiddenFilterModel,
                                                           const Eegeo::Labels::LabelLayer::IdType interiorLabelLayer,
                                                           ExampleAppMessaging::TMessageBus& messageBus,
                                                           IHighlightColorMapper& highlightColorMapper,
                                                           Eegeo::Resources::Interiors::Highlights::IInteriorsHighlightService& interiorsHighlightService);
                    
                    ~InteriorsHighlightVisibilityController();
                    
                private:
                    typedef std::unordered_set<std::string> SearchResultLabelNameSet;
                    typedef std::vector<Eegeo::Rendering::Renderables::InteriorHighlightRenderable*> HighlightRenderableVector;
                    typedef std::map<std::string, Eegeo::v4> HighlightIdToColor;
                    typedef std::map<std::string, Eegeo::v4> AvailabilityToColor;
                    
                    static AvailabilityToColor BuildAvailabilityToColor();
                    
                    void OnSearchResultsLoaded(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results);
                    void OnSearchResultCleared();
                    void OnSearchItemSelected(const SearchResultSection::SearchResultSectionItemSelectedMessage& message);
                    void OnInteriorChanged();
                    void OnInteriorAddedToSceneGraph(const Eegeo::Resources::Interiors::InteriorsCellResource& callback);
                    
                    Eegeo::v4 GetColorForAvailability(const std::string& availability) const;
                    void GetCurrentSearchResults(std::vector<Search::SdkModel::SearchResultModel>& out_results) const;
                    
                    void PopulateHighlightRenderables();
                    void ClearHighlightRenderables();
                    
                    void RefreshForSearchResults(const std::vector<Search::SdkModel::SearchResultModel>& results);
                    void RefreshHighlightsColor();
                    
                    bool HideLabelAlwaysPredicate(const Eegeo::Labels::IAnchoredLabel& anchoredLabel) const;
                    
                    Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                    Eegeo::Resources::Interiors::InteriorsCellResourceObserver& m_interiorsCellResourceObserver;
                    Eegeo::Labels::ILabelAnchorFilterModel& m_labelHiddenFilterModel;
                    const Eegeo::Labels::LabelLayer::IdType m_interiorLabelLayer;
                    Search::SdkModel::ISearchService& m_searchService;
                    Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                    Search::SdkModel::ISearchResultRepository& m_searchResultRepository;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    IHighlightColorMapper& m_highlightColorMapper;
                    Eegeo::Resources::Interiors::Highlights::IInteriorsHighlightService& m_interiorsHighlightService;
                    const AvailabilityToColor m_availabilityToColor;
                    std::vector<Search::SdkModel::SearchResultModel> m_searchResults;
                    int m_searchResultsIndex;

                    Eegeo::Helpers::TCallback2<InteriorsHighlightVisibilityController, const Search::SdkModel::SearchQuery&, const std::vector<Search::SdkModel::SearchResultModel>&> m_searchResultsHandler;
                    Eegeo::Helpers::TCallback1<InteriorsHighlightVisibilityController, const Eegeo::Resources::Interiors::InteriorsCellResource> m_interiorCellAddedHandler;
                    Eegeo::Helpers::TCallback0<InteriorsHighlightVisibilityController> m_searchResultsClearedHandler;
                    Eegeo::Helpers::TCallback0<InteriorsHighlightVisibilityController> m_interiorInteractionModelChangedHandler;
                    Eegeo::Helpers::TCallback1<InteriorsHighlightVisibilityController, const SearchResultSection::SearchResultSectionItemSelectedMessage&> m_handleSearchResultSectionItemSelectedMessageBinding;
                    Eegeo::Labels::TLabelAnchorFilter<InteriorsHighlightVisibilityController> m_hideLabelAlwaysFilter;
                    
                    HighlightRenderableVector m_highlightRenderablesForInterior;
                    HighlightIdToColor m_searchResultHighlightIdToColor;
                };
            }
        }
    }
}

