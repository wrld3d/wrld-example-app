// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsHighlightVisibilityController.h"
#include "ISearchService.h"
#include "ISearchQueryPerformer.h"
#include "ISearchResultRepository.h"
#include "InteriorInteractionModel.h"
#include "InteriorsModel.h"
#include "InteriorsFloorModel.h"
#include "IInteriorsLabelController.h"
#include "SwallowSearchConstants.h"
#include "SwallowSearchParser.h"
#include "VectorMath.h"
#include "InteriorHighlightRenderable.h"
#include "InteriorsLabelParser.h"
#include "InteriorsFloorCells.h"
#include "InteriorsFloorCell.h"
#include "PlaceNameModel.h"
#include "InteriorsCellResource.h"
#include "InteriorsCellResourceObserver.h"

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
                    Eegeo::Resources::Interiors::Entities::IInteriorsLabelController& labelController,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    IHighlightColorMapper& highlightColorMapper,
                    PersistentSettings::IPersistentSettingsModel& persistentSettings)
                    : m_interiorInteractionModel(interiorInteractionModel)
                    , m_interiorsCellResourceObserver(interiorsCellResourceObserver)
                    , m_interiorslabelsController(labelController)
                    , m_searchService(searchService)
                    , m_searchQueryPerformer(searchQueryPerformer)
                    , m_searchResultRepository(searchResultRepository)
                    , m_searchResultsHandler(this, &InteriorsHighlightVisibilityController::OnSearchResultsLoaded)
                    , m_searchResultsClearedHandler(this, &InteriorsHighlightVisibilityController::OnSearchResultCleared)
                    , m_interiorInteractionModelChangedHandler(this, &InteriorsHighlightVisibilityController::OnInteriorChanged)
                    , m_interiorCellAddedHandler(this, &InteriorsHighlightVisibilityController::OnInteriorAddedToSceneGraph)
                    , m_availabilityChangedHandlerBinding(this, &InteriorsHighlightVisibilityController::OnAvailabilityChanged)
                    , m_interiorLabelsBuiltHandler(this, &InteriorsHighlightVisibilityController::OnInteriorLabelsBuilt)
                    , m_highlightColorMapper(highlightColorMapper)
                    , m_messageBus(messageBus)
                    , m_persistentSettings(persistentSettings)
                {
                    m_searchService.InsertOnReceivedQueryResultsCallback(m_searchResultsHandler);
                    m_searchQueryPerformer.InsertOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_interiorInteractionModel.RegisterModelChangedCallback(m_interiorInteractionModelChangedHandler);
                    m_interiorslabelsController.RegisterLabelsBuiltCallback(m_interiorLabelsBuiltHandler);
                    m_interiorsCellResourceObserver.RegisterAddedToSceneGraphCallback(m_interiorCellAddedHandler);

                    m_messageBus.SubscribeNative(m_availabilityChangedHandlerBinding);
                }

                InteriorsHighlightVisibilityController::~InteriorsHighlightVisibilityController()
                {
                    m_interiorsCellResourceObserver.UnregisterAddedToSceneGraphCallback(m_interiorCellAddedHandler);
                    m_interiorslabelsController.UnregisterLabelsBuiltCallback(m_interiorLabelsBuiltHandler);
                    m_searchService.RemoveOnReceivedQueryResultsCallback(m_searchResultsHandler);
                    m_searchQueryPerformer.RemoveOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_interiorInteractionModel.UnregisterModelChangedCallback(m_interiorInteractionModelChangedHandler);
                    
                    m_messageBus.UnsubscribeNative(m_availabilityChangedHandlerBinding);
                }

                void InteriorsHighlightVisibilityController::OnAvailabilityChanged(const ExampleApp::SearchResultOnMap::SearchResultMeetingAvailabilityChanged& message)
                {
                    int tempState = 1;
                    if(message.GetAvailability() == Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE)
                    {
                        tempState = 1;
                    }
                    else if (message.GetAvailability() == Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE_SOON)
                    {
                        tempState = 2;
                    }
                    else
                    {
                        tempState = 3;
                    }
                    
                    m_persistentSettings.SetValue(message.GetModel().GetIdentifier(), tempState);
                    Search::SdkModel::SearchResultModel model = message.GetModel();
                    
                    const Search::Swallow::SdkModel::SwallowMeetingRoomResultModel& meetingRoom = Search::Swallow::SdkModel::SearchParser::TransformToSwallowMeetingRoomResult(model);
                    
                    const std::string& roomName = meetingRoom.GetName();
                    std::map<std::string, std::vector<Eegeo::Rendering::Renderables::InteriorHighlightRenderable*>>::iterator it =
                    m_currentHighlightRenderables.find(roomName);
                    
                    if (it != m_currentHighlightRenderables.end())
                    {
                        for (auto& renderable : it->second)
                        {
                            ConfigureRenderableForAvailability(*renderable, message.GetAvailability());
                        }
                    }

                    m_highlightAvailabilityData[roomName] = message.GetAvailability();
                    
                    m_persistentSettings.SetValue(roomName, message.GetAvailability());
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
                            renderable->SetDiffuseColor(transparent);
                        }
                    }

                    DeactivateLabels();
                }

                void InteriorsHighlightVisibilityController::ActivateLabels(bool active)
                {
                    namespace IE = Eegeo::Resources::Interiors::Entities;

                    const IE::TFloorIndexToModelsMap& floorIndexToModels = m_interiorslabelsController.GetFloorIndexToModels();

                    for (IE::TFloorIndexToModelsMap::const_iterator it = floorIndexToModels.begin(); it != floorIndexToModels.end(); ++it)
                    {
                        const IE::TModelVector& modelVector = (*it).second;

                        for (IE::TModelVector::const_iterator modelIt = modelVector.begin(); modelIt != modelVector.end(); ++modelIt)
                        {
                            modelIt->second->SetEnabled(active);
                        }
                    }
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
                    if (!ShowHighlightsForCurrentResults())
                    {
                        ActivateLabels(true);
                    }
                }

                void InteriorsHighlightVisibilityController::OnSearchResultCleared()
                {
                    DeactivateHighlightRenderables();
                    m_highlightAvailabilityData.clear();
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
                            bool showingHighlights = ShowHighlightsForCurrentResults();
                            ActivateLabels(!showingHighlights);
                        }
                        else
                        {
                            ActivateLabels(true);
                        }
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

                        std::map<std::string, std::string>::iterator availabilityData = m_highlightAvailabilityData.find(highlightId);

                        if (availabilityData != m_highlightAvailabilityData.end())
                        {
                            ConfigureRenderableForAvailability(renderable, availabilityData->second);
                        }
                    }
                }

                void InteriorsHighlightVisibilityController::ConfigureRenderableForAvailability(Eegeo::Rendering::Renderables::InteriorHighlightRenderable& renderable, const std::string& availability)
                {
                    const Eegeo::v4 available(0.0f, 1.0f, 0.0f, 0.4f);
                    const Eegeo::v4 availableSoon(1.0f, 0.8f, 0.0f, 0.4f);
                    const Eegeo::v4 occupied(1.0f, 0.0f, 0.0f, 0.4f);
                    const Eegeo::v4 unknown(1.0f, 1.0f, 1.0f, 0.0f);

                    if (availability == Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE)
                    {
                        renderable.SetDiffuseColor(available);
                    }
                    else if (availability == Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE_SOON)
                    {
                        renderable.SetDiffuseColor(availableSoon);
                    }
                    else if (availability == Search::Swallow::SearchConstants::MEETING_ROOM_OCCUPIED)
                    {
                        renderable.SetDiffuseColor(occupied);
                    }
                    else
                    {
                        renderable.SetDiffuseColor(unknown);
                    }
                }

                void InteriorsHighlightVisibilityController::OnSearchResultsLoaded(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results)
                {
                    DeactivateHighlightRenderables();
                    m_highlightAvailabilityData.clear();
                    
                    if (ShowHighlightsForResults(results))
                    {
                        ActivateLabels(false);
                    }
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
                                    if (renderable->GetRenderableId().compare("entity_highlight " + highlightedRoomId) == 0)
                                    {
                                        renderable->SetDiffuseColor(m_highlightColorMapper.GetColor(*resultsItt, "highlight_color"));
                                        showingHighlights = true;
                                    }
                                }
                            }
                        }
                        else if ((*resultsItt).GetPrimaryTag() == Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME)
                        {
                            const Search::Swallow::SdkModel::SwallowMeetingRoomResultModel& meetingRoom = Search::Swallow::SdkModel::SearchParser::TransformToSwallowMeetingRoomResult(*resultsItt);

                            std::string roomName = meetingRoom.GetName();

                            std::string availability = meetingRoom.GetAvailability();
                            m_persistentSettings.TryGetValue(roomName, availability);

                            std::map<std::string, std::vector<Eegeo::Rendering::Renderables::InteriorHighlightRenderable*>>::iterator room = m_currentHighlightRenderables.find(roomName);

                            if (room != m_currentHighlightRenderables.end())
                            {
                                for (auto& renderable : room->second)
                                {
                                    ConfigureRenderableForAvailability(*renderable, availability);
                                    showingHighlights = true;
                                }
                            }

                            m_highlightAvailabilityData[roomName] = availability;
                        }
                    }

                    return showingHighlights;
                }
            }
        }
    }
}