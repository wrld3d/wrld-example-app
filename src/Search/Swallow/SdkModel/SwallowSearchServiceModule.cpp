// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowSearchServiceModule.h"

#include "SwallowOfficeResultMenuOptionSelectedMessageHandler.h"
#include "SwallowSearchConstants.h"
#include "SwallowSearchService.h"
#include "SwallowSearchTransitionPinController.h"
#include "ISearchQueryPerformer.h"
#include "INetworkCapabilities.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                SwallowSearchServiceModule::SwallowSearchServiceModule(Search::SdkModel::ISearchService& searchService,
                                                                       Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                                       CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                       AppCamera::SdkModel::IAppCameraController& appCameraController,
                                                                       ExampleAppMessaging::TMessageBus& messageBus,
                                                                       WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                                       Net::SdkModel::INetworkCapabilities& networkCapabilities)
                : m_searchService(searchService)
                , m_searchQueryPerformer(searchQueryPerformer)
                , m_networkCapabilities(networkCapabilities)
                , m_pSwallowOfficeResultMenuOptionSelectedMessageHandler(NULL)
                , m_pSwallowSearchTransitionPinController(NULL)
                , m_handleNetworkCapabilitiesChanged(this, &SwallowSearchServiceModule::OnNetworkCapabilitiesChanged)
                , m_handleSearchServiceReceivedQueryResults(this, &SwallowSearchServiceModule::OnSearchServiceReceivedQueryResults)
                , m_clearSearchNextUpdate(false)
                , m_hasTransitionPoiResults(false)
                , m_hasPerformedFirstSearch(false)
                {
                    m_searchService.InsertOnReceivedQueryResultsCallback(m_handleSearchServiceReceivedQueryResults);

                    m_networkCapabilities.RegisterChangedCallback(m_handleNetworkCapabilitiesChanged);
                    
                    m_pSwallowOfficeResultMenuOptionSelectedMessageHandler = Eegeo_NEW(SwallowOfficeResultMenuOptionSelectedMessageHandler)(cameraTransitionController, messageBus);
                    
                    m_pSwallowSearchTransitionPinController = Eegeo_NEW(SwallowSearchTransitionPinController)(worldPinsService, cameraTransitionController, appCameraController, m_searchService);
                }
                    
                SwallowSearchServiceModule::~SwallowSearchServiceModule()
                {
                    m_searchService.RemoveOnReceivedQueryResultsCallback(m_handleSearchServiceReceivedQueryResults);

                    m_networkCapabilities.UnregisterChangedCallback(m_handleNetworkCapabilitiesChanged);

                    Eegeo_DELETE m_pSwallowSearchTransitionPinController;
                    
                    Eegeo_DELETE m_pSwallowOfficeResultMenuOptionSelectedMessageHandler;
                }

                void SwallowSearchServiceModule::PerformTransitionPoiSearch()
                {
                    ExampleApp::Search::SdkModel::SearchQuery query(SearchConstants::TRANSITION_CATEGORY_NAME, true, false, Eegeo::Space::LatLongAltitude::FromDegrees(51.520199, -0.086243, 0.0), 1000.0);
                    m_searchService.PerformLocationQuerySearch(query);
                }
                    
                std::vector<CategorySearch::View::CategorySearchModel> SwallowSearchServiceModule::GetCategorySearchModels() const
                {
                    return SearchConstants::GetCategorySearchModels();
                }
                
                SwallowSearchTransitionPinController& SwallowSearchServiceModule::GetSwallowSearchTransitionPinController() const
                {
                    return *m_pSwallowSearchTransitionPinController;
                }

                void SwallowSearchServiceModule::OnNetworkCapabilitiesChanged()
                {
                    if (!m_hasTransitionPoiResults && m_networkCapabilities.NetworkAvailable())
                    {
                        PerformTransitionPoiSearch();
                    }
                }
                
                void SwallowSearchServiceModule::OnSearchServiceReceivedQueryResults(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results)
                {
                    if (query.IsCategory() && query.Query() == SearchConstants::TRANSITION_CATEGORY_NAME)
                    {
                        // Due to multiple callbacks of "ReceivedQueryResultsCallback" happening in undetermined order, clear results
                        // after they've all been resolved by handlers. Needs better model/schedule support. 
                        m_clearSearchNextUpdate = true;

                        m_hasTransitionPoiResults = !results.empty();
                    }
                }

                void SwallowSearchServiceModule::Start()
                {
                    if (!m_hasPerformedFirstSearch)
                    {
                        m_hasPerformedFirstSearch = true;
                        PerformTransitionPoiSearch();
                    }
                }

                void SwallowSearchServiceModule::Update()
                {

                    if (m_clearSearchNextUpdate)
                    {
                        m_searchQueryPerformer.RemoveSearchQueryResults();
                        m_clearSearchNextUpdate = false;
                    }
                }
            }
        }
    }
}