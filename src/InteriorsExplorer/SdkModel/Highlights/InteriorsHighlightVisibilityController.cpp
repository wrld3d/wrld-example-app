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

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                InteriorsHighlightVisibilityController::InteriorsHighlightVisibilityController(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                                               Search::SdkModel::ISearchService& searchService,
                                                                                               Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                                                               Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                                                                               Eegeo::Resources::Interiors::Entities::IInteriorsLabelController& labelController,
                                                                                               ExampleAppMessaging::TMessageBus& messageBus,
                                                                                               IHighlightColorMapper& highlightColorMapper)
                : m_interiorInteractionModel(interiorInteractionModel)
                , m_interiorslabelsController(labelController)
                , m_searchService(searchService)
                , m_searchQueryPerformer(searchQueryPerformer)
                , m_searchResultRepository(searchResultRepository)
//                , m_messageBus(messageBus)
                , m_searchResultsHandler(this, &InteriorsHighlightVisibilityController::OnSearchResultsLoaded)
                , m_searchResultsClearedHandler(this, &InteriorsHighlightVisibilityController::OnSearchResultCleared)
                , m_interiorInteractionModelChangedHandler(this, &InteriorsHighlightVisibilityController::OnInteriorInteractionModelChanged)
                , m_availabilityChangedHandlerBinding(this, &InteriorsHighlightVisibilityController::OnAvailabilityChanged)
                , m_interiorLabelsBuiltHandler(this, &InteriorsHighlightVisibilityController::OnInteriorLabelsBuilt)
                , m_highlightColorMapper(highlightColorMapper)
                {
                    m_searchService.InsertOnReceivedQueryResultsCallback(m_searchResultsHandler);
                    m_searchQueryPerformer.InsertOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_interiorInteractionModel.RegisterModelChangedCallback(m_interiorInteractionModelChangedHandler);
                    m_interiorslabelsController.RegisterLabelsBuiltCallback(m_interiorLabelsBuiltHandler);
                }
                
                InteriorsHighlightVisibilityController::~InteriorsHighlightVisibilityController()
                {
                    
                    m_interiorslabelsController.UnregisterLabelsBuiltCallback(m_interiorLabelsBuiltHandler);
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
                    
                    for (std::map<std::string, Eegeo::Rendering::Renderables::InteriorHighlightRenderable*>::iterator it = m_currentHighlightRenderables.begin();
                         it != m_currentHighlightRenderables.end();
                         ++it)
                    {
                        it->second->SetDiffuseColor(transparent);
                    }
                    
                    DeactivateLabels();
                }
                
                void InteriorsHighlightVisibilityController::DeactivateLabels()
                {
                    namespace IE = Eegeo::Resources::Interiors::Entities;

                    const IE::TFloorIndexToModelsMap& floorIndexToModels = m_interiorslabelsController.GetFloorIndexToModels();
                    
                    for (IE::TFloorIndexToModelsMap::const_iterator it = floorIndexToModels.begin(); it != floorIndexToModels.end(); ++it)
                    {
                        const IE::TModelVector& modelVector = (*it).second;
                        
                        for (IE::TModelVector::const_iterator modelIt = modelVector.begin(); modelIt != modelVector.end(); ++modelIt)
                        {
                            modelIt->second->SetEnabled(false);
                        }
                    }
                }
                
                void InteriorsHighlightVisibilityController::OnInteriorLabelsBuilt()
                {
                    ShowLabelsForCurrentResults();
                }
                
                void InteriorsHighlightVisibilityController::OnSearchResultCleared()
                {
                    DeactivateHighlightRenderables();
                }
                
                void InteriorsHighlightVisibilityController::OnInteriorInteractionModelChanged()
                {
                    namespace EegeoInteriors = Eegeo::Resources::Interiors;
                    namespace EegeoRenderables = Eegeo::Rendering::Renderables;
                    
                    if (m_interiorInteractionModel.HasInteriorModel())
                    {
                        const EegeoInteriors::InteriorsModel& model = *m_interiorInteractionModel.GetInteriorModel();
                        
                        for(EegeoInteriors::TFloorModelVector::const_iterator floors = model.GetFloors().begin();
                            floors != model.GetFloors().end();
                            ++floors)
                        {
                            EegeoInteriors::InteriorsFloorCells* floorCells = model.GetFloorCells((*floors)->GetFloorNumber());
                            
                            for (int cellIndex = 0; cellIndex < floorCells->GetCellCount(); ++cellIndex)
                            {
                                EegeoInteriors::InteriorsFloorCell* cell = floorCells->GetFloorCells()[cellIndex];
                                std::vector<EegeoRenderables::InteriorHighlightRenderable*> renderables = cell->GetHighlightRenderables();
                                
                                for (std::vector<EegeoRenderables::InteriorHighlightRenderable*>::iterator renderableIterator = renderables.begin();
                                     renderableIterator != renderables.end();
                                     ++renderableIterator)
                                {
                                    AddHighlight(**renderableIterator);
                                }
                            }
                        }
                        
                        if(m_currentHighlightRenderables.size() > 0)
                        {
                            ShowLabelsForCurrentResults();
                        }
                    }
                    else
                    {
                        DeactivateHighlightRenderables();
                        m_currentHighlightRenderables.clear();
                    }
                }
                
                void InteriorsHighlightVisibilityController::AddHighlight(Eegeo::Rendering::Renderables::InteriorHighlightRenderable& renderable)
                {
                    static const std::string highlightPrefix = "entity_highlight ";
                    const std::string& id = renderable.GetRenderableId();
                    
                    if (id.compare(0, highlightPrefix.length(), highlightPrefix) == 0)
                    {
                        std::string roomName = id.substr(highlightPrefix.length());
                        m_currentHighlightRenderables.insert(std::make_pair(roomName, &renderable));
                    }
                }
                
                void InteriorsHighlightVisibilityController::OnSearchResultsLoaded(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results)
                {
                    DeactivateHighlightRenderables();
                    ShowLabelsForResults(results);
                }
                
                void InteriorsHighlightVisibilityController::ShowLabelsForCurrentResults()
                {
                    std::vector<Search::SdkModel::SearchResultModel> results;
                    results.reserve(m_searchResultRepository.GetItemCount());
                    
                    for(int i = 0; i < m_searchResultRepository.GetItemCount(); i++)
                    {
                        Search::SdkModel::SearchResultModel* pResult = m_searchResultRepository.GetItemAtIndex(i);
                        results.push_back(*pResult);
                    }
                    
                    ShowLabelsForResults(results);
                }
                
                void InteriorsHighlightVisibilityController::ShowLabelsForResults(const std::vector<Search::SdkModel::SearchResultModel> &results)
                {
                    if (m_interiorInteractionModel.HasInteriorModel() && m_currentHighlightRenderables.size() == 0)
                    {
                        OnInteriorInteractionModelChanged();
                    }
                    
                    rapidjson::Document json;
                    std::string highlightedRoomId = "";
                    
                    for(std::vector<Search::SdkModel::SearchResultModel>::const_iterator resultsItt = results.begin(); resultsItt != results.end(); ++resultsItt)
                    {
                        if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("highlight"))
                        {
                            highlightedRoomId = json["highlight"].GetString();

                            for (std::map<std::string, Eegeo::Rendering::Renderables::InteriorHighlightRenderable*>::iterator renderItt = m_currentHighlightRenderables.begin();
                                 renderItt != m_currentHighlightRenderables.end();
                                 ++renderItt)
                            {
                                if( renderItt->second->GetRenderableId().compare("entity_highlight " + highlightedRoomId) == 0)
                                {
                                    renderItt->second->SetDiffuseColor(m_highlightColorMapper.GetColor(*resultsItt, "highlight_color"));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}