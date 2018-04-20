// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once
#include "DeepLink.h"
#include "CameraTransitions.h"
#include "ApplicationConfig.h"
#include "IAlertBoxFactory.h"
#include "IWebLoadRequestFactory.h"
#include "CoverageTrees.h"
#include "CityThemes.h"
#include "ISearchQueryPerformer.h"
#include "Location.h"
#include "AppModes.h"
#include "Interiors.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            class DeepLinkModule
            {
            public:
                DeepLinkModule(
                    CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                    Eegeo::Web::IWebLoadRequestFactory& webFactory,
                    Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                    ApplicationConfig::ApplicationConfiguration& defaultConfig,
                    Eegeo::Streaming::CoverageTrees::ICoverageTreeManifestLoader& manifestLoader,
                    Eegeo::Streaming::CoverageTrees::CoverageTreeManifestNotifier& manifestNotifier,
                    Eegeo::Resources::CityThemes::CityThemeLoader& cityThemeLoader,
                    Eegeo::Resources::CityThemes::ICityThemesService& cityThemeService,
                    Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                    Eegeo::Location::NavigationService& navigationService,
                    Eegeo::Web::ApiTokenService& apiTokenService,
                    Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                    const ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                    ExampleAppMessaging::TMessageBus& messageBus);

                ~DeepLinkModule();
                DeepLinkController& GetDeepLinkController();
            private:
                DeepLinkModel* m_pDeepLinkModel;
                DeepLinkController* m_pDeepLinkController;
            };
        }
    }
}
