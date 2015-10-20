// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ToursModule.h"
#include "TourExplorerViewModel.h"
#include "TourCameraModule.h"
#include "TourFullScreenImageViewModel.h"
#include "IAppModeModel.h"

namespace ExampleApp
{
    namespace Tours
    {
        ToursModule::ToursModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
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
                                 AppModes::SdkModel::IAppModeModel& appModeModel)
        {
            m_pToursCameraModule = Eegeo_NEW(SdkModel::Camera::TourCameraModule)(resourceCeilingProvider,
                                                                                 screenProperties,
                                                                                 gpsGlobeCameraController,
                                                                                 terrainHeightProvider);
            
            
            m_pTourRepository = Eegeo_NEW(SdkModel::TourRepository);
            
            m_pTourService = Eegeo_NEW(SdkModel::TourService)(*m_pTourRepository,
                                                              m_pToursCameraModule->GetCameraTransitionController(),
                                                              messageBus,
                                                              sdkDomainEventBus);
            
            m_pTourWorldPinSelectionHandlerFactory = Eegeo_NEW(SdkModel::TourWorldPinSelectionHandlerFactory)(*m_pTourService,
                                                                                                              searchRefreshService,
                                                                                                              appModeModel);
            
            m_pTourAddedObserver = Eegeo_NEW(SdkModel::TourAddedObserver)(*m_pTourRepository,
                                                                          worldPinsService,
                                                                          *m_pTourWorldPinSelectionHandlerFactory);
            
            m_pTourRemovedObserver = Eegeo_NEW(SdkModel::TourRemovedObserver)(*m_pTourRepository,
                                                                              worldPinsService);
            
            m_pTourActiveStateChangedMessageHandler = Eegeo_NEW(SdkModel::TourActiveStateChangedMessageHandler)(*m_pTourService,
                                                                                                                messageBus);
            
            m_pActiveTourQuitSelectedMessageHandler = Eegeo_NEW(SdkModel::ActiveTourQuitSelectedMessageHandler)(*m_pTourService,
                                                                                                                searchRefreshService,
                                                                                                                messageBus);
            
            m_pTourChangeRequestMessageHandler = Eegeo_NEW(SdkModel::TourChangeRequestMessageHandler)(*m_pTourRepository,
                                                                                                      *m_pTourService,
                                                                                                      messageBus);
            
            m_pTourExplorerViewModel = Eegeo_NEW(View::TourExplorer::TourExplorerViewModel)(identityProvider.GetNextIdentity(), false);
            
            m_pTourExplorerCompositeViewController = Eegeo_NEW(View::TourExplorer::TourExplorerCompositeViewController)(*m_pTourExplorerViewModel,
                                                                                                                        secondaryMenuViewModel,
                                                                                                                        searchMenuViewModel,
                                                                                                                        compassViewModel,
                                                                                                                        flattenViewModel,
                                                                                                                        myPinCreationViewModel,
                                                                                                                        watermarkViewModel);
            
            m_pTourSelectedViewObserver = Eegeo_NEW(View::TourExplorer::TourSelectedViewObserver)(*m_pTourExplorerCompositeViewController,
                                                                                                  messageBus);
            
            
            m_pTourFullScreenImageViewModel = Eegeo_NEW(View::TourFullScreenImage::TourFullScreenImageViewModel)();
            
            m_pTourFullScreenImageCeremonyBeganObserver = Eegeo_NEW(View::TourFullScreenImage::TourFullScreenImageCeremonyBeganObserver)(*m_pTourFullScreenImageViewModel,
                                                                                                                                         messageBus);
            
            m_pTourFullScreenImageCeremonyEndedObserver = Eegeo_NEW(View::TourFullScreenImage::TourFullScreenImageCeremonyEndedObserver)(*m_pTourFullScreenImageViewModel,
                                                                                                                                         messageBus);
        }
        
        ToursModule::~ToursModule()
        {
            Eegeo_DELETE m_pTourFullScreenImageCeremonyEndedObserver;
            Eegeo_DELETE m_pTourFullScreenImageCeremonyBeganObserver;
            Eegeo_DELETE m_pTourFullScreenImageViewModel;
            
            Eegeo_DELETE m_pTourSelectedViewObserver;
            Eegeo_DELETE m_pTourExplorerCompositeViewController;
            Eegeo_DELETE m_pTourExplorerViewModel;
            
            Eegeo_DELETE m_pTourChangeRequestMessageHandler;
            Eegeo_DELETE m_pActiveTourQuitSelectedMessageHandler;
            Eegeo_DELETE m_pTourActiveStateChangedMessageHandler;
            Eegeo_DELETE m_pTourRemovedObserver;
            Eegeo_DELETE m_pTourAddedObserver;
            Eegeo_DELETE m_pTourWorldPinSelectionHandlerFactory;
            Eegeo_DELETE m_pTourService;
            Eegeo_DELETE m_pTourRepository;
            Eegeo_DELETE m_pToursCameraModule;
        }
        
        SdkModel::ITourService& ToursModule::GetTourService() const
        {
            return *m_pTourService;
        }
        
        SdkModel::ITourRepository& ToursModule::GetTourRepository() const
        {
            return *m_pTourRepository;
        }
        
        SdkModel::Camera::IToursCameraTransitionController& ToursModule::GetCameraTransitionController() const
        {
            return m_pToursCameraModule->GetCameraTransitionController();
        }
        
        SdkModel::Camera::IToursCameraController& ToursModule::GetCameraController() const
        {
            return m_pToursCameraModule->GetToursCameraController();
        }
        
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& ToursModule::GetCameraTouchController() const
        {
            return m_pToursCameraModule->GetCameraTouchController();
        }
        
        View::TourExplorer::ITourExplorerViewModel& ToursModule::GetToursExplorerViewModel() const
        {
            return *m_pTourExplorerViewModel;
        }
        
        View::TourExplorer::TourExplorerCompositeViewController& ToursModule::GetToursExplorerCompositeViewController() const
        {
            return *m_pTourExplorerCompositeViewController;
        }
        
        ScreenControl::View::IScreenControlViewModel& ToursModule::GetToursExplorerScreenControlViewModel() const
        {
            return m_pTourExplorerViewModel->GetScreenControlViewModel();
        }
        
        View::TourFullScreenImage::ITourFullScreenImageViewModel& ToursModule::GetTourFullScreenImageViewModel() const
        {
            return *m_pTourFullScreenImageViewModel;
        }
    }
}
