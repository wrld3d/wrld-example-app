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
#include "LabelAnchorFilterModel.h"
#include "IAnchoredLabel.h"
#include "document.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                namespace
                {
                    const std::string highlightPrefix = "entity_highlight ";
                    const Eegeo::v4 transparentHighlightColor(1.0f, 1.0f, 1.0f, 0.0f);
                }
                
                InteriorsHighlightVisibilityController::AvailabilityToColor InteriorsHighlightVisibilityController::BuildAvailabilityToColor()
                {
                    const AvailabilityToColor availabilityToColor =
                    {
                        { std::string(), transparentHighlightColor },
                        { Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE, Eegeo::v4(0.0f, 1.0f, 0.0f, 0.4f) },
                        { Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE_SOON, Eegeo::v4(1.0f, 0.8f, 0.0f, 0.4f) },
                        { Search::Swallow::SearchConstants::MEETING_ROOM_OCCUPIED, Eegeo::v4(1.0f, 0.0f, 0.0f, 0.4f) }
                    };
                    return availabilityToColor;
                }
                
                InteriorsHighlightVisibilityController::InteriorsHighlightVisibilityController(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                    Eegeo::Resources::Interiors::InteriorsCellResourceObserver& interiorsCellResourceObserver,
                    Search::SdkModel::ISearchService& searchService,
                    Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                    Search::SdkModel::ISearchResultRepository& searchResultRepository,
                    Eegeo::Labels::ILabelAnchorFilterModel& labelHiddenFilterModel,
                    const Eegeo::Labels::LabelLayer::IdType interiorLabelLayer,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    IHighlightColorMapper& highlightColorMapper,
                    PersistentSettings::IPersistentSettingsModel& persistentSettings)
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
                    , m_messageBus(messageBus)
                    , m_persistentSettings(persistentSettings)
                    , m_availabilityToColor(BuildAvailabilityToColor())
                    , m_hideLabelAlwaysFilter(this, &InteriorsHighlightVisibilityController::HideLabelAlwaysPredicate)
                {
                    m_searchService.InsertOnReceivedQueryResultsCallback(m_searchResultsHandler);
                    m_searchQueryPerformer.InsertOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_interiorInteractionModel.RegisterModelChangedCallback(m_interiorInteractionModelChangedHandler);
                    m_interiorsCellResourceObserver.RegisterAddedToSceneGraphCallback(m_interiorCellAddedHandler);

                    m_messageBus.SubscribeNative(m_availabilityChangedHandlerBinding);

                    m_labelHiddenFilterModel.SetFilter(m_interiorLabelLayer, &m_hideLabelAlwaysFilter);
                }

                InteriorsHighlightVisibilityController::~InteriorsHighlightVisibilityController()
                {
                    m_interiorsCellResourceObserver.UnregisterAddedToSceneGraphCallback(m_interiorCellAddedHandler);
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
                    m_persistentSettings.SetValue(roomName, message.GetAvailability());
                    
                    const Eegeo::v4& highlightColor = GetColorForAvailability(message.GetAvailability());

                    const std::string highlightRenderableId(highlightPrefix + roomName);
                    
                    if (m_searchResultHighlightIdToColor.find(highlightRenderableId) != m_searchResultHighlightIdToColor.end())
                    {
                        m_searchResultHighlightIdToColor.at(highlightRenderableId) = highlightColor;
                    }
                    
                    RefreshHighlightsColor();
                }
                
                void InteriorsHighlightVisibilityController::OnSearchResultsLoaded(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results)
                {
                    RefreshForSearchResults(results);
                }

                void InteriorsHighlightVisibilityController::OnSearchResultCleared()
                {
                    std::vector<Search::SdkModel::SearchResultModel> results;
                    GetCurrentSearchResults(results);
                    RefreshForSearchResults(results);
                }

                void InteriorsHighlightVisibilityController::OnInteriorChanged()
                {
                    PopulateHighlightRenderables();
                }
                
                void InteriorsHighlightVisibilityController::OnInteriorAddedToSceneGraph(const Eegeo::Resources::Interiors::InteriorsCellResource& resource)
                {
                    if (m_interiorInteractionModel.HasInteriorModel())
                    {
                        const Eegeo::Resources::Interiors::InteriorsModel& model = *m_interiorInteractionModel.GetInteriorModel();
                        if (model.GetId() == resource.GetInteriorId())
                        {
                            PopulateHighlightRenderables();
                        }
                    }
                }
                
                void InteriorsHighlightVisibilityController::PopulateHighlightRenderables()
                {
                    namespace EegeoInteriors = Eegeo::Resources::Interiors;
                    namespace EegeoRenderables = Eegeo::Rendering::Renderables;

                    ClearHighlightRenderables();
                    
                    Eegeo_ASSERT(m_highlightRenderablesForInterior.empty());

                    if (!m_interiorInteractionModel.HasInteriorModel())
                    {
                        return;
                    }
                    
                    const std::vector<const EegeoInteriors::InteriorsFloorCell*>& floorCells = m_interiorInteractionModel.GetInteriorModel()->GetAllFloorCells();

                    for (auto const pInteriorsFloorCell : floorCells)
                    {
                        const HighlightRenderableVector& renderablesForFloorCell = pInteriorsFloorCell->GetHighlightRenderables();
                        
                        m_highlightRenderablesForInterior.insert(m_highlightRenderablesForInterior.end(), renderablesForFloorCell.begin(), renderablesForFloorCell.end());
                    }

                    RefreshHighlightsColor();
                }
                
                void InteriorsHighlightVisibilityController::ClearHighlightRenderables()
                {
                    const Eegeo::v4& transparent = GetColorForAvailability("");
                    
                    for (auto const pHighlightRenderable : m_highlightRenderablesForInterior)
                    {
                        pHighlightRenderable->SetDiffuseColor(transparent);
                    }
                    
                    m_highlightRenderablesForInterior.clear();
                }
                
                Eegeo::v4 InteriorsHighlightVisibilityController::GetColorForAvailability(const std::string& availability) const
                {
                    return m_availabilityToColor.at(availability);
                }
                
                void InteriorsHighlightVisibilityController::GetCurrentSearchResults(std::vector<Search::SdkModel::SearchResultModel>& out_results) const
                {
                    out_results.clear();
                    out_results.reserve(m_searchResultRepository.GetItemCount());
                    
                    for (int i = 0; i < m_searchResultRepository.GetItemCount(); i++)
                    {
                        Search::SdkModel::SearchResultModel* pResult = m_searchResultRepository.GetItemAtIndex(i);
                        out_results.push_back(*pResult);
                    }
                }
                
                void InteriorsHighlightVisibilityController::RefreshForSearchResults(const std::vector<Search::SdkModel::SearchResultModel> &results)
                {
                    m_searchResultHighlightIdToColor.clear();
 
                    rapidjson::Document json;

                    for (auto const& searchResult : results)
                    {
                        if (searchResult.GetPrimaryTag() == Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME)
                        {
                            const Search::Swallow::SdkModel::SwallowMeetingRoomResultModel& meetingRoom = Search::Swallow::SdkModel::SearchParser::TransformToSwallowMeetingRoomResult(searchResult);
                            
                            const std::string& roomName = meetingRoom.GetName();
                            
                            std::string availability = meetingRoom.GetAvailability();
                            m_persistentSettings.TryGetValue(roomName, availability);
                            
                            const std::string highlightRenderableId(highlightPrefix + roomName);
                            const Eegeo::v4& highlightColor = GetColorForAvailability(availability);
                            
                            m_searchResultHighlightIdToColor[highlightRenderableId] = highlightColor;
                        }
                        else if (!json.Parse<0>(searchResult.GetJsonData().c_str()).HasParseError() && json.HasMember("highlight"))
                        {
                            const std::string highlightedRoomId(json["highlight"].GetString());
                            const std::string highlightRenderableId(highlightPrefix + highlightedRoomId);
                            const Eegeo::v4& highlightColor = m_highlightColorMapper.GetColor(searchResult, "highlight_color");
                            
                            m_searchResultHighlightIdToColor[highlightRenderableId] = highlightColor;
                        }

                    }
                    
                    RefreshHighlightsColor();
                }
                
                void InteriorsHighlightVisibilityController::RefreshHighlightsColor()
                {
                    for (auto const pHighlightRenderable : m_highlightRenderablesForInterior)
                    {
                        const std::string& renderableId = pHighlightRenderable->GetRenderableId();
                        
                        HighlightIdToColor::const_iterator iter = m_searchResultHighlightIdToColor.find(renderableId);
                        const Eegeo::v4& highlightColor = (iter != m_searchResultHighlightIdToColor.end())
                        ? iter->second
                        : transparentHighlightColor;
                        
                        pHighlightRenderable->SetDiffuseColor(highlightColor);
                    }
                }
                
                bool InteriorsHighlightVisibilityController::HideLabelAlwaysPredicate(const Eegeo::Labels::IAnchoredLabel& anchoredLabel) const
                {
                    return true;
                }
            }
        }
    }
}
