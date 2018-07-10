// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Search.h"
#include "Interiors.h"
#include "InteriorsExplorer.h"
#include "Rendering.h"
#include "BidirectionalBus.h"
#include "ILabelAnchorFilter.h"
#include "HighlightColorMapper.h"

#include <string>
#include <vector>
#include <map>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                
                class InteriorEntityHighlightController : protected Eegeo::NonCopyable
                {
                public:
                    InteriorEntityHighlightController(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                           Eegeo::Resources::Interiors::InteriorsCellResourceObserver& interiorsCellResourceObserver,
                                                           Search::SdkModel::ISearchService& searchService,
                                                           Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                           Eegeo::Resources::Interiors::Entities::IInteriorsLabelController& legacyLabelController,
                                                           Eegeo::Labels::ILabelAnchorFilterModel& labelHiddenFilterModel,
                                                           const Eegeo::Labels::LabelLayer::IdType interiorLabelLayer,
                                                           ExampleAppMessaging::TMessageBus& messageBus,
                                                           IHighlightColorMapper& highlightColorMapper,
                                                           Eegeo::Resources::Interiors::Highlights::IInteriorsHighlightService& interiorsHighlightService);
                    
                    ~InteriorEntityHighlightController();
                    
                    void HighlightResultWithId(const std::string& id);
                    
                private:
                    void OnSearchQueryResponseReceived(const Search::SearchQueryResponseReceivedMessage& message);
                    void OnSearchResultCleared();
                    void OnSearchItemSelected(const SearchResultSection::SearchResultSectionItemSelectedMessage& message);
                    void OnInteriorChanged();
                    void OnInteriorAddedToSceneGraph(const Eegeo::Resources::Interiors::InteriorsCellResource& callback);
                    void OnInteriorLabelsBuilt();
                    void OnAvailabilityChanged();
                    
                    void RemoveHighlights();
                    void AddHighlight(Eegeo::Rendering::Renderables::InteriorHighlightRenderable& renderable);
                    
                    std::vector<Search::SdkModel::SearchResultModel> GetCurrentSearchResults();
                    void ApplyHighlightsForCurrentResults();
                    void ApplyHighlights(const std::vector<Search::SdkModel::SearchResultModel>& results);
                    void HighlightSearchResult(const Search::SdkModel::SearchResultModel &result);
                    void ActivateLabels(bool active);
                    
                    bool HideLabelAlwaysPredicate(const Eegeo::Labels::IAnchoredLabel& anchoredLabel) const;
                    bool HideLabelByNamePredicate(const Eegeo::Labels::IAnchoredLabel& anchoredLabel) const;
                    
                    Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                    Eegeo::Resources::Interiors::InteriorsCellResourceObserver& m_interiorsCellResourceObserver;
                    
                    Eegeo::Labels::ILabelAnchorFilterModel& m_labelHiddenFilterModel;
                    const Eegeo::Labels::LabelLayer::IdType m_interiorLabelLayer;
                    Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                    IHighlightColorMapper& m_highlightColorMapper;
                    Eegeo::Resources::Interiors::Highlights::IInteriorsHighlightService& m_interiorsHighlightService;
                    std::vector<Search::SdkModel::SearchResultModel> m_searchResults;
                    int m_searchResultsIndex;
                    
                    Eegeo::Helpers::TCallback1<InteriorEntityHighlightController, const Search::SearchQueryResponseReceivedMessage&>
                    m_searchQueryResponseHandler;
                    Eegeo::Helpers::TCallback1<InteriorEntityHighlightController, const Eegeo::Resources::Interiors::InteriorsCellResource> m_interiorCellAddedHandler;
                    Eegeo::Helpers::TCallback0<InteriorEntityHighlightController> m_searchResultsClearedHandler;
                    Eegeo::Helpers::TCallback0<InteriorEntityHighlightController> m_interiorInteractionModelChangedHandler;
                    Eegeo::Helpers::TCallback0<InteriorEntityHighlightController> m_interiorLabelsBuiltHandler;
                    
                    Eegeo::Helpers::TCallback0<InteriorEntityHighlightController> m_availabilityChangedHandlerBinding;
                    Eegeo::Helpers::TCallback1<InteriorEntityHighlightController, const SearchResultSection::SearchResultSectionItemSelectedMessage&> m_handleSearchResultSectionItemSelectedMessageBinding;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    
                    std::map<std::string, std::vector<Eegeo::Rendering::Renderables::InteriorHighlightRenderable*>> m_currentHighlightRenderables;
                    
                    Eegeo::Labels::TLabelAnchorFilter<InteriorEntityHighlightController> m_hideLabelAlwaysFilter;
                    Eegeo::Labels::TLabelAnchorFilter<InteriorEntityHighlightController> m_hideLabelByNameFilter;
                };
            }
        }
    }
}

