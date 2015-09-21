// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"
#include "ScreenControlViewModelIncludes.h"
#include "GlobeCameraTouchController.h"

namespace ExampleApp
{
    namespace Tours
    {
        class IToursModule
        {
        public:
            virtual ~IToursModule() { }
            
            virtual SdkModel::ITourService& GetTourService() const = 0;
            
            virtual SdkModel::ITourRepository& GetTourRepository() const = 0;
            
            virtual SdkModel::Camera::IToursCameraController& GetCameraController() const = 0;
            
            virtual SdkModel::Camera::IToursCameraTransitionController & GetCameraTransitionController() const = 0;
            
            virtual Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& GetCameraTouchController() const = 0;
            
            virtual View::TourExplorer::ITourExplorerViewModel& GetToursExplorerViewModel() const = 0;
            
            virtual View::TourExplorer::ITourExplorerCompositeViewController& GetToursExplorerCompositeViewController() const = 0;
            
            virtual ScreenControl::View::IScreenControlViewModel& GetToursExplorerScreenControlViewModel() const = 0;
            
            virtual View::TourFullScreenImage::ITourFullScreenImageViewModel& GetTourFullScreenImageViewModel() const = 0;
        };
    }
}
