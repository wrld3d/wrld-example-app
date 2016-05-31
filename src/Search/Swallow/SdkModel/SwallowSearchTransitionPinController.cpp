// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowSearchTransitionPinController.h"

#include "IWorldPinsService.h"
#include "SwallowSearchParser.h"
#include "SwallowSearchTransitionPinSelectionHandler.h"
#include "WorldPinVisibility.h"
#include "SearchQuery.h"
#include "SwallowSearchConstants.h"
#include "ISearchService.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                SwallowSearchTransitionPinController::SwallowSearchTransitionPinController(WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                                                           CameraTransitions::SdkModel::ICameraTransitionController& transitionController,
                                                                                           AppCamera::SdkModel::IAppCameraController& appCameraController,
                                                                                           Search::SdkModel::ISearchService& searchService)
                : m_worldPinsService(worldPinsService)
                , m_transitionController(transitionController)
                , m_appCameraController(appCameraController)
                , m_searchService(searchService)
                , m_handleSearchServiceReceivedQueryResults(this, &SwallowSearchTransitionPinController::OnSearchServiceReceivedQueryResults)
                {
                    m_searchService.InsertOnReceivedQueryResultsCallback(m_handleSearchServiceReceivedQueryResults);
                }
                
                SwallowSearchTransitionPinController::~SwallowSearchTransitionPinController()
                {
                    ClearResults();

                    m_searchService.RemoveOnReceivedQueryResultsCallback(m_handleSearchServiceReceivedQueryResults);
                }

                
                void SwallowSearchTransitionPinController::OnSearchServiceReceivedQueryResults(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results)
                {
                    if (query.IsCategory() && query.Query() == SearchConstants::TRANSITION_CATEGORY_NAME)
                    {
                        OnTransitionsLoaded(results);
                    }
                }
                
                void SwallowSearchTransitionPinController::OnTransitionsLoaded(const std::vector<Search::SdkModel::SearchResultModel>& transitionResults)
                {
                    ClearResults();
                    
                    for(std::vector<Search::SdkModel::SearchResultModel>::const_iterator it = transitionResults.begin(); it != transitionResults.end(); ++it)
                    {
                        WorldPins::SdkModel::WorldPinFocusData worldPinFocusData("Exit", "", it->GetVendor());
                        WorldPins::SdkModel::WorldPinInteriorData worldPinInteriorData((*it).GetBuildingId(),
                                                                                       (*it).GetFloor());
                        
                        const float heightOffsetMetres = 0.0f;
                        const int iconIndex = m_searchResultIconCategoryMapper.GetIconIndexFromSearchResult(*it);
                        const bool isInteriorPin = true;
                        
                        SwallowTransitionResultModel transitionResultModel = SearchParser::TransformToSwallowTransitionResult(*it);
                        
                        WorldPins::SdkModel::WorldPinItemModel* pPinItemModel = m_worldPinsService.AddPin(Eegeo_NEW(SwallowSearchTransitionPinSelectionHandler)(
                                                                                                                                            transitionResultModel,
                                                                                                                                            m_transitionController,
                                                                                                                                            m_appCameraController),
                                                                                                          NULL,
                                                                                                          worldPinFocusData,
                                                                                                          isInteriorPin,
                                                                                                          worldPinInteriorData,
                                                                                                          (*it).GetLocation(),
                                                                                                          iconIndex,
                                                                                                          heightOffsetMetres,
                                                                                                          WorldPins::SdkModel::WorldPinVisibility::Search);
                        pPinItemModel->SetFocusable(false);
                        
                        m_transitionPins.push_back(pPinItemModel);
                    }
                }
                
                void SwallowSearchTransitionPinController::ClearResults()
                {
                    for(std::vector<WorldPins::SdkModel::WorldPinItemModel*>::const_iterator it = m_transitionPins.begin(); it != m_transitionPins.end(); ++it)
                    {
                        m_worldPinsService.RemovePin(*it);
                    }
                    
                    m_transitionPins.clear();
                }
            }
        }
    }
}