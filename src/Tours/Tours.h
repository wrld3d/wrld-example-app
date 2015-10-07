// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            class ITourService;
            class ITourRepository;
            class TourModel;
            class TourStateModel;
            class TourWorldPinSelectionHandlerFactory;
        }
        
        namespace SdkModel
        {
            namespace Camera
            {
                struct ToursCameraState;
                
                class IToursCameraMode;
                class IToursCameraTransitionMode;
                class IToursCameraController;
                class IToursCameraTransitionController;
            }
        }
        
        namespace SdkModel
        {
            namespace States
            {
                class ITourStateMachine;
                class ITourStateMachineState;
            }
        }
        
        namespace View
        {
            namespace TourExplorer
            {
                class ITourExplorerView;
                class ITourExplorerViewModel;
                class ITourExplorerCompositeViewController;
            }
            
            namespace TourFullScreenImage
            {
                class ITourFullScreenImageView;
                class ITourFullScreenImageViewModel;
            }
        }
        
        namespace SdkModel
        {
            namespace TourInstances
            {
                namespace Example
                {
                    class ExampleCurrentTourCardTappedHandler;
                }
            }
        }
    }
}
