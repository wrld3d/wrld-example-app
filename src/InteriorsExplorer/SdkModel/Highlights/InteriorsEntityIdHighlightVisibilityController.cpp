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
                    std::vector<Eegeo::Rendering::Renderables::InteriorRenderable*> TransformToInteriorRenderable(const std::vector<Eegeo::Rendering::Renderables::InstancedInteriorFloorRenderable*>& renderables)
                    {
                        std::vector<Eegeo::Rendering::Renderables::InteriorRenderable*> transformedRenderables;
                        
                        for (std::vector<Eegeo::Rendering::Renderables::InstancedInteriorFloorRenderable*>::const_iterator i = renderables.begin();
                             i != renderables.end();
                             ++i)
                        {
                            transformedRenderables.push_back(static_cast<Eegeo::Rendering::Renderables::InteriorRenderable*>(*i));
                        }
                        
                        return transformedRenderables;
                    }
                }
                
                InteriorsEntityIdHighlightVisibilityController::InteriorsEntityIdHighlightVisibilityController(Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                                                               Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                                                                               const Eegeo::Resources::Interiors::InteriorsInstanceRepository& instanceRepository,
                                                                                               ExampleAppMessaging::TMessageBus& messageBus,
                                                                                               const Eegeo::v4& defaultHighlightColor,
                                                                                               Eegeo::Resources::Interiors::InteriorsCellResourceObserver& cellResourceObserver)
                : InteriorsEntityIdHighlightController(instanceRepository, defaultHighlightColor)
                , m_searchQueryPerformer(searchQueryPerformer)
                , m_searchResultsHandler(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchResultsLoaded)
                , m_searchResultsClearedHandler(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchResultCleared)
                , m_handleSearchResultSectionItemSelectedMessageBinding(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchItemSelected)
                , m_messageBus(messageBus)
                , m_cellResourceObserver(cellResourceObserver)
                , m_cellResourceDeletedCallback(this, &InteriorsEntityIdHighlightVisibilityController::HandleFloorCellDeleted)
                {
                    m_searchQueryPerformer.InsertOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_messageBus.SubscribeNative(m_handleSearchResultSectionItemSelectedMessageBinding);
                    m_messageBus.SubscribeUi(m_searchResultsHandler);
                    
                    m_cellResourceObserver.RegisterResourceDeletedCallback(m_cellResourceDeletedCallback);
                }
                
                InteriorsEntityIdHighlightVisibilityController::~InteriorsEntityIdHighlightVisibilityController()
                {
                    m_searchQueryPerformer.RemoveOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_messageBus.UnsubscribeNative(m_handleSearchResultSectionItemSelectedMessageBinding);
                    m_messageBus.UnsubscribeUi(m_searchResultsHandler);
                    
                    m_cellResourceObserver.UnregisterResourceDeletedCallback(m_cellResourceDeletedCallback);
                }
                
                void InteriorsEntityIdHighlightVisibilityController::OnSearchResultCleared()
                {
                    for (Eegeo::Resources::Interiors::CountPerRenderable::iterator i = m_lastHighlightedRenderables.begin();
                        i != m_lastHighlightedRenderables.end();
                        ++i)
                    {
                        Eegeo::Rendering::Renderables::InstancedInteriorFloorRenderable* currentRenderable = static_cast<Eegeo::Rendering::Renderables::InstancedInteriorFloorRenderable*>(i->first);
                        Eegeo::Rendering::Renderables::InstancedRenderState currentState = currentRenderable->GetInstancedRenderState();

                        currentState.IsHighlightingActive = false;

                        currentRenderable->SetInstancedRenderState(currentState);
                    }

                    m_lastHighlightedRenderables.clear();
                }

                void InteriorsEntityIdHighlightVisibilityController::OnSearchItemSelected(const SearchResultSection::SearchResultSectionItemSelectedMessage& message)
                {
                    OnSearchResultCleared();

                    int itemIndex = message.ItemIndex();

                    std::map<int, std::vector<std::string> >::iterator result = m_lastSearchedResults.find(itemIndex);
                    
                    if (result != m_lastSearchedResults.end())
                    {
                        Super::HighlightEntityIds(result->second, m_lastHighlightedRenderables);

                        std::map<int, std::string>::iterator id = m_lastSearchedResultsId.find(itemIndex);

                        m_lastIdSearched = id->second;
                    }
                }
                
                void InteriorsEntityIdHighlightVisibilityController::HandleFloorCellDeleted(const Eegeo::Resources::Interiors::InteriorsCellResource& interiorCellResource)
                {
                    std::vector<Eegeo::Resources::Interiors::InteriorsFloorCell*> floorCells = interiorCellResource.GetFloorCells();
                    
                    std::vector<Eegeo::Rendering::Renderables::InteriorRenderable*> renderablesToDelete;
                    
                    for (std::vector<Eegeo::Resources::Interiors::InteriorsFloorCell*>::const_iterator i = floorCells.begin();
                         i != floorCells.end();
                         ++i)
                    {
                        std::vector<Eegeo::Rendering::Renderables::InstancedInteriorFloorRenderable*> floorRenderables((*i)->GetInstancedRenderables());
                        
                        std::vector<Eegeo::Rendering::Renderables::InteriorRenderable*> transformedRenderables = TransformToInteriorRenderable(floorRenderables);
                        
                        renderablesToDelete.insert(renderablesToDelete.end(), transformedRenderables.begin(), transformedRenderables.end());
                    }
                    
                    for (std::vector<Eegeo::Rendering::Renderables::InteriorRenderable*>::iterator i = renderablesToDelete.begin();
                         i != renderablesToDelete.end();
                         ++i)
                    {
                        Eegeo::Resources::Interiors::CountPerRenderable::iterator result = m_lastHighlightedRenderables.find(*i);

                        if(result != m_lastHighlightedRenderables.end())
                        {
                            m_lastHighlightedRenderables.erase(result);
                        }
                    }

                }

                void InteriorsEntityIdHighlightVisibilityController::OnSearchResultsLoaded(const Search::SearchQueryResponseReceivedMessage& message)
                {
                    const std::vector<Search::SdkModel::SearchResultModel>& results = message.GetResults();
                    
                    m_lastSearchedResults.clear();
                    m_lastSearchedResultsId.clear();

                    bool lastIdFound = false;

                    int i = 0;
                    for(std::vector<Search::SdkModel::SearchResultModel>::const_iterator it = results.begin(); it != results.end(); ++it)
                    {
                        if((*it).GetCategory() == Search::Swallow::SearchConstants::DEPARTMENT_CATEGORY_NAME)
                        {
                            const Search::Swallow::SdkModel::SwallowDepartmentResultModel& department = Search::Swallow::SdkModel::SearchParser::TransformToSwallowDepartmentResult(*it);

                            const std::string& id = department.GetName();
                            m_lastSearchedResultsId.insert(std::make_pair(i, id));

                            if (id == m_lastIdSearched)
                            {
                                lastIdFound = true;
                            }

                            const std::vector<std::string>& currentDeskIds = department.GetAllDesks();
                            
                            m_lastSearchedResults.insert(std::make_pair(i, currentDeskIds));
                        }
                        else if ((*it).GetCategory() == Search::Swallow::SearchConstants::PERSON_CATEGORY_NAME)
                        {
                            const Search::Swallow::SdkModel::SwallowPersonResultModel& person = Search::Swallow::SdkModel::SearchParser::TransformToSwallowPersonResult(*it);

                            const std::string& id = person.GetDeskCode();
                            m_lastSearchedResultsId.insert(std::make_pair(i, id));

                            if (id == m_lastIdSearched)
                            {
                                lastIdFound = true;
                            }

                            std::vector<std::string> desks(1);
                            desks[0] = person.GetDeskCode();

                            m_lastSearchedResults.insert(std::make_pair(i, desks));
                        }
                        
                        if ((*it).GetCategory() != Search::Swallow::SearchConstants::TRANSITION_CATEGORY_NAME)
                        {
                            ++i;
                        }
                    }

                    if (!lastIdFound)
                    {
                        OnSearchResultCleared();
                    }
                }
            }
        }
    }
}
