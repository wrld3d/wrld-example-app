// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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
#include "PoiCreation.h"
#include "PoiCreationDetails.h"
#include "MyPins.h"

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
        bool m_initialisedApplicationState;
        float m_pinDiameter;
        
        CameraTransitions::ICameraTransitionController* m_pCameraTransitionController;
        
        Eegeo::Helpers::IdentityProvider m_identityProvider;
        ExampleApp::PrimaryMenu::IPrimaryMenuModule* m_pPrimaryMenuModule;
        ExampleApp::SecondaryMenu::ISecondaryMenuModule* m_pSecondaryMenuModule;
        ExampleApp::SearchResultMenu::ISearchResultMenuModule* m_pSearchResultMenuModule;
        ExampleApp::Modality::IModalityModule* m_pModalityModule;
        ExampleApp::CategorySearch::ICategorySearchModule* m_pCategorySearchModule;
        ExampleApp::FlattenButton::IFlattenButtonModule* m_pFlattenButtonModule;
        ExampleApp::Search::ISearchModule* m_pSearchModule;
        Eegeo::Rendering::ITexturePageLayout* m_pPinIconsTexturePageLayout;
        Eegeo::Helpers::GLHelpers::TextureInfo m_pinIconsTexture;
        Eegeo::Pins::PinsModule* m_pPinsModule;
        ExampleApp::WorldPins::IWorldPinsModule* m_pWorldPinsModule;
        ExampleApp::SearchResultOnMap::ISearchResultOnMapModule* m_pSearchResultOnMapModule;
        ExampleApp::Reaction::IReactionModelModule* m_pReactionModelModule;
        ExampleApp::Reaction::IReactionControllerModule* m_pReactionControllerModule;
        ExampleApp::SearchResultPoi::ISearchResultPoiModule* m_pSearchResultPoiModule;
        ExampleApp::PlaceJumps::IPlaceJumpsModule* m_pPlaceJumpsModule;
        ExampleApp::WeatherMenu::IWeatherMenuModule* m_pWeatherMenuModule;
        ExampleApp::Compass::ICompassModule* m_pCompassModule;
        ExampleApp::WorldAreaLoader::IWorldAreaLoaderModule* m_pWorldAreaLoaderModule;
        ExampleApp::AboutPage::IAboutPageModule* m_pAboutPageModule;
        ExampleApp::InitialExperience::IInitialExperienceModule& m_initialExperienceModule;
        ExampleApp::PoiCreation::PoiRing::IPoiRingModule* m_pPoiRingModule;
        ExampleApp::PoiCreation::IPoiCreationModule* m_pPoiCreationModule;
        ExampleApp::PoiCreationDetails::IPoiCreationDetailsModule* m_pPoiCreationDetailsModule;
        ExampleApp::MyPins::IMyPinsModule* m_pMyPinsModule;
        
        void CreateApplicationModelModules();
        
        void DestroyApplicationModelModules();
        
        void InitialiseApplicationState();
        
        void UpdateLoadingScreen(float dt);
        
        std::vector<ExampleApp::OpenableControlViewModel::IOpenableControlViewModel*> GetOpenableControls() const;
        
        std::vector<ExampleApp::ScreenControlViewModel::IScreenControlViewModel*> GetReactorControls() const;
        
        void InitialisePinsModules(Eegeo::Modules::Map::MapModule& mapModule, Eegeo::EegeoWorld& world);
        
    public:
        MobileExampleApp(Eegeo::Modules::IPlatformAbstractionModule& platformAbstractions,
                         Eegeo::Rendering::ScreenProperties& screenProperties,
                         Eegeo::Location::ILocationService& locationService,
                         Eegeo::UI::NativeUIFactories& nativeUIFactories,
                         Eegeo::Config::PlatformConfig platformConfig,
                         Eegeo::Helpers::Jpeg::IJpegLoader& jpegLoader,
                         ExampleApp::InitialExperience::IInitialExperienceModule& initialExperienceModule);
        
        
        ~MobileExampleApp();
        
        Eegeo::EegeoWorld& World()
        {
            return * m_pWorld;
        }
        
        float PinDiameter() const { return m_pinDiameter; }
        
        const ExampleApp::PrimaryMenu::IPrimaryMenuModule& PrimaryMenuModule() const { return *m_pPrimaryMenuModule; }
        
        const ExampleApp::SecondaryMenu::ISecondaryMenuModule& SecondaryMenuModule() const { return *m_pSecondaryMenuModule; }
        
        const ExampleApp::SearchResultMenu::ISearchResultMenuModule& SearchResultMenuModule() const { return *m_pSearchResultMenuModule; }
        
        const ExampleApp::Modality::IModalityModule& ModalityModule() const { return *m_pModalityModule; }
        
        const ExampleApp::FlattenButton::IFlattenButtonModule& FlattenButtonModule() const { return *m_pFlattenButtonModule; }
        
        const ExampleApp::Search::ISearchModule& SearchModule() const { return *m_pSearchModule; }
        
        const Eegeo::Pins::PinsModule& PinsModule() const { return *m_pPinsModule; }
        
        const ExampleApp::WorldPins::IWorldPinsModule& WorldPinsModule() const { return *m_pWorldPinsModule; }
        
        const ExampleApp::SearchResultOnMap::ISearchResultOnMapModule& SearchResultOnMapModule() const { return *m_pSearchResultOnMapModule; }
        
        const ExampleApp::Reaction::IReactionModelModule& ReactionModelModule() const { return *m_pReactionModelModule; }
        
        const ExampleApp::Reaction::IReactionControllerModule& ReactionControllerModule() const { return *m_pReactionControllerModule; }
        
        const ExampleApp::SearchResultPoi::ISearchResultPoiModule& SearchResultPoiModule() const { return *m_pSearchResultPoiModule; }
        
        const ExampleApp::PlaceJumps::IPlaceJumpsModule& PlaceJumpsModule() const { return *m_pPlaceJumpsModule; }
        
        const ExampleApp::WeatherMenu::IWeatherMenuModule& WeatherMenuModule() const { return *m_pWeatherMenuModule; }
        
        const ExampleApp::Compass::ICompassModule& CompassModule() const { return *m_pCompassModule; }
        
        const ExampleApp::AboutPage::IAboutPageModule& AboutPageModule() const { return *m_pAboutPageModule; }
        
        const ExampleApp::CategorySearch::ICategorySearchModule& CategorySearchModule() const { return *m_pCategorySearchModule; }
        
        const ExampleApp::PoiCreation::IPoiCreationModule& PoiCreationModule() const { return *m_pPoiCreationModule; }
        
        const ExampleApp::PoiCreation::PoiRing::IPoiRingModule& PoiRingModule() const { return *m_pPoiRingModule; }
        
        const ExampleApp::PoiCreationDetails::IPoiCreationDetailsModule& PoiCreationDetailsModule() const { return *m_pPoiCreationDetailsModule; }
        
        const ExampleApp::MyPins::IMyPinsModule& MyPinsModule() const { return *m_pMyPinsModule; }
        
        void OnPause();
        
        void OnResume();
        
        void Update (float dt);
        
        void Draw (float dt);
        
        bool IsRunning() const;
        
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

