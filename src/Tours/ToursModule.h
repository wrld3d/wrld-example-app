// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IToursModule.h"
#include "TourExplorerViewModel.h"
#include "TourRepository.h"
#include "TourService.h"
#include "TourWorldPinSelectionHandlerFactory.h"
#include "TourAddedObserver.h"
#include "TourRemovedObserver.h"
#include "TourExplorerCompositeViewController.h"
#include "TourSelectedViewObserver.h"
#include "Types.h"
#include "ScreenControlViewModelIncludes.h"
#include "IIdentity.h"
#include "BidirectionalBus.h"
#include "WorldPins.h"
#include "IScreenControlViewModel.h"
#include "TourActiveStateChangedMessageHandler.h"
#include "ActiveTourQuitSelectedMessageHandler.h"
#include "TourChangeRequestMessageHandler.h"
#include "IToursCameraModule.h"
#include "ResourceCeilingProvider.h"
#include "ScreenProperties.h"
#include "Search.h"
#include "TourFullScreenImageCeremonyBeganObserver.h"
#include "TourFullScreenImageCeremonyEndedObserver.h"
#include "Menu.h"
#include "Interiors.h"
#include "SdkModelDomainEventBus.h"
#include "AppModes.h"

namespace ExampleApp
{
    namespace Tours
    {
        class ToursModule : public IToursModule, private Eegeo::NonCopyable
        {
            SdkModel::TourRepository* m_pTourRepository;
            SdkModel::TourService* m_pTourService;
            SdkModel::TourWorldPinSelectionHandlerFactory* m_pTourWorldPinSelectionHandlerFactory;
            SdkModel::TourAddedObserver* m_pTourAddedObserver;
            SdkModel::TourRemovedObserver* m_pTourRemovedObserver;
            SdkModel::TourActiveStateChangedMessageHandler* m_pTourActiveStateChangedMessageHandler;
            SdkModel::ActiveTourQuitSelectedMessageHandler* m_pActiveTourQuitSelectedMessageHandler;
            SdkModel::TourChangeRequestMessageHandler* m_pTourChangeRequestMessageHandler;
            SdkModel::Camera::IToursCameraModule* m_pToursCameraModule;
            
            View::TourExplorer::TourExplorerViewModel* m_pTourExplorerViewModel;
            View::TourExplorer::TourSelectedViewObserver* m_pTourSelectedViewObserver;
            View::TourExplorer::TourExplorerCompositeViewController* m_pTourExplorerCompositeViewController;
            
            View::TourFullScreenImage::ITourFullScreenImageViewModel* m_pTourFullScreenImageViewModel;
            View::TourFullScreenImage::TourFullScreenImageCeremonyBeganObserver* m_pTourFullScreenImageCeremonyBeganObserver;
            View::TourFullScreenImage::TourFullScreenImageCeremonyEndedObserver* m_pTourFullScreenImageCeremonyEndedObserver;
            
        public:
            ToursModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                        ExampleAppMessaging::TMessageBus& messageBus,
                        WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                        Search::SdkModel::ISearchRefreshService& searchRefreshService,
                        Menu::View::IMenuViewModel& secondaryMenuViewModel,
                        Menu::View::IMenuViewModel& searchMenuViewModel,
                        ScreenControl::View::IScreenControlViewModel& compassViewModel,
                        ScreenControl::View::IScreenControlViewModel& flattenViewModel,
                        ScreenControl::View::IScreenControlViewModel& myPinCreationViewModel,
                        ScreenControl::View::IScreenControlViewModel& watermarkViewModel,
                        Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                        const Eegeo::Rendering::ScreenProperties& screenProperties,
                        Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& gpsGlobeCameraController,
                        Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                        ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus,
                        AppModes::SdkModel::IAppModeModel& appModeModel);
            
            ~ToursModule();
            
            SdkModel::ITourService& GetTourService() const;
            
            SdkModel::ITourRepository& GetTourRepository() const;
            
            SdkModel::Camera::IToursCameraController& GetCameraController() const;
            
            Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& GetCameraTouchController() const;
            
            SdkModel::Camera::IToursCameraTransitionController & GetCameraTransitionController() const;
            
            View::TourExplorer::ITourExplorerViewModel& GetToursExplorerViewModel() const;
            
            View::TourExplorer::TourExplorerCompositeViewController& GetToursExplorerCompositeViewController() const;
            
            ScreenControl::View::IScreenControlViewModel& GetToursExplorerScreenControlViewModel() const;
            
            View::TourFullScreenImage::ITourFullScreenImageViewModel& GetTourFullScreenImageViewModel() const;
        };
    }
}
