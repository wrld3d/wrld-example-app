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

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                InteriorsEntityIdHighlightVisibilityController::InteriorsEntityIdHighlightVisibilityController(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                                                               Search::SdkModel::ISearchService& searchService,
                                                                                               Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                                                               Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                                                                               const Eegeo::Resources::Interiors::InteriorsInstanceRepository& instanceRepository,
                                                                                               const Eegeo::v4& defaultHighlightColor)
                : InteriorsEntityIdHighlightController(instanceRepository, defaultHighlightColor)
                , m_interiorController(interiorController)
                , m_searchService(searchService)
                , m_searchQueryPerformer(searchQueryPerformer)
                , m_searchResultRepository(searchResultRepository)
                , m_searchPerformedHandler(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchPerformed)
                , m_searchResultsHandler(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchResultsLoaded)
                , m_searchResultsClearedHandler(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchResultCleared)
                , m_interiorVisibilityChangedHandler(this, &InteriorsEntityIdHighlightVisibilityController::OnInteriorVisibilityChanged)
                {
                    m_searchService.InsertOnPerformedQueryCallback(m_searchPerformedHandler);
                    m_searchService.InsertOnReceivedQueryResultsCallback(m_searchResultsHandler);
                    m_searchQueryPerformer.InsertOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_interiorController.RegisterVisibilityChangedCallback(m_interiorVisibilityChangedHandler);
                }
                
                InteriorsEntityIdHighlightVisibilityController::~InteriorsEntityIdHighlightVisibilityController()
                {
                    m_searchService.RemoveOnPerformedQueryCallback(m_searchPerformedHandler);
                    m_searchService.RemoveOnReceivedQueryResultsCallback(m_searchResultsHandler);
                    m_searchQueryPerformer.RemoveOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_interiorController.UnregisterVisibilityChangedCallback(m_interiorVisibilityChangedHandler);
                }
                
                void InteriorsEntityIdHighlightVisibilityController::OnSearchPerformed(const Search::SdkModel::SearchQuery &query)
                {
                    if(!query.IsCategory() || query.Query() != Search::Swallow::SearchConstants::DEPARTMENT_CATEGORY_NAME)
                    {
                    }
                }

                void InteriorsEntityIdHighlightVisibilityController::OnSearchResultCleared()
                {

                }
                
                void InteriorsEntityIdHighlightVisibilityController::OnInteriorVisibilityChanged()
                {
                    namespace EegeoInteriors = Eegeo::Resources::Interiors;
                    namespace EegeoRenderables = Eegeo::Rendering::Renderables;
                }
                

                void InteriorsEntityIdHighlightVisibilityController::OnSearchResultsLoaded(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results)
                {
                    for(std::vector<Search::SdkModel::SearchResultModel>::const_iterator it = results.begin(); it != results.end(); ++it)
                    {
                        if((*it).GetCategory() == Search::Swallow::SearchConstants::DEPARTMENT_CATEGORY_NAME)
                        {
                            const Search::Swallow::SdkModel::SwallowDepartmentResultModel& department = Search::Swallow::SdkModel::SearchParser::TransformToSwallowDepartmentResult(*it);

                            Super::HighlightEntityIds(department.GetAllDesks());
                        }
                    }
                }
            }
        }
    }
}