// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsEntityIdHighlightVisibilityController.h"
#include "ISearchService.h"
#include "ISearchQueryPerformer.h"
#include "ISearchResultRepository.h"
#include "InteriorController.h"
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
#include "SwallowDepartmentResultModel.h"
#include "InstancedInteriorFloorRenderable.h"
#include "InteriorsCellResource.h"
#include "SearchResultSectionItemSelectedMessage.h"
#include "document.h"

#include "InteriorsInstanceRepository.h"
#include "IInteriorsHighlightService.h"
#include "InteriorInteractionModel.h"

#include <algorithm>
#include <iterator>

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
                    std::vector<std::string> GetEntityIdsFromSearchResultModel(const Search::SdkModel::SearchResultModel& selectedSearchResult)
                    {
                        rapidjson::Document json;
                        std::string highlightedEntityId = "";
                        
                        if (!json.Parse<0>(selectedSearchResult.GetJsonData().c_str()).HasParseError() && json.HasMember("entity_highlight"))
                        {
                            std::vector<std::string> entities;
                            const rapidjson::Value& entity_highlight = json["entity_highlight"];
                            assert(entity_highlight.IsArray());
                            
                            for (int i  = 0; i < entity_highlight.Size(); i++)
                            {
                                entities.push_back(entity_highlight[i].GetString());
                            }
                            return entities;
                        }
                        else if (selectedSearchResult.GetPrimaryTag() == Search::Swallow::SearchConstants::DEPARTMENT_CATEGORY_NAME)
                        {
                            const Search::Swallow::SdkModel::SwallowDepartmentResultModel& department = Search::Swallow::SdkModel::SearchParser::TransformToSwallowDepartmentResult(selectedSearchResult);

                            return department.GetAllDesks();
                        }
                        else if (selectedSearchResult.GetPrimaryTag() == Search::Swallow::SearchConstants::PERSON_CATEGORY_NAME)
                        {
                            const Search::Swallow::SdkModel::SwallowPersonResultModel& person = Search::Swallow::SdkModel::SearchParser::TransformToSwallowPersonResult(selectedSearchResult);

                            return std::vector<std::string>(1, person.GetDeskCode());
                        }
                        else if (selectedSearchResult.GetPrimaryTag() == Search::Swallow::SearchConstants::DESK_CATEGORY_NAME)
                        {
                            return std::vector<std::string>(1, selectedSearchResult.GetTitle());
                        }
                        else if (selectedSearchResult.GetPrimaryTag() == Search::Swallow::SearchConstants::WORKING_GROUP_CATEGORY_NAME)
                        {
                            const Search::Swallow::SdkModel::SwallowWorkingGroupResultModel& workingGroup = Search::Swallow::SdkModel::SearchParser::TransformToSwallowWorkingGroupResult(selectedSearchResult);

                            return workingGroup.GetAllDesks();
                        }

                        return std::vector<std::string>();
                    }
                }

                InteriorsEntityIdHighlightVisibilityController::InteriorsEntityIdHighlightVisibilityController(
                    Eegeo::Resources::Interiors::Highlights::IInteriorsHighlightService& interiorsHighlightService,
                    Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                    Search::SdkModel::ISearchResultRepository& searchResultRepository,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    Eegeo::Resources::Interiors::InteriorsInstanceRepository& interiorsInstanceRepository,
                    IHighlightColorMapper& highlightColorMapper)
                : m_interiorsHighlightService(interiorsHighlightService)
                , m_searchQueryPerformer(searchQueryPerformer)
                , m_searchResultsHandler(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchResultsLoaded)
                , m_searchResultsClearedHandler(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchResultsCleared)
                , m_handleSearchResultSectionItemSelectedMessageBinding(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchItemSelected)
                , m_messageBus(messageBus)
                , m_interiorsInstanceRepository(interiorsInstanceRepository)
                , m_searchResultsIndex(-1)
                , m_highlightColorMapper(highlightColorMapper)
                {
                    m_searchQueryPerformer.InsertOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_messageBus.SubscribeNative(m_handleSearchResultSectionItemSelectedMessageBinding);
                    m_messageBus.SubscribeUi(m_searchResultsHandler);
                }
                
                InteriorsEntityIdHighlightVisibilityController::~InteriorsEntityIdHighlightVisibilityController()
                {
                    m_searchQueryPerformer.RemoveOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_messageBus.UnsubscribeNative(m_handleSearchResultSectionItemSelectedMessageBinding);
                    m_messageBus.UnsubscribeUi(m_searchResultsHandler);
                }
                
                void InteriorsEntityIdHighlightVisibilityController::OnSearchResultsCleared()
                {
                    m_searchResultsIndex = -1;
                    m_searchResults.clear();
                    ClearHighlights();
                }

                void InteriorsEntityIdHighlightVisibilityController::ClearHighlights()
                {
                    m_interiorsHighlightService.ClearAllHighlights();
                }

                void InteriorsEntityIdHighlightVisibilityController::OnSearchItemSelected(const SearchResultSection::SearchResultSectionItemSelectedMessage& message)
                {
                    if (message.ItemIndex() >= m_searchResults.size())
                    {
                        m_searchResultsIndex = -1;
                    }
                    else
                    {
                        m_searchResultsIndex = message.ItemIndex();
                    }
                    
                    RefreshHighlights();
                }

                void InteriorsEntityIdHighlightVisibilityController::OnSearchResultsLoaded(const Search::SearchQueryResponseReceivedMessage& message)
                {
                    if (m_searchResultsIndex >= 0)
                    {
                        const Search::SdkModel::SearchResultModel& selectedSearchResult = m_searchResults.at(m_searchResultsIndex);

                        const std::vector<Search::SdkModel::SearchResultModel>& newSearchResults = message.GetResults();

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

                    m_searchResults = message.GetResults();

                    RefreshHighlights();
                }
                
                void InteriorsEntityIdHighlightVisibilityController::RefreshHighlights()
                {
                    ClearHighlights();

                    if (m_searchResultsIndex >= 0)
                    {
                        const Search::SdkModel::SearchResultModel& selectedSearchResult = m_searchResults.at(m_searchResultsIndex);
                        if (selectedSearchResult.IsInterior())
                        {
                            std::vector<std::string> entityIds = GetEntityIdsFromSearchResultModel(selectedSearchResult);
                            Eegeo::v4 highlightColor = m_highlightColorMapper.GetColor(selectedSearchResult, "entity_highlight_color");
                            m_interiorsHighlightService.SetHighlights(selectedSearchResult.GetBuildingId().Value(), entityIds, highlightColor);
                        }
                    }
                }
            }
        }
    }
}
