//
// Created by david.crooks on 13/03/2018.
//

#pragma once
#include <string>
#include "BidirectionalBus.h"
#include "IAppCameraController.h"
#include "IAutocompleteSuggestionQueryPerformer.h"
#include "Web.h"
#include "WebLoadRequestCompletionCallback.h"
#include "IEegeoParser.h"

#include "UrlHelpers.h"

namespace ExampleApp {
    namespace Search {
        namespace SdkModel {
            class AutocompleteSuggestionQueryPerformer : public IAutocompleteSuggestionQueryPerformer {
                ExampleApp::AppCamera::SdkModel::IAppCameraController& m_cameraController;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                std::string m_responseString;
                Eegeo::Web::TWebLoadRequestCompletionCallback<AutocompleteSuggestionQueryPerformer> m_webRequestCompleteCallback;
                Eegeo::Web::IWebLoadRequest* m_pWebLoadRequest;
                Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
                Search::EegeoPois::SdkModel::IEegeoParser& m_eeGeoParser;
                SearchQuery m_current_query;
                Eegeo::Helpers::UrlHelpers::IUrlEncoder& m_urlEncoder;
            public:
                AutocompleteSuggestionQueryPerformer(ExampleApp::AppCamera::SdkModel::IAppCameraController& cameraController,
                                                     Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                     Search::EegeoPois::SdkModel::IEegeoParser& eeGeoParser,
                                                     const std::string& serviceUrl,
                                                     const Eegeo::Web::ApiTokenModel& apiTokenModel,
                                                     Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                        ExampleAppMessaging::TMessageBus& messageBus);
               ~AutocompleteSuggestionQueryPerformer();
                void PerformSuggestionsQuery(const std::string& query);
                void Cancel();

                void OnWebResponseReceived(Eegeo::Web::IWebResponse& webResponse);
            private:
                const std::string m_serviceUrl;
                const Eegeo::Web::ApiTokenModel& m_apiTokenModel;
            };
        }
    }
}

