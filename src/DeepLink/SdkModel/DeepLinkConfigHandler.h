// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IDeepLinkHandler.h"
#include "Web.h"
#include "CameraTransitions.h"
#include "ApplicationConfiguration.h"
#include "WebLoadRequestCompletionCallback.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "PendingWebRequestsContainer.h"

#include "IAlertBoxFactory.h"

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            class DeepLinkConfigHandler: public IDeepLinkHandler
            {
            public:
                DeepLinkConfigHandler(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController, Eegeo::Web::IWebLoadRequestFactory& webRequestFactory, Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory, ExampleApp::ApplicationConfig::ApplicationConfiguration& defaultConfig, ExampleApp::ApplicationConfig::SdkModel::ApplicationConfigurationChangedHolder& applicationConfigurationChangedHolder);
                void HandleDeepLink(const AppInterface::UrlData& data);
                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
            private:
                Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
                Eegeo::UI::NativeAlerts::IAlertBoxFactory& m_alertBoxFactory;
                Eegeo::Web::PendingWebRequestsContainer m_pendingWebRequestsContainer;
                Eegeo::Web::IWebLoadRequest* m_pWebLoadRequest;
                ApplicationConfig::ApplicationConfiguration& m_defaultConfig;
                Eegeo::Web::TWebLoadRequestCompletionCallback<DeepLinkConfigHandler> m_configRequestCompleteCallback;
                Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<DeepLinkConfigHandler> m_failAlertHandler;
                std::string GenerateConfigUrl(const AppInterface::UrlData& data) const;
                ExampleApp::ApplicationConfig::SdkModel::ApplicationConfigurationChangedHolder& m_applicationConfigurationChangedHolder;
                void HandleConfigResponse(Eegeo::Web::IWebResponse& webResponse);
                void OnFailAlertBoxDismissed();
            };
        
            const std::string CONFIG_FILES_HOME = "http://cdn1.eegeo.com/test_configs";
        }
    }
}
