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

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                InteriorsEntityIdHighlightVisibilityController::InteriorsEntityIdHighlightVisibilityController(Search::SdkModel::ISearchService& searchService,
                                                                                               Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                                                               Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                                                                               const Eegeo::Resources::Interiors::InteriorsInstanceRepository& instanceRepository,
                                                                                               const Eegeo::v4& defaultHighlightColor)
                : InteriorsEntityIdHighlightController(instanceRepository, defaultHighlightColor)
                , m_searchService(searchService)
                , m_searchQueryPerformer(searchQueryPerformer)
                , m_searchResultRepository(searchResultRepository)
                , m_searchResultsHandler(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchResultsLoaded)
                , m_searchResultsClearedHandler(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchResultCleared)
                {
                    m_searchService.InsertOnReceivedQueryResultsCallback(m_searchResultsHandler);
                    m_searchQueryPerformer.InsertOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                }
                
                InteriorsEntityIdHighlightVisibilityController::~InteriorsEntityIdHighlightVisibilityController()
                {
                    m_searchService.RemoveOnReceivedQueryResultsCallback(m_searchResultsHandler);
                    m_searchQueryPerformer.RemoveOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                }
                
                void InteriorsEntityIdHighlightVisibilityController::OnSearchResultCleared()
                {
                    for (Eegeo::Resources::Interiors::CountPerRenderable::iterator i = m_lastSearchedRenderables.begin();
                        i != m_lastSearchedRenderables.end();
                        ++i)
                    {
                        Eegeo::Rendering::Renderables::InstancedInteriorFloorRenderable* currentRenderable = dynamic_cast<Eegeo::Rendering::Renderables::InstancedInteriorFloorRenderable*>(i->first);
                        Eegeo::Rendering::Renderables::InstancedRenderState currentState = currentRenderable->GetInstancedRenderState();

                        currentState.IsHighlightingActive = false;

                        currentRenderable->SetInstancedRenderState(currentState);
                    }

                    m_lastSearchedRenderables.clear();
                }

                void InteriorsEntityIdHighlightVisibilityController::OnSearchResultsLoaded(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results)
                {
                    std::vector<std::string> deskIds;

                    for(std::vector<Search::SdkModel::SearchResultModel>::const_iterator it = results.begin(); it != results.end(); ++it)
                    {
                        if((*it).GetCategory() == Search::Swallow::SearchConstants::DEPARTMENT_CATEGORY_NAME)
                        {
                            const Search::Swallow::SdkModel::SwallowDepartmentResultModel& department = Search::Swallow::SdkModel::SearchParser::TransformToSwallowDepartmentResult(*it);

                            //need to confirm behaviour for partial searches
                            /*if (department.GetName() != query.Query())
                            {
                                continue;
                            }*/

                            const std::vector<std::string>& currentDeskIds = department.GetAllDesks();

                            deskIds.insert(deskIds.end(), currentDeskIds.begin(), currentDeskIds.end());
                        }
                    }

                    if (!m_lastSearchedRenderables.empty())
                    {
                        OnSearchResultCleared();
                    }

                    if (!deskIds.empty())
                    {
                        Super::HighlightEntityIds(deskIds, m_lastSearchedRenderables);
                    }
                }
            }
        }
    }
}