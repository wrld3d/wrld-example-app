// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "LaxSearchServiceModule.h"

#include "LaxOfficeResultMenuOptionSelectedMessageHandler.h"
#include "LaxSearchConstants.h"
#include "LaxSearchService.h"
#include "LaxSearchTransitionPinController.h"
#include "ISearchQueryPerformer.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            namespace SdkModel
            {
                LaxSearchServiceModule::LaxSearchServiceModule(Search::SdkModel::ISearchService& searchService,
                                                                       Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                                       CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                       AppCamera::SdkModel::IAppCameraController& appCameraController,
                                                                       ExampleAppMessaging::TMessageBus& messageBus,
                                                                       WorldPins::SdkModel::IWorldPinsService& worldPinsService)
                : m_searchService(searchService)
                , m_searchQueryPerformer(searchQueryPerformer)
                , m_pLaxOfficeResultMenuOptionSelectedMessageHandler(NULL)
                , m_pLaxSearchTransitionPinController(NULL)
                , m_transitionCallback(this, &LaxSearchServiceModule::OnTransitionResult)
                {
                    
                    m_searchService.InsertOnReceivedQueryResultsCallback(m_transitionCallback);
                    
                    m_pLaxOfficeResultMenuOptionSelectedMessageHandler = Eegeo_NEW(LaxOfficeResultMenuOptionSelectedMessageHandler)(cameraTransitionController, messageBus);
                    
                    m_pLaxSearchTransitionPinController = Eegeo_NEW(LaxSearchTransitionPinController)(worldPinsService, cameraTransitionController, appCameraController);
                    
                    ExampleApp::Search::SdkModel::SearchQuery query(SearchConstants::TRANSITION_CATEGORY_NAME, true, false, Eegeo::Space::LatLongAltitude::FromDegrees(51.520199, -0.086243, 0.0), 1000.0);
                    m_searchService.PerformLocationQuerySearch(query);

                }
                    
                LaxSearchServiceModule::~LaxSearchServiceModule()
                {
                    Eegeo_DELETE m_pLaxSearchTransitionPinController;
                    
                    Eegeo_DELETE m_pLaxOfficeResultMenuOptionSelectedMessageHandler;
                }
                    
                std::vector<CategorySearch::View::CategorySearchModel> LaxSearchServiceModule::GetCategorySearchModels() const
                {
                    return GetCategorySearchModels();
                }
                
                LaxSearchTransitionPinController& LaxSearchServiceModule::GetLaxSearchTransitionPinController() const
                {
                    return *m_pLaxSearchTransitionPinController;
                }
                
                void LaxSearchServiceModule::OnTransitionResult(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results)
                {
                    if (query.IsCategory() && query.Query() == SearchConstants::TRANSITION_CATEGORY_NAME)
                    {
                       // (*m_pLaxSearchTransitionPinController)(results);
                        m_searchQueryPerformer.RemoveSearchQueryResults();
                    }
                }
            }
        }
    }
}