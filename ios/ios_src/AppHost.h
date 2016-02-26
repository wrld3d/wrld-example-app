// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <string>
#include <vector>
#include "Types.h"
#include "Graphics.h"
#include "IJpegLoader.h"
#include "GlobeCameraInterestPointProvider.h"
#include "iOSInputBoxFactory.h"
#include "iOSKeyboardInputFactory.h"
#include "iOSAlertBoxFactory.h"
#include "NativeUIFactories.h"
#include "Blitter.h"
#include "AppInputDelegate.h"
#include "AppLocationDelegate.h"
#include "Modules.h"
#include "MobileExampleApp.h"
#include "InitialExperience.h"
#include "iOSPersistentSettingsModel.h"
#include "ViewControllerUpdater.h"
#include "SettingsMenuViewIncludes.h"
#include "SearchMenuViewIncludes.h"
#include "SearchResultSectionViewIncludes.h"
#include "ModalBackgroundViewIncludes.h"
#include "FlattenButtonViewIncludes.h"
#include "SearchResultPoiViewIncludes.h"
#include "WorldPinOnMapViewIncludes.h"
#include "CompassViewIncludes.h"
#include "AboutPageViewIncludes.h"
#include "MyPinCreationInitiationViewIncludes.h"
#include "MyPinCreationConfirmationViewIncludes.h"
#include "MyPinCreationDetailsViewIncludes.h"
#include "BidirectionalBus.h"
#include "MyPinDetailsViewIncludes.h"
#include "iOSConnectivityService.h"
#include "OptionsViewIncludes.h"
#include "WatermarkViewIncludes.h"
#include "TourWebViewIncludes.h"
#include "TourExplorerViewIncludes.h"
#include "TourFullScreenImageViewIncludes.h"
#include "InitialExperienceIntroViewIncludes.h"
#include "NetIncludes.h"
#include "Search.h"
#include "SdkModelDomainEventBus.h"
#include "IEegeoErrorHandler.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "iOSFlurryMetricsService.h"
#include "Interiors.h"
#include "InteriorsExplorerViewIncludes.h"
#include "ImageStore.h"
#include "ICallback.h"
#include "UserInteraction.h"
#include "LinkOutObserver.h"
#include "URLRequestHandler.h"
#include "SurveyViewIncludes.h"

@class ViewController;
class AppInputDelegate;
class AppLocationDelegate;

class AppHost : public Eegeo::IEegeoErrorHandler, protected Eegeo::NonCopyable
{
public:
    AppHost(
        ViewController& viewController,
        UIView* pView,
        Eegeo::Rendering::ScreenProperties screenProperties,
        const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
        ExampleApp::Metrics::iOSFlurryMetricsService& metricsService
    );
    ~AppHost();

    bool IsRunning();

    void Update(float dt);
    void Draw(float dt);

    void OnPause();
    void OnResume();

    void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);
    
    void HandleFailureToProvideWorkingApiKey();
    
    void HandleFailureToDownloadBootstrapResources();
    
    void HandleNoConnectivityWarning();
    
    void HandleInvalidConnectivityError();

private:
    UIView* m_pView;
    ViewController& m_viewController;
    Eegeo::Helpers::Jpeg::IJpegLoader* m_pJpegLoader;
    Eegeo::iOS::iOSLocationService* m_piOSLocationService;
    Eegeo::iOS::iOSConnectivityService* m_piOSConnectivityService;
    AppInputDelegate* m_pAppInputDelegate;
    AppLocationDelegate* m_pAppLocationDelegate;

    Eegeo::UI::NativeInput::iOS::iOSInputBoxFactory m_iOSInputBoxFactory;
    Eegeo::UI::NativeInput::iOS::iOSKeyboardInputFactory m_iOSKeyboardInputFactory;
    Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory m_iOSAlertBoxFactory;
    Eegeo::UI::NativeUIFactories m_iOSNativeUIFactories;
    Eegeo::iOS::iOSPlatformAbstractionModule* m_piOSPlatformAbstractionModule;
    
    ExampleApp::SettingsMenu::View::ISettingsMenuViewModule* m_pSettingsMenuViewModule;
    ExampleApp::SearchMenu::View::ISearchMenuViewModule* m_pSearchMenuViewModule;
    ExampleApp::SearchResultSection::View::ISearchResultSectionViewModule* m_pSearchResultSectionViewModule;
    ExampleApp::ModalBackground::View::IModalBackgroundViewModule* m_pModalBackgroundViewModule;
    ExampleApp::FlattenButton::View::IFlattenButtonViewModule* m_pFlattenButtonViewModule;
    ExampleApp::SearchResultPoi::View::ISearchResultPoiViewModule* m_pSearchResultPoiViewModule;
    ExampleApp::WorldPins::View::IWorldPinOnMapViewModule* m_pWorldPinOnMapViewModule;
    ExampleApp::Compass::View::ICompassViewModule* m_pCompassViewModule;
    ExampleApp::ViewControllerUpdater::View::IViewControllerUpdaterModule* m_pViewControllerUpdaterModule;
    ExampleApp::PersistentSettings::iOSPersistentSettingsModel m_iOSPersistentSettingsModel;
    ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule* m_pInitialExperienceModule;
    ExampleApp::AboutPage::View::IAboutPageViewModule* m_pAboutPageViewModule;
    ExampleApp::MyPinCreation::View::IMyPinCreationInitiationViewModule* m_pMyPinCreationInitiationViewModule;
    ExampleApp::MyPinCreation::View::IMyPinCreationConfirmationViewModule* m_pMyPinCreationConfirmationViewModule;
    ExampleApp::MyPinCreationDetails::View::IMyPinCreationDetailsViewModule* m_pMyPinCreationDetailsViewModule;
    ExampleApp::MyPinDetails::View::IMyPinDetailsViewModule* m_pMyPinDetailsViewModule;
    ExampleApp::Options::View::IOptionsViewModule* m_pOptionsViewModule;
    ExampleApp::Watermark::View::IWatermarkViewModule* m_pWatermarkViewModule;
    ExampleApp::Tours::View::TourWeb::ITourWebViewModule* m_pTourWebViewModule;
    ExampleApp::Tours::View::TourExplorer::ITourExplorerViewModule* m_pTourExplorerViewModule;
    ExampleApp::Tours::View::TourFullScreenImage::ITourFullScreenImageViewModule* m_pTourFullScreenImageViewModule;
    ExampleApp::InitialExperience::View::IInitialExperienceIntroViewModule* m_pInitialExperienceIntroViewModule;
    ExampleApp::Net::SdkModel::INetworkCapabilities* m_pNetworkCapabilities;
    std::map<std::string,ExampleApp::Search::SdkModel::ISearchServiceModule*> m_searchServiceModules;
    ExampleApp::Metrics::iOSFlurryMetricsService& m_iOSFlurryMetricsService;
    ExampleApp::InteriorsExplorer::View::IInteriorsExplorerViewModule* m_pInteriorsExplorerViewModule;
    ExampleApp::LinkOutObserver::LinkOutObserver* m_pLinkOutObserver;
    ExampleApp::URLRequest::View::URLRequestHandler* m_pURLRequestHandler;
    ExampleApp::Surveys::View::ISurveyViewModule* m_pSurveyViewModule;
    
    ImageStore* m_pImageStore;
    
    ExampleApp::MobileExampleApp* m_pApp;
    bool m_requestedApplicationInitialiseViewState;

    ExampleApp::ExampleAppMessaging::TMessageBus m_messageBus;
    ExampleApp::ExampleAppMessaging::TSdkModelDomainEventBus m_sdkModelDomainEventBus;
    
    Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<AppHost> m_failAlertHandler;
    Eegeo::Helpers::TCallback1<AppHost, const ExampleApp::UserInteraction::UserInteractionEnabledChangedMessage&> m_userInteractionEnabledChangedHandler;

    void CreateApplicationViewModules(const Eegeo::Rendering::ScreenProperties& screenProperties);
    void DestroyApplicationViewModules();
    
    void SetTouchExclusivity();
    
    void HandleStartupFailure();
    void HandleUserInteractionEnabledChanged(const ExampleApp::UserInteraction::UserInteractionEnabledChangedMessage& message);
};

