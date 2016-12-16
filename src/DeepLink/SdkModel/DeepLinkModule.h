// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once
#include "DeepLink.h"
#include "CameraTransitions.h"
#include "ApplicationConfig.h"
#include "IAlertBoxFactory.h"
#include "IWebLoadRequestFactory.h"
#include "CoverageTrees.h"
#include "CityThemes.h"
#include "InteriorMenuObserver.h"
#include "AboutPageViewModel.h"

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            class DeepLinkModule: private Eegeo::NonCopyable
            {
            public:

                DeepLinkModule(
                    CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                    Eegeo::Web::IWebLoadRequestFactory& webFactory,
                    Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                    ApplicationConfig::ApplicationConfiguration& defaultConfig,
                    Eegeo::Streaming::CoverageTrees::ICoverageTreeManifestLoader& manifest,
                    Eegeo::Resources::CityThemes::CityThemeLoader& cityThemeLoader,
                    Search::SdkModel::InteriorMenuObserver& interiorMenuObserver,
                    AboutPage::View::IAboutPageViewModel& aboutPageViewModule,
                    Eegeo::Web::ApiTokenService& apiTokenService);

                ~DeepLinkModule();
                DeepLinkController& GetDeepLinkController();
            private:
                DeepLinkModel* m_pDeepLinkModel;
                DeepLinkController* m_pDeepLinkController;
            };
        }
    }
}
