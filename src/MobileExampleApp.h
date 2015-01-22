// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "GlobeCamera.h"
#include "EegeoWorld.h"
#include "AppInterface.h"
#include "WorldPins.h"
#include "Search.h"
#include "SearchResultOnMap.h"
#include "NavigationService.h"
#include "IPlatformAbstractionModule.h"
#include "PrimaryMenu.h"
#include "SecondaryMenu.h"
#include "SearchResultMenu.h"
#include "Modality.h"
#include "FlattenButton.h"
#include "Search.h"
#include "WorldPins.h"
#include "SearchResultOnMap.h"
#include "Pins.h"
#include "Reaction.h"
#include "PlaceJumps.h"
#include "IIdentity.h"
#include "SearchResultPoi.h"
#include "WeatherMenu.h"
#include "CameraTransitions.h"
#include "PrimaryMenuModule.h"
#include "SecondaryMenuModule.h"
#include "ModalityModule.h"
#include "MenuModel.h"
#include "MenuViewModel.h"
#include "SearchResultMenuModule.h"
#include "MenuOptionsModel.h"
#include "AboutPageModule.h"
#include "SearchModule.h"
#include "SearchResultOnMapModule.h"
#include "WorldPinsModule.h"
#include "RegularTexturePageLayout.h"
#include "PinsModule.h"
#include "SearchResultRepository.h"
#include "LatLongAltitude.h"
#include "ReactionModelModule.h"
#include "ReactionControllerModule.h"
#include "SearchResultPoiModule.h"
#include "FlattenButtonModule.h"
#include "PlaceJumpsModule.h"
#include "IPlaceJumpController.h"
#include "WeatherMenuModule.h"
#include "CompassModule.h"
#include "CategorySearch.h"
#include "WorldAreaLoader.h"
#include "InitialExperience.h"
#include "IInitialExperienceModule.h"
#include "MyPinCreation.h"
#include "MyPinCreationDetails.h"
#include "MyPins.h"
#include "MyPinDetails.h"
#include "PersistentSettings.h"
#include "BidirectionalBus.h"
#include "CameraFrustumStreamingVolume.h"
#include "ScreenProperties.h"
#include "CameraFrustumStreamingVolume.h"
#include "PlatformConfig.h"

namespace ExampleApp
{
    class MobileExampleApp : private Eegeo::NonCopyable
    {
    private:
        Eegeo::Camera::GlobeCamera::GpsGlobeCameraController* m_pGlobeCameraController;
        Eegeo::ITouchController* m_pCameraTouchController;
        Eegeo::EegeoWorld* m_pWorld;
        Eegeo::Location::NavigationService* m_pNavigationService;
        Eegeo::Modules::IPlatformAbstractionModule& m_platformAbstractions;
        Eegeo::Rendering::LoadingScreen* m_pLoadingScreen;
        Eegeo::Blitter* m_pBlitter;
        Eegeo::Rendering::ScreenProperties m_screenProperties;
        bool m_initialisedApplicationViewState;
        float m_pinDiameter;

        CameraTransitions::SdkModel::ICameraTransitionController* m_pCameraTransitionController;

        ExampleApp::PersistentSettings::IPersistentSettingsModel& m_persistentSettings;
        Eegeo::Helpers::IdentityProvider m_identityProvider;
        ExampleApp::PrimaryMenu::View::IPrimaryMenuModule* m_pPrimaryMenuModule;
        ExampleApp::SecondaryMenu::SdkModel::ISecondaryMenuModule* m_pSecondaryMenuModule;
        ExampleApp::SearchResultMenu::SdkModel::ISearchResultMenuModule* m_pSearchResultMenuModule;
        ExampleApp::Modality::View::IModalityModule* m_pModalityModule;
        ExampleApp::CategorySearch::SdkModel::ICategorySearchModule* m_pCategorySearchModule;
        ExampleApp::FlattenButton::SdkModel::IFlattenButtonModule* m_pFlattenButtonModule;
        Search::SdkModel::ISearchModule* m_pSearchModule;
        Eegeo::Rendering::ITexturePageLayout* m_pPinIconsTexturePageLayout;
        Eegeo::Helpers::GLHelpers::TextureInfo m_pinIconsTexture;
        Eegeo::Pins::PinsModule* m_pPinsModule;
        ExampleApp::WorldPins::SdkModel::IWorldPinsModule* m_pWorldPinsModule;
        SearchResultOnMap::SdkModel::ISearchResultOnMapModule* m_pSearchResultOnMapModule;
        ExampleApp::Reaction::View::IReactionModelModule* m_pReactionModelModule;
        ExampleApp::Reaction::View::IReactionControllerModule* m_pReactionControllerModule;
        ExampleApp::SearchResultPoi::View::ISearchResultPoiModule* m_pSearchResultPoiModule;
        ExampleApp::PlaceJumps::SdkModel::IPlaceJumpsModule* m_pPlaceJumpsModule;
        ExampleApp::WeatherMenu::SdkModel::IWeatherMenuModule* m_pWeatherMenuModule;
        ExampleApp::Compass::SdkModel::ICompassModule* m_pCompassModule;
        ExampleApp::WorldAreaLoader::SdkModel::IWorldAreaLoaderModule* m_pWorldAreaLoaderModule;
        ExampleApp::AboutPage::View::IAboutPageModule* m_pAboutPageModule;
        ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule& m_initialExperienceModule;
        ExampleApp::MyPinCreation::PoiRing::SdkModel::IPoiRingModule* m_pPoiRingModule;
        ExampleApp::MyPinCreation::SdkModel::IMyPinCreationModule* m_pMyPinCreationModule;
        ExampleApp::MyPinCreationDetails::View::IMyPinCreationDetailsModule* m_pMyPinCreationDetailsModule;
        ExampleApp::MyPins::SdkModel::IMyPinsModule* m_pMyPinsModule;
        ExampleApp::MyPinDetails::SdkModel::IMyPinDetailsModule* m_pMyPinDetailsModule;
        Eegeo::Streaming::CameraFrustumStreamingVolume* m_pStreamingVolume;
        ExampleAppMessaging::TMessageBus& m_messageBus;

        void CreateApplicationModelModules();

        void DestroyApplicationModelModules();

        void UpdateLoadingScreen(float dt);

        std::vector<ExampleApp::OpenableControl::View::IOpenableControlViewModel*> GetOpenableControls() const;

        std::vector<ExampleApp::ScreenControl::View::IScreenControlViewModel*> GetReactorControls() const;

        void InitialisePinsModules(Eegeo::Modules::Map::MapModule& mapModule, Eegeo::EegeoWorld& world);

    public:
        MobileExampleApp(const std::string& apiKey,
                         Eegeo::Modules::IPlatformAbstractionModule& platformAbstractions,
                         Eegeo::Rendering::ScreenProperties& screenProperties,
                         Eegeo::Location::ILocationService& locationService,
                         Eegeo::UI::NativeUIFactories& nativeUIFactories,
                         Eegeo::Config::PlatformConfig platformConfig,
                         Eegeo::Helpers::Jpeg::IJpegLoader& jpegLoader,
                         ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule& initialExperienceModule,
                         ExampleApp::PersistentSettings::IPersistentSettingsModel& persistentSettings,
                         ExampleAppMessaging::TMessageBus& messageBus);


        ~MobileExampleApp();

        Eegeo::EegeoWorld& World()
        {
            return * m_pWorld;
        }

        float PinDiameter() const
        {
            return m_pinDiameter;
        }

        CameraTransitions::SdkModel::ICameraTransitionController& CameraTransitionController() const
        {
            return *m_pCameraTransitionController;
        }

        const ExampleApp::PrimaryMenu::View::IPrimaryMenuModule& PrimaryMenuModule() const
        {
            return *m_pPrimaryMenuModule;
        }

        const ExampleApp::SecondaryMenu::SdkModel::ISecondaryMenuModule& SecondaryMenuModule() const
        {
            return *m_pSecondaryMenuModule;
        }

        const SearchResultMenu::SdkModel::ISearchResultMenuModule& SearchResultMenuModule() const
        {
            return *m_pSearchResultMenuModule;
        }

        const ExampleApp::Modality::View::IModalityModule& ModalityModule() const
        {
            return *m_pModalityModule;
        }

        const ExampleApp::FlattenButton::SdkModel::IFlattenButtonModule& FlattenButtonModule() const
        {
            return *m_pFlattenButtonModule;
        }

        const Search::SdkModel::ISearchModule& SearchModule() const
        {
            return *m_pSearchModule;
        }

        const Eegeo::Pins::PinsModule& PinsModule() const
        {
            return *m_pPinsModule;
        }

        const ExampleApp::WorldPins::SdkModel::IWorldPinsModule& WorldPinsModule() const
        {
            return *m_pWorldPinsModule;
        }

        const SearchResultOnMap::SdkModel::ISearchResultOnMapModule& SearchResultOnMapModule() const
        {
            return *m_pSearchResultOnMapModule;
        }

        const Reaction::View::IReactionModelModule& ReactionModelModule() const
        {
            return *m_pReactionModelModule;
        }

        const Reaction::View::IReactionControllerModule& ReactionControllerModule() const
        {
            return *m_pReactionControllerModule;
        }

        const ExampleApp::SearchResultPoi::View::ISearchResultPoiModule& SearchResultPoiModule() const
        {
            return *m_pSearchResultPoiModule;
        }

        const ExampleApp::PlaceJumps::SdkModel::IPlaceJumpsModule& PlaceJumpsModule() const
        {
            return *m_pPlaceJumpsModule;
        }

        const ExampleApp::WeatherMenu::SdkModel::IWeatherMenuModule& WeatherMenuModule() const
        {
            return *m_pWeatherMenuModule;
        }

        const ExampleApp::Compass::SdkModel::ICompassModule& CompassModule() const
        {
            return *m_pCompassModule;
        }

        const ExampleApp::AboutPage::View::IAboutPageModule& AboutPageModule() const
        {
            return *m_pAboutPageModule;
        }

        const ExampleApp::CategorySearch::SdkModel::ICategorySearchModule& CategorySearchModule() const
        {
            return *m_pCategorySearchModule;
        }

        const ExampleApp::MyPinCreation::SdkModel::IMyPinCreationModule& MyPinCreationModule() const
        {
            return *m_pMyPinCreationModule;
        }

        const ExampleApp::MyPinCreation::PoiRing::SdkModel::IPoiRingModule& PoiRingModule() const
        {
            return *m_pPoiRingModule;
        }

        const ExampleApp::MyPinCreationDetails::View::IMyPinCreationDetailsModule& MyPinCreationDetailsModule() const
        {
            return *m_pMyPinCreationDetailsModule;
        }

        const ExampleApp::MyPins::SdkModel::IMyPinsModule& MyPinsModule() const
        {
            return *m_pMyPinsModule;
        }

        const ExampleApp::MyPinDetails::SdkModel::IMyPinDetailsModule& MyPinDetailsModule() const
        {
            return *m_pMyPinDetailsModule;
        }

        void OnPause();

        void OnResume();

        void Update (float dt);

        void Draw (float dt);

        void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);


        Eegeo::Streaming::IStreamingVolume& GetUpdatedStreamingVolume(const Eegeo::Camera::CameraState& cameraState,
                const Eegeo::Camera::RenderCamera& renderCamera);

        bool IsLoadingScreenComplete() const
        {
            return m_pLoadingScreen == NULL;
        }

        bool IsRunning() const;

        bool IsApplicationViewStateInitialised() const
        {
            return m_initialisedApplicationViewState;
        }

        void InitialiseApplicationViewState();

        Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& GetCameraController()
        {
            return *m_pGlobeCameraController;
        }

        void Event_TouchRotate 			(const AppInterface::RotateData& data);
        void Event_TouchRotate_Start	(const AppInterface::RotateData& data);
        void Event_TouchRotate_End 		(const AppInterface::RotateData& data);

        void Event_TouchPinch 			(const AppInterface::PinchData& data);
        void Event_TouchPinch_Start 	(const AppInterface::PinchData& data);
        void Event_TouchPinch_End 		(const AppInterface::PinchData& data);

        void Event_TouchPan				(const AppInterface::PanData& data);
        void Event_TouchPan_Start		(const AppInterface::PanData& data);
        void Event_TouchPan_End 		(const AppInterface::PanData& data);

        void Event_TouchTap 			(const AppInterface::TapData& data);
        void Event_TouchDoubleTap		(const AppInterface::TapData& data);

        void Event_TouchDown 			(const AppInterface::TouchData& data);
        void Event_TouchMove 			(const AppInterface::TouchData& data);
        void Event_TouchUp 				(const AppInterface::TouchData& data);
    };
}

