//
// Created by david.crooks on 13/03/2018.
//

#include "AutocompleteSuggestionQueryPerformer.h"
#include "IWebLoadRequest.h"
#include "IWebLoadRequestFactory.h"
#include <sstream>
#include <iomanip>
#include "ApiTokenModel.h"
#include "CameraState.h"

namespace ExampleApp {
    namespace Search {
        namespace SdkModel {
            AutocompleteSuggestionQueryPerformer::AutocompleteSuggestionQueryPerformer(ExampleApp::AppCamera::SdkModel::IAppCameraController& cameraController,
                                                                                       Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                                                       Search::EegeoPois::SdkModel::IEegeoParser& eeGeoParser,
                                                                                       const std::string& serviceUrl,
                                                                                       const Eegeo::Web::ApiTokenModel& apiTokenModel,
                                                                                       Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                                                                       ExampleAppMessaging::TMessageBus& messageBus)
                    : m_cameraController(cameraController)
                    , m_messageBus(messageBus)
                    , m_webRequestCompleteCallback(this, &AutocompleteSuggestionQueryPerformer::OnWebResponseReceived)
                    , m_webRequestFactory( webRequestFactory)
                    , m_eeGeoParser(eeGeoParser)
                    , m_serviceUrl(serviceUrl)
                    , m_apiTokenModel(apiTokenModel)
                    , m_current_query()
                    , m_urlEncoder(urlEncoder)
            {

            }

            AutocompleteSuggestionQueryPerformer::~AutocompleteSuggestionQueryPerformer()
            {

            }

            void AutocompleteSuggestionQueryPerformer::PerformSuggestionsQuery(const std::string& query){

                Eegeo::Space::LatLongAltitude location = Eegeo::Space::LatLongAltitude::FromECEF(m_cameraController.GetCameraState().InterestPointEcef());
                bool isTag = false;
                bool tryInteriorSearch = false;
                bool selectFirstResult = false;
                float radius = 0.0;
                m_current_query = SearchQuery(query, isTag, tryInteriorSearch, selectFirstResult, location, radius);

                const int timeOutSecs = 30;
                std::stringstream urlstream;
                urlstream.setf(std::ios_base::fixed);

                std::string encodedQuery;
                m_urlEncoder.UrlEncode(query, encodedQuery);

                urlstream << m_serviceUrl << "autocomplete?s=" << encodedQuery;
                urlstream << "&lat=" << std::setprecision(8) << location.GetLatitudeInDegrees();
                urlstream << "&lon=" << std::setprecision(8) << location.GetLongitudeInDegrees();

                urlstream << "&apikey=" << m_apiTokenModel.GetApiKey();
                std::string url = urlstream.str();

                m_pWebLoadRequest = m_webRequestFactory
                        .Begin(Eegeo::Web::HttpVerbs::GET, url, m_webRequestCompleteCallback)
                        .SetShouldCacheAggressively(false)
                        .SetShouldRequestOnlyFromCache(false)
                        .SetTimeout(timeOutSecs)
                        .Build();
                m_pWebLoadRequest->Load();
            }

            void AutocompleteSuggestionQueryPerformer::Cancel()
            {
                Eegeo_ASSERT(m_pWebLoadRequest != NULL, "Cannot cancel autocomplete request - no request exists");
                m_pWebLoadRequest->Cancel();
            }

            void AutocompleteSuggestionQueryPerformer::OnWebResponseReceived(Eegeo::Web::IWebResponse& webResponse)
            {
                std::vector<Search::SdkModel::SearchResultModel> queryResults;
                
                if(!webResponse.IsSucceeded())
                {
                    m_messageBus.Publish(AutocompleteSuggestionsReceivedMessage(webResponse.IsSucceeded(), m_current_query, queryResults));
                    return;
                }
                else if(!webResponse.IsCancelled())
                {
                    size_t resultSize = webResponse.GetBodyData().size();
                    std::string response = std::string(reinterpret_cast<char const*>(&(webResponse.GetBodyData().front())), resultSize);

                    m_eeGeoParser.ParseEegeoQueryResults(response, queryResults);

                    m_messageBus.Publish(AutocompleteSuggestionsReceivedMessage(webResponse.IsSucceeded(), m_current_query, queryResults));
                }
            }

        }
    }
}