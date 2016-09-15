// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    class MobileExampleApp;
}

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
#include "AppInputDelegate.h"
#include "AppLocationDelegate.h"
#include "Modules.h"
#include "InitialExperience.h"
#include "iOSPersistentSettingsModel.h"
#include "ViewControllerUpdater.h"
#include "SettingsMenuViewIncludes.h"
#include "SearchMenuViewIncludes.h"
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
#include "IMenuReactionModel.h"
#include "ApplicationConfiguration.h"
#include "AppWiring.h"
#include "Hypodermic/ContainerBuilder.h"
#include "ICallback.h"
#include "IViewControllerUpdaterModel.h"

#include <memory>

@class ViewController;
class AppInputDelegate;
class AppLocationDelegate;

class AppHost : protected Eegeo::NonCopyable
{
public:
    AppHost(
        ViewController& viewController,
        UIView* pView,
        Eegeo::Rendering::ScreenProperties screenProperties,
        ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
        ExampleApp::Metrics::iOSFlurryMetricsService& metricsService
    );
    ~AppHost();

    bool IsRunning();

    void Update(float dt);
    void Draw(float dt);

    void OnPause();
    void OnResume();

    void OnLoadingScreenComplete();
    
    void NotifyScreenPropertiesChanged(const std::shared_ptr<Eegeo::Rendering::ScreenProperties>& screenProperties);
    
    template <class T>
    void AddSubview()
    {
        [m_pView addSubview: m_wiring->Resolve<T>()->Get()];
    }
    
    template <class T>
    void AddViewControllerUpdatable()
    {
        auto t = m_wiring->Resolve<T>();
        m_wiring->Resolve<ExampleApp::ViewControllerUpdater::View::IViewControllerUpdaterModel>()->AddUpdateableObject(*t);
    }

private:
    Eegeo::Helpers::TCallback0<AppHost> m_loadingSreenCompleteCallback;
    
    ExampleApp::ExampleAppMessaging::TMessageBus& GetMessageBus();
    ExampleApp::ExampleAppMessaging::TSdkModelDomainEventBus& GetSdkMessageBus();

    UIView* m_pView;
    ViewController& m_viewController;
    AppInputDelegate* m_pAppInputDelegate;
    std::shared_ptr<ExampleApp::AppWiring> m_wiring;
    std::shared_ptr<ExampleApp::MobileExampleApp> m_app;

    ExampleApp::Tours::View::TourWeb::ITourWebViewModule* m_pTourWebViewModule;
    ExampleApp::Tours::View::TourExplorer::ITourExplorerViewModule* m_pTourExplorerViewModule;
    ExampleApp::Tours::View::TourFullScreenImage::ITourFullScreenImageViewModule* m_pTourFullScreenImageViewModule;
    ExampleApp::Surveys::View::ISurveyViewModule* m_pSurveyViewModule;
    
    Eegeo::Helpers::TCallback1<AppHost, const ExampleApp::UserInteraction::UserInteractionEnabledChangedMessage&> m_userInteractionEnabledChangedHandler;

    void RegisterApplicationViewModules();
    void DestroyApplicationViewModules();
    
    void AddApplicationViews();
    
    void SetTouchExclusivity();
    
    void HandleUserInteractionEnabledChanged(const ExampleApp::UserInteraction::UserInteractionEnabledChangedMessage& message);
};

