// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once
#include "DeepLink.h"
#include "CameraTransitions.h"
#include "ApplicationConfig.h"
#include "IAlertBoxFactory.h"
#include "IWebLoadRequestFactory.h"

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            class DeepLinkModule
            {
            public:
                DeepLinkModule(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController, Eegeo::Web::IWebLoadRequestFactory& webFactory, Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory, ApplicationConfig::ApplicationConfiguration& defaultConfig, ExampleApp::ApplicationConfig::SdkModel::ApplicationConfigurationChangedHolder& applicationConfigurationChangedHolder);
                ~DeepLinkModule();
                DeepLinkController& GetDeepLinkController();
            private:
                DeepLinkModel* m_pDeepLinkModel;
                DeepLinkController* m_pDeepLinkController;
            };
        }
    }
}
