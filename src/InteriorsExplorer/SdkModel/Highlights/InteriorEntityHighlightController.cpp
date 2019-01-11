// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorEntityHighlightController.h"
#include "ISearchService.h"
#include "ISearchQueryPerformer.h"
#include "ISearchResultRepository.h"
#include "InteriorInteractionModel.h"
#include "InteriorsModel.h"
#include "InteriorsFloorModel.h"
#include "IInteriorsLabelController.h"
#include "VectorMath.h"
#include "InteriorHighlightRenderable.h"
#include "InteriorsLabelParser.h"
#include "InteriorsFloorCells.h"
#include "InteriorsFloorCell.h"
#include "PlaceNameModel.h"
#include "InteriorsCellResource.h"
#include "InteriorsCellResourceObserver.h"
#include "LabelAnchorFilterModel.h"
#include "IAnchoredLabel.h"
#include "document.h"
#include "IInteriorsHighlightService.h"
#include "InteriorEntityHighlightHelpers.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                InteriorEntityHighlightController::InteriorEntityHighlightController(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                                               Eegeo::Resources::Interiors::InteriorsCellResourceObserver& interiorsCellResourceObserver,
                                                                                               Search::SdkModel::ISearchService& searchService,
                                                                                               Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer, Eegeo::Resources::Interiors::Entities::IInteriorsLabelController& legacyLabelController,
                                                                                               Eegeo::Labels::ILabelAnchorFilterModel& labelHiddenFilterModel,
                                                                                               const Eegeo::Labels::LabelLayer::IdType interiorLabelLayer,
                                                                                               ExampleAppMessaging::TMessageBus& messageBus,
                                                                                               IHighlightColorMapper& highlightColorMapper,
                                                                                               Eegeo::Resources::Interiors::Highlights::IInteriorsHighlightService& interiorsHighlightService)
                : m_interiorInteractionModel(interiorInteractionModel)
                , m_interiorsCellResourceObserver(interiorsCellResourceObserver)
                , m_interiorLabelLayer(interiorLabelLayer)
                , m_labelHiddenFilterModel(labelHiddenFilterModel)
                , m_searchQueryPerformer(searchQueryPerformer)
                , m_highlightColorMapper(highlightColorMapper)
                , m_searchResultsIndex(-1)
                , m_searchQueryResponseHandler(this, &InteriorEntityHighlightController::OnSearchQueryResponseReceived)
                , m_searchResultsClearedHandler(this, &InteriorEntityHighlightController::OnSearchResultCleared)
                , m_handleSearchResultSectionItemSelectedMessageBinding(this, &InteriorEntityHighlightController::OnSearchItemSelected)
                , m_interiorInteractionModelChangedHandler(this, &InteriorEntityHighlightController::OnInteriorChanged)
                , m_interiorCellAddedHandler(this, &InteriorEntityHighlightController::OnInteriorAddedToSceneGraph)
                , m_availabilityChangedHandlerBinding(this, &InteriorEntityHighlightController::OnAvailabilityChanged)
                , m_interiorLabelsBuiltHandler(this, &InteriorEntityHighlightController::OnInteriorLabelsBuilt)
                , m_interiorsHighlightService(interiorsHighlightService)
                , m_messageBus(messageBus)
                , m_hideLabelAlwaysFilter(this, &InteriorEntityHighlightController::HideLabelAlwaysPredicate)
                , m_hideLabelByNameFilter(this, &InteriorEntityHighlightController::HideLabelByNamePredicate)
                {
                    m_messageBus.SubscribeUi(m_searchQueryResponseHandler);
                    m_searchQueryPerformer.InsertOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_interiorInteractionModel.RegisterModelChangedCallback(m_interiorInteractionModelChangedHandler);
                    
                    m_interiorsCellResourceObserver.RegisterAddedToSceneGraphCallback(m_interiorCellAddedHandler);
                    m_messageBus.SubscribeNative(m_handleSearchResultSectionItemSelectedMessageBinding);
                    m_labelHiddenFilterModel.SetFilter(m_interiorLabelLayer, &m_hideLabelAlwaysFilter);
                }
                
                InteriorEntityHighlightController::~InteriorEntityHighlightController()
                {
                    m_interiorsCellResourceObserver.UnregisterAddedToSceneGraphCallback(m_interiorCellAddedHandler);
                    
                    m_messageBus.UnsubscribeUi(m_searchQueryResponseHandler);
                    
                    m_searchQueryPerformer.RemoveOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_interiorInteractionModel.UnregisterModelChangedCallback(m_interiorInteractionModelChangedHandler);
                    
                    m_messageBus.UnsubscribeNative(m_handleSearchResultSectionItemSelectedMessageBinding);
                }
                
                void InteriorEntityHighlightController::OnAvailabilityChanged()
                {
                }
                
                void InteriorEntityHighlightController::RemoveHighlights()
                {
                    m_interiorsHighlightService.ClearAllHighlights();
                    
                }
                
                void InteriorEntityHighlightController::ActivateLabels(bool active)
                {
                    m_labelHiddenFilterModel.SetFilter(m_interiorLabelLayer, active ? NULL : &m_hideLabelByNameFilter);
                }
                
                void InteriorEntityHighlightController::OnInteriorLabelsBuilt()
                {
                    ApplyHighlightsForCurrentResults();
                    bool hasResults = m_searchResults.size() > 0;
                    ActivateLabels(!hasResults);
                }
                
                void InteriorEntityHighlightController::OnSearchResultCleared()
                {
                    m_searchResultsIndex = -1;
                    m_searchResults.clear();
                    RemoveHighlights();
                    ApplyHighlightsForCurrentResults();
                    ActivateLabels(true);
                }
                
                void InteriorEntityHighlightController::HighlightResultWithId(const std::string& id)
                {
                    int resultIndex = -1;
                    for(int i = 0; i < m_searchResults.size(); ++i)
                    {
                        auto& searchResult = m_searchResults.at(i);
                        if(searchResult.GetIdentifier() == id)
                        {
                            resultIndex = i;
                            break;
                        }
                    }
                    
                    m_searchResultsIndex = resultIndex;
                    
                    ApplyHighlightsForCurrentResults();
                }
                
                void InteriorEntityHighlightController::OnSearchItemSelected(const SearchResultSection::SearchResultSectionItemSelectedMessage& message)
                {
                    if (message.ItemIndex() >= m_searchResults.size())
                    {
                        m_searchResultsIndex = -1;
                    }
                    else
                    {
                        m_searchResultsIndex = message.ItemIndex();
                    }
                    
                    ApplyHighlightsForCurrentResults();
                }
                
                void InteriorEntityHighlightController::OnInteriorChanged()
                {
                    namespace EegeoInteriors = Eegeo::Resources::Interiors;
                    namespace EegeoRenderables = Eegeo::Rendering::Renderables;
                    
                    RemoveHighlights();
                    m_currentHighlightRenderables.clear();
                    
                    if (m_interiorInteractionModel.HasInteriorModel())
                    {
                        const EegeoInteriors::InteriorsModel& model = *m_interiorInteractionModel.GetInteriorModel();
                        
                        for (EegeoInteriors::TFloorModelVector::const_iterator floors = model.GetFloors().begin();
                             floors != model.GetFloors().end();
                             ++floors)
                        {
                            const EegeoInteriors::InteriorsFloorCells* floorCells = model.GetFloorCells((*floors)->GetFloorNumber());
                            
                            for (int cellIndex = 0; cellIndex < floorCells->GetCellCount(); ++cellIndex)
                            {
                                const EegeoInteriors::InteriorsFloorCell* cell = floorCells->GetFloorCells()[cellIndex];
                                std::vector<EegeoRenderables::InteriorHighlightRenderable*> renderables = cell->GetHighlightRenderables();
                                
                                for (std::vector<EegeoRenderables::InteriorHighlightRenderable*>::iterator renderableIterator = renderables.begin();
                                     renderableIterator != renderables.end();
                                     ++renderableIterator)
                                {
                                    AddHighlight(**renderableIterator);
                                }
                            }
                        }
                        
                        RemoveHighlights();
                        bool hasResults = m_searchResults.size() > 0;
                        ActivateLabels(!hasResults);
                    }
                    else
                    {
                        RemoveHighlights();
                        m_currentHighlightRenderables.clear();
                    }
                }
                
                void InteriorEntityHighlightController::OnInteriorAddedToSceneGraph(const Eegeo::Resources::Interiors::InteriorsCellResource& resource)
                {
                    if (m_interiorInteractionModel.HasInteriorModel())
                    {
                        const Eegeo::Resources::Interiors::InteriorsModel& model = *m_interiorInteractionModel.GetInteriorModel();
                        if (model.GetId() == resource.GetInteriorId())
                        {
                            OnInteriorChanged();
                            ApplyHighlightsForCurrentResults();
                        }
                    }
                }
                
                void InteriorEntityHighlightController::AddHighlight(Eegeo::Rendering::Renderables::InteriorHighlightRenderable& renderable)
                {
                    static const std::string highlightPrefix = "entity_highlight ";
                    const std::string& id = renderable.GetRenderableId();
                    
                    if (id.compare(0, highlightPrefix.length(), highlightPrefix) == 0)
                    {
                        std::string highlightId = id.substr(highlightPrefix.length());
                        if (m_currentHighlightRenderables.find(highlightId) == m_currentHighlightRenderables.end())
                        {
                            std::vector<Eegeo::Rendering::Renderables::InteriorHighlightRenderable*> highlights;
                            m_currentHighlightRenderables.insert(std::make_pair(highlightId, highlights));
                        }
                        m_currentHighlightRenderables[highlightId].push_back(&renderable);
                    }
                }
                
                void InteriorEntityHighlightController::OnSearchQueryResponseReceived(const Search::SearchQueryResponseReceivedMessage& message)
                {
                    auto results = message.GetResults();
                    RemoveHighlights();
                    if (m_searchResultsIndex >= 0)
                    {
                        const Search::SdkModel::SearchResultModel& selectedSearchResult = m_searchResults.at(m_searchResultsIndex);
                        
                        const std::vector<Search::SdkModel::SearchResultModel>& newSearchResults = results;
                        
                        std::vector<Search::SdkModel::SearchResultModel>::const_iterator iter = std::find(newSearchResults.begin(), newSearchResults.end(), selectedSearchResult);
                        if (iter == newSearchResults.end())
                        {
                            m_searchResultsIndex = -1;
                        }
                        else
                        {
                            m_searchResultsIndex = static_cast<int>(std::distance(newSearchResults.begin(), iter));
                        }
                    }
                    
                    m_searchResults = results;
                    ApplyHighlightsForCurrentResults();
                    
                    bool hasResults = results.size() > 0;
                    ActivateLabels(!hasResults);
                }
                
                std::vector<Search::SdkModel::SearchResultModel> InteriorEntityHighlightController::GetCurrentSearchResults()
                {
                    std::vector<Search::SdkModel::SearchResultModel> results;
                    results.reserve(m_searchResults.size());
                    
                    for (int i = 0; i < m_searchResults.size(); i++)
                    {
                        Search::SdkModel::SearchResultModel pResult = m_searchResults.at(i);
                        results.push_back(pResult);
                    }
                    return results;
                }
                
                void InteriorEntityHighlightController::ApplyHighlightsForCurrentResults()
                {
                    std::vector<Search::SdkModel::SearchResultModel> results = GetCurrentSearchResults();
                    ApplyHighlights(results);
                }
                
                void InteriorEntityHighlightController::HighlightSearchResult(const Search::SdkModel::SearchResultModel &searchResult)
                {
                    if (!searchResult.IsInterior())
                    {
                        return;
                    }
                    rapidjson::Document json;
                    std::string highlightedRoomId = "";
                    
                    std::vector<std::string> filteredEntityIds = GetEntityIdsFromSearchResultModel(searchResult);
                    std::vector<Eegeo::v4> highlightColors = m_highlightColorMapper.GetColors(searchResult);
                    
                    if (m_interiorInteractionModel.HasInteriorModel())
                    {
                        const std::string& interiorId = m_interiorInteractionModel.GetInteriorModel()->GetId().Value();
                        m_interiorsHighlightService.SetHighlights(interiorId, filteredEntityIds, highlightColors.front());
                     }
                }
                
                void InteriorEntityHighlightController::ApplyHighlights(const std::vector<Search::SdkModel::SearchResultModel> &results)
                {
                    RemoveHighlights();
                    
                    if (m_interiorInteractionModel.HasInteriorModel() && m_currentHighlightRenderables.size() == 0)
                    {
                        OnInteriorChanged();
                    }
                    
                    rapidjson::Document json;
                    std::string highlightedRoomId = "";
                    
                    if (m_searchResultsIndex >= 0)
                    {
                        const Search::SdkModel::SearchResultModel& resultsItt = m_searchResults.at(m_searchResultsIndex);
                        HighlightSearchResult(resultsItt);
                    }
                    else
                    {
                        for (std::vector<Search::SdkModel::SearchResultModel>::const_iterator resultsItt = results.begin(); resultsItt != results.end(); ++resultsItt)
                        {
                            HighlightSearchResult(*resultsItt);
                        }
                    }
                }
                
                bool InteriorEntityHighlightController::HideLabelAlwaysPredicate(const Eegeo::Labels::IAnchoredLabel& anchoredLabel) const
                {
                    return true;
                }
                
                bool InteriorEntityHighlightController::HideLabelByNamePredicate(const Eegeo::Labels::IAnchoredLabel& anchoredLabel) const
                {
                    const std::string& labelCategoryName = anchoredLabel.GetLabelAnchorCategory().GetId();
                    bool shouldHide =  labelCategoryName != "interior_facility_escalator"
                    && labelCategoryName != "interior_facility_stairs"
                    && labelCategoryName != "interior_facility_elevator"
                    && labelCategoryName != "interior_facility_toilets";
                    return shouldHide;
                }
            }
        }
    }
}
