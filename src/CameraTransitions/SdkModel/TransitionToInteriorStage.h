// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICameraTransitionStage.h"
#include "InteriorController.h"
#include "InteriorSelectionModel.h"
#include "InteriorsExplorerCameraController.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            class TransitionToInteriorStage : public ICameraTransitionStage
            {
            public:
                
                TransitionToInteriorStage(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                          const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                          InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& cameraController,
                                          const Eegeo::dv3& newInterestPoint,
                                          float newDistanceToInterest,
                                          const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                          int targetFloorIndex);
                
                void Start();
                void Update(float dt);
                void End();
                const bool StageIsComplete() const;
                const bool StageHasFailed() const;
                
            private:
                
                Eegeo::Resources::Interiors::InteriorController& m_interiorController;
                const Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& m_cameraController;
                
                Eegeo::dv3 m_newInterestPoint;
                Eegeo::dv3 m_startInterestPoint;
                float m_startDistanceToInterest;
                float m_transitionTime;
                float m_transitionDuration;
                
                Eegeo::Resources::Interiors::InteriorId m_interiorId;
                const float m_targetDistanceToInterest;
                int m_targetFloorIndex;
                const bool m_isAlreadyInInterior;
            };
        }
    }
}