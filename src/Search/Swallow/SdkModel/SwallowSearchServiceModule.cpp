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
                SwallowSearchServiceModule::SwallowSearchServiceModule(Search::SdkModel::ISearchService& transitionPoiSearchService,
                                                                       CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                       AppCamera::SdkModel::IAppCameraController& appCameraController,
                                                                       ExampleAppMessaging::TMessageBus& messageBus,
                                                                       WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                                       Net::SdkModel::INetworkCapabilities& networkCapabilities)
                : m_transitionPoiSearchService(transitionPoiSearchService)
                , m_networkCapabilities(networkCapabilities)
                , m_pSwallowOfficeResultMenuOptionSelectedMessageHandler(NULL)
                , m_pSwallowSearchTransitionPinController(NULL)
                , m_handleNetworkCapabilitiesChanged(this, &SwallowSearchServiceModule::OnNetworkCapabilitiesChanged)
                , m_handleSearchServiceReceivedQueryResults(this, &SwallowSearchServiceModule::OnSearchServiceReceivedQueryResults)
                , m_hasTransitionPoiResults(false)
                , m_hasPerformedFirstSearch(false)
                {
                    m_transitionPoiSearchService.InsertOnReceivedQueryResultsCallback(m_handleSearchServiceReceivedQueryResults);

                    m_networkCapabilities.RegisterChangedCallback(m_handleNetworkCapabilitiesChanged);
                    
                    m_pSwallowOfficeResultMenuOptionSelectedMessageHandler = Eegeo_NEW(SwallowOfficeResultMenuOptionSelectedMessageHandler)(cameraTransitionController, messageBus);
                    
                    m_pSwallowSearchTransitionPinController = Eegeo_NEW(SwallowSearchTransitionPinController)(worldPinsService, cameraTransitionController, appCameraController, m_transitionPoiSearchService);
                }
                    
                SwallowSearchServiceModule::~SwallowSearchServiceModule()
                {
                    m_transitionPoiSearchService.RemoveOnReceivedQueryResultsCallback(m_handleSearchServiceReceivedQueryResults);

                    m_networkCapabilities.UnregisterChangedCallback(m_handleNetworkCapabilitiesChanged);

                    Eegeo_DELETE m_pSwallowSearchTransitionPinController;
                    
                    Eegeo_DELETE m_pSwallowOfficeResultMenuOptionSelectedMessageHandler;
                }

                void SwallowSearchServiceModule::PerformTransitionPoiSearch()
                {
                    ExampleApp::Search::SdkModel::SearchQuery query(SearchConstants::TRANSITION_CATEGORY_NAME, true, false, Eegeo::Space::LatLongAltitude::FromDegrees(51.520199, -0.086243, 0.0), 1000.0);
                    m_transitionPoiSearchService.PerformLocationQuerySearch(query);
                }
                    
                std::vector<TagSearch::View::TagSearchModel> SwallowSearchServiceModule::GetTagSearchModels() const
                {
                    return SearchConstants::GetTagSearchModels();
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
                    if (query.IsTag() && query.Query() == SearchConstants::TRANSITION_CATEGORY_NAME)
                    {
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

                }
            }
        }
    }
}
