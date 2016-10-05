// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ToursModule.h"
#include "TourRepository.h"
#include "GlobeCameraTouchController.h"
#include "ToursCameraController.h"
#include "ToursCameraTransitionController.h"
#include "TourService.h"
#include "TourWorldPinSelectionHandlerFactory.h"
#include "TourAddedObserver.h"
#include "TourRemovedObserver.h"
#include "TourActiveStateChangedMessageHandler.h"
#include "ActiveTourQuitSelectedMessageHandler.h"
#include "TourExplorerViewModel.h"
#include "TourExplorerCompositeViewController.h"
#include "TourSelectedViewObserver.h"
#include "TourFullScreenImageViewModel.h"
#include "TourFullScreenImageCeremonyBeganObserver.h"
#include "TourFullScreenImageCeremonyEndedObserver.h"
#include "ResourceCeilingProvider.h"
#include "IMetricsService.h"
#include "ISearchRefreshService.h"
#include "IWorldPinsService.h"
#include "IMenuViewModel.h"

namespace ExampleApp
{
    namespace Tours
    {
        void ToursModule::Register(const TContainerBuilder& builder)
        {
            builder->registerType<SdkModel::TourRepository>().as<SdkModel::ITourRepository>().singleInstance();
            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                               {
                                                   return std::make_shared<SdkModel::Camera::TourGlobeCameraTouchController>(Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration::CreateDefault(),
                                                                                                           context.resolve<Eegeo::Rendering::ScreenProperties>());
                                               }).singleInstance();
            builder->registerType<SdkModel::Camera::ToursCameraController>().as<SdkModel::Camera::IToursCameraController>().singleInstance();
            builder->registerType<SdkModel::Camera::ToursCameraTransitionController>().as<SdkModel::Camera::IToursCameraTransitionController>().singleInstance();
            builder->registerType<SdkModel::TourService>().as<SdkModel::ITourService>().singleInstance();
            builder->registerType<SdkModel::TourWorldPinSelectionHandlerFactory>().singleInstance();
            builder->registerType<SdkModel::TourAddedObserver>().singleInstance();
            builder->registerType<SdkModel::TourRemovedObserver>().singleInstance();
            builder->registerType<SdkModel::TourActiveStateChangedMessageHandler>().singleInstance();
            builder->registerType<SdkModel::ActiveTourQuitSelectedMessageHandler>().singleInstance();
            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                               {
                                                   return std::make_shared<View::TourExplorer::TourExplorerViewModel>(context.resolve<Eegeo::Helpers::IIdentityProvider>(),
                                                                                                               false);
                                               }).singleInstance();
            builder->registerType<View::TourExplorer::TourExplorerCompositeViewController>().as<View::TourExplorer::ITourExplorerCompositeViewController>().singleInstance();
            builder->registerType<View::TourExplorer::TourSelectedViewObserver>().singleInstance();
            builder->registerType<View::TourFullScreenImage::TourFullScreenImageViewModel>().as<View::TourFullScreenImage::ITourFullScreenImageViewModel>().singleInstance();
            builder->registerType<View::TourFullScreenImage::TourFullScreenImageCeremonyBeganObserver>().singleInstance();
            builder->registerType<View::TourFullScreenImage::TourFullScreenImageCeremonyEndedObserver>().singleInstance();
        }
        
        void ToursModule::RegisterNativeLeaves()
        {
            RegisterLeaf<SdkModel::TourAddedObserver>();
            RegisterLeaf<SdkModel::TourRemovedObserver>();
            RegisterLeaf<SdkModel::TourActiveStateChangedMessageHandler>();
            RegisterLeaf<SdkModel::ActiveTourQuitSelectedMessageHandler>();
            RegisterLeaf<View::TourExplorer::TourSelectedViewObserver>();
            RegisterLeaf<View::TourFullScreenImage::TourFullScreenImageCeremonyBeganObserver>();
            RegisterLeaf<View::TourFullScreenImage::TourFullScreenImageCeremonyEndedObserver>();
        }
    }
}
