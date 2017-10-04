// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsHighlightVisibilityController.h"
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

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                InteriorsHighlightVisibilityController::InteriorsHighlightVisibilityController(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                    Eegeo::Resources::Interiors::InteriorsCellResourceObserver& interiorsCellResourceObserver,
                    Search::SdkModel::ISearchService& searchService,
                    Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                    Search::SdkModel::ISearchResultRepository& searchResultRepository,
                    Eegeo::Resources::Interiors::Entities::IInteriorsLabelController& legacyLabelController,
                    Eegeo::Labels::ILabelAnchorFilterModel& labelHiddenFilterModel,
                    const Eegeo::Labels::LabelLayer::IdType interiorLabelLayer,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    IHighlightColorMapper& highlightColorMapper,
                    Eegeo::Resources::Interiors::Highlights::IInteriorsHighlightService& interiorsHighlightService)
                    : m_interiorInteractionModel(interiorInteractionModel)
                    , m_interiorsCellResourceObserver(interiorsCellResourceObserver)
                    , m_interiorLabelLayer(interiorLabelLayer)
                    , m_labelHiddenFilterModel(labelHiddenFilterModel)
                    , m_searchService(searchService)
                    , m_searchQueryPerformer(searchQueryPerformer)
                    , m_searchResultRepository(searchResultRepository)
                    , m_highlightColorMapper(highlightColorMapper)
                    , m_searchResultsHandler(this, &InteriorsHighlightVisibilityController::OnSearchResultsLoaded)
                    , m_searchResultsClearedHandler(this, &InteriorsHighlightVisibilityController::OnSearchResultCleared)
                    , m_interiorInteractionModelChangedHandler(this, &InteriorsHighlightVisibilityController::OnInteriorChanged)
                    , m_interiorCellAddedHandler(this, &InteriorsHighlightVisibilityController::OnInteriorAddedToSceneGraph)
                    , m_availabilityChangedHandlerBinding(this, &InteriorsHighlightVisibilityController::OnAvailabilityChanged)
                    , m_interiorLabelsBuiltHandler(this, &InteriorsHighlightVisibilityController::OnInteriorLabelsBuilt)
                    , m_interiorsHighlightService(interiorsHighlightService)
                    , m_hideLabelAlwaysFilter(this, &InteriorsHighlightVisibilityController::HideLabelAlwaysPredicate)
                    , m_hideLabelByNameFilter(this, &InteriorsHighlightVisibilityController::HideLabelByNamePredicate)
                {
                    m_searchService.InsertOnReceivedQueryResultsCallback(m_searchResultsHandler);
                    m_searchQueryPerformer.InsertOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_interiorInteractionModel.RegisterModelChangedCallback(m_interiorInteractionModelChangedHandler);
                    
                    
                    m_interiorsCellResourceObserver.RegisterAddedToSceneGraphCallback(m_interiorCellAddedHandler);

                    m_labelHiddenFilterModel.SetFilter(m_interiorLabelLayer, &m_hideLabelAlwaysFilter);
                }

                InteriorsHighlightVisibilityController::~InteriorsHighlightVisibilityController()
                {
                    m_interiorsCellResourceObserver.UnregisterAddedToSceneGraphCallback(m_interiorCellAddedHandler);

                    m_searchService.RemoveOnReceivedQueryResultsCallback(m_searchResultsHandler);
                    m_searchQueryPerformer.RemoveOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_interiorInteractionModel.UnregisterModelChangedCallback(m_interiorInteractionModelChangedHandler);
                }

                void InteriorsHighlightVisibilityController::OnAvailabilityChanged()
                {
                }

                void InteriorsHighlightVisibilityController::DeactivateHighlightRenderables()
                {
                    const Eegeo::v4 transparent(1.0f, 1.0f, 1.0f, 0.0f);

                    for (std::map<std::string, std::vector<Eegeo::Rendering::Renderables::InteriorHighlightRenderable*>>::iterator it = m_currentHighlightRenderables.begin();
                        it != m_currentHighlightRenderables.end();
                        ++it)
                    {
                        for (auto& renderable : it->second)
                        {
                            m_interiorsHighlightService.ClearHighlight(renderable->GetInteriorId(), renderable->GetHighlightId());
                        }
                    }
                }

                void InteriorsHighlightVisibilityController::ActivateLabels(bool active)
                {
                    m_labelHiddenFilterModel.SetFilter(m_interiorLabelLayer, active ? NULL : &m_hideLabelByNameFilter);
                }


                void InteriorsHighlightVisibilityController::OnInteriorLabelsBuilt()
                {
                    ShowHighlightsForCurrentResults();
                    
                    bool hasResults = m_searchResultRepository.GetItemCount() > 0;
                    ActivateLabels(!hasResults);
                    
                }

                void InteriorsHighlightVisibilityController::OnSearchResultCleared()
                {
                    DeactivateHighlightRenderables();
                    ActivateLabels(true);
                }

                void InteriorsHighlightVisibilityController::OnInteriorChanged()
                {
                    namespace EegeoInteriors = Eegeo::Resources::Interiors;
                    namespace EegeoRenderables = Eegeo::Rendering::Renderables;

                    DeactivateHighlightRenderables();
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

                        if (m_currentHighlightRenderables.size() > 0)
                        {
                            ShowHighlightsForCurrentResults();
                        }
                        bool hasResults = m_searchResultRepository.GetItemCount() > 0;
                        ActivateLabels(!hasResults);
                    }
                    else
                    {
                        DeactivateHighlightRenderables();
                        m_currentHighlightRenderables.clear();
                    }
                }

                void InteriorsHighlightVisibilityController::OnInteriorAddedToSceneGraph(const Eegeo::Resources::Interiors::InteriorsCellResource& resource)
                {
                    if (m_interiorInteractionModel.HasInteriorModel())
                    {
                        const Eegeo::Resources::Interiors::InteriorsModel& model = *m_interiorInteractionModel.GetInteriorModel();
                        if (model.GetId() == resource.GetInteriorId())
                        {
                            OnInteriorChanged();
                        }
                    }
                }

                void InteriorsHighlightVisibilityController::AddHighlight(Eegeo::Rendering::Renderables::InteriorHighlightRenderable& renderable)
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

                void InteriorsHighlightVisibilityController::OnSearchResultsLoaded(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results)
                {
                    DeactivateHighlightRenderables();
                    
                    ShowHighlightsForResults(results);
                    
                    bool hasResults = results.size() > 0;
                    ActivateLabels(!hasResults);
                }

                bool InteriorsHighlightVisibilityController::ShowHighlightsForCurrentResults()
                {
                    std::vector<Search::SdkModel::SearchResultModel> results;
                    results.reserve(m_searchResultRepository.GetItemCount());

                    for (int i = 0; i < m_searchResultRepository.GetItemCount(); i++)
                    {
                        Search::SdkModel::SearchResultModel* pResult = m_searchResultRepository.GetItemAtIndex(i);
                        results.push_back(*pResult);
                    }

                    return ShowHighlightsForResults(results);
                }

                bool InteriorsHighlightVisibilityController::ShowHighlightsForResults(const std::vector<Search::SdkModel::SearchResultModel> &results)
                {
                    bool showingHighlights = false;

                    if (m_interiorInteractionModel.HasInteriorModel() && m_currentHighlightRenderables.size() == 0)
                    {
                        OnInteriorChanged();
                    }

                    rapidjson::Document json;
                    std::string highlightedRoomId = "";

                    for (std::vector<Search::SdkModel::SearchResultModel>::const_iterator resultsItt = results.begin(); resultsItt != results.end(); ++resultsItt)
                    {
                        if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("highlight"))
                        {
                            highlightedRoomId = json["highlight"].GetString();

                            for (std::map<std::string, std::vector<Eegeo::Rendering::Renderables::InteriorHighlightRenderable*>>::iterator renderItt = m_currentHighlightRenderables.begin();
                                renderItt != m_currentHighlightRenderables.end();
                                ++renderItt)
                            {
                                for (auto& renderable : renderItt->second)
                                {
									if (renderable->GetInteriorId().compare(resultsItt->GetBuildingId().Value()) == 0)
									{
										if (renderable->GetRenderableId().compare("entity_highlight " + highlightedRoomId) == 0)
										{
											m_interiorsHighlightService.SetHighlight(renderable->GetInteriorId(), highlightedRoomId, m_highlightColorMapper.GetColor(*resultsItt, "highlight_color"));
											showingHighlights = true;
										}
									}
                                }
                            }
                        }
                    }

                    return showingHighlights;
                }
                
                bool InteriorsHighlightVisibilityController::HideLabelAlwaysPredicate(const Eegeo::Labels::IAnchoredLabel& anchoredLabel) const
                {
                    return true;
                }
                
                bool InteriorsHighlightVisibilityController::HideLabelByNamePredicate(const Eegeo::Labels::IAnchoredLabel& anchoredLabel) const
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
