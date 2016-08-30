// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Tours.h"
#include "IToursCameraTransitionController.h"
#include "GlobeCamera.h"
#include "Terrain.h"
#include <memory>

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                class ToursCameraTransitionController : public IToursCameraTransitionController, private Eegeo::NonCopyable
                {
                public:
                    
                    ToursCameraTransitionController(const std::shared_ptr<IToursCameraController>& toursCameraController,
                                                    const std::shared_ptr<TourGlobeCameraTouchController>& touchController);
                    
                    ~ToursCameraTransitionController();
                    
                    bool IsTransitionComplete() const;
                    
                    bool IsTransitioning() const;
                    
                    void Update(float dt);
                    
                    void TransitionTo(IToursCameraMode& targetCameraMode, bool jumpIfFar);
                    
                    void ResetControllerState();
                    
                private:
                    
                    void PerformCameraTransitionOrFade(const ToursCameraState& currentState,
                                                       const ToursCameraState& desiredState);
                    
                    bool ShouldPerformCameraSpline(const ToursCameraState& currentState,
                                                   const ToursCameraState& desiredState);
                    
                    const std::shared_ptr<IToursCameraController>& m_toursCameraController;
                    
                    // This class manages the lifetime of m_pToursTransitionMode.
                    IToursCameraTransitionMode* m_pToursTransitionMode;
                    
                    // This class does not manage the lifetime of the modes, but they are pointers as they are transient
                    // and replaceable. Assumption: the lifetime of the IToursCameraMode instances is longer than the time
                    //for which they are referenced by this class.
                    IToursCameraMode* m_pToursCurrentMode;
                    IToursCameraMode* m_pToursNextMode;
                    
                    const std::shared_ptr<TourGlobeCameraTouchController> m_touchController;
                };
            }
        }
    }
}
