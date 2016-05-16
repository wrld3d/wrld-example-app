// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsEntityIdHighlightVisibilityController.h"
#include "ISearchService.h"
#include "ISearchQueryPerformer.h"
#include "ISearchResultRepository.h"
#include "InteriorController.h"
#include "InteriorsModel.h"
#include "InteriorsFloorModel.h"
#include "IInteriorsLabelController.h"
#include "VectorMath.h"
#include "InteriorHighlightRenderable.h"
#include "InteriorsLabelParser.h"
#include "InteriorsFloorCells.h"
#include "InteriorsFloorCell.h"
#include "PlaceNameModel.h"
#include "InstancedInteriorFloorRenderable.h"
#include "InteriorsCellResource.h"
#include "SearchResultSectionItemSelectedMessage.h"
#include "InteriorsEntityIdHighlightController.h"

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
                    std::vector<std::string> GetDeskIdsFromSearchResultModel(const Search::SdkModel::SearchResultModel& selectedSearchResult)
                    {
                        return std::vector<std::string>();
                    }
                    
                    struct IsInteriorInstancePresentForId
                    {
                        typedef const std::string& argument_type;
                        
                        IsInteriorInstancePresentForId(const Eegeo::Resources::Interiors::InteriorsInstanceRepository& interiorsInstanceRepository)
                        : m_interiorsInstanceRepository(interiorsInstanceRepository)
                        {}
                        
                        bool operator()(argument_type id) const
                        {
                            return m_interiorsInstanceRepository.Contains(id);
                        }
                    private:
                        const Eegeo::Resources::Interiors::InteriorsInstanceRepository& m_interiorsInstanceRepository;
                    };
                }

                InteriorsEntityIdHighlightVisibilityController::InteriorsEntityIdHighlightVisibilityController(
                    Eegeo::Resources::Interiors::InteriorsEntityIdHighlightController& interiorsEntityIdHighlightController,
                    Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                    Search::SdkModel::ISearchResultRepository& searchResultRepository,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    Eegeo::Resources::Interiors::InteriorsInstanceRepository& interiorsInstanceRepository)
                : m_interiorsEntityIdHighlightController(interiorsEntityIdHighlightController)
                , m_searchQueryPerformer(searchQueryPerformer)
                , m_searchResultsHandler(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchResultsLoaded)
                , m_searchResultsClearedHandler(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchResultsCleared)
                , m_handleSearchResultSectionItemSelectedMessageBinding(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchItemSelected)
                , m_messageBus(messageBus)
                , m_interiorsInstanceRepository(interiorsInstanceRepository)
                , m_interiorsInstanceRepositoryChangedHandler(this, &InteriorsEntityIdHighlightVisibilityController::OnInteriorsInstanceRepositoryChanged)
                , m_searchResultsIndex(-1)
                {
                    m_searchQueryPerformer.InsertOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_messageBus.SubscribeNative(m_handleSearchResultSectionItemSelectedMessageBinding);
                    m_messageBus.SubscribeUi(m_searchResultsHandler);
                    
                    m_interiorsInstanceRepository.RegisterChangedCallback(m_interiorsInstanceRepositoryChangedHandler);
                }
                
                InteriorsEntityIdHighlightVisibilityController::~InteriorsEntityIdHighlightVisibilityController()
                {
                    m_searchQueryPerformer.RemoveOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_messageBus.UnsubscribeNative(m_handleSearchResultSectionItemSelectedMessageBinding);
                    m_messageBus.UnsubscribeUi(m_searchResultsHandler);
                    
                    m_interiorsInstanceRepository.UnregisterChangedCallback(m_interiorsInstanceRepositoryChangedHandler);
                }
                
                void InteriorsEntityIdHighlightVisibilityController::OnSearchResultsCleared()
                {
                    m_searchResultsIndex = -1;
                    m_searchResults.clear();
                    ClearHighlights();
                }

                void InteriorsEntityIdHighlightVisibilityController::ClearHighlights()
                {
                    for (InstancedRenderableVector::const_iterator iter = m_lastHighlightedRenderables.begin(); iter != m_lastHighlightedRenderables.end(); ++iter)
                    {
                        Eegeo::Rendering::Renderables::InstancedInteriorFloorRenderable& currentRenderable = **iter;
                        Eegeo::Rendering::Renderables::InstancedRenderState currentState = currentRenderable.GetInstancedRenderState();

                        currentState.IsHighlightingActive = false;

                        currentRenderable.SetInstancedRenderState(currentState);
                    }

                    m_lastHighlightedRenderables.clear();
                }

                void InteriorsEntityIdHighlightVisibilityController::OnSearchItemSelected(const SearchResultSection::SearchResultSectionItemSelectedMessage& message)
                {
                    if (message.ItemIndex() >= m_searchResults.size())
                        m_searchResultsIndex = -1;
                    else
                        m_searchResultsIndex = message.ItemIndex();
                    
                    RefreshHighlights();
                }
                
                void InteriorsEntityIdHighlightVisibilityController::OnInteriorsInstanceRepositoryChanged()
                {
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

                        const std::vector<std::string>& deskIds = GetDeskIdsFromSearchResultModel(selectedSearchResult);
                        
                        std::vector<std::string> filteredDeskIds;
                        
                        std::remove_copy_if(deskIds.begin(), deskIds.end(), std::back_inserter(filteredDeskIds), std::not1(IsInteriorInstancePresentForId(m_interiorsInstanceRepository)));

                        m_interiorsEntityIdHighlightController.HighlightEntityIds(filteredDeskIds, m_lastHighlightedRenderables);
                    }

                }
            }
        }
    }
}
