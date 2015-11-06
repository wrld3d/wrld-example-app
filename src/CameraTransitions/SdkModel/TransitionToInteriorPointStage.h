// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICameraTransitionStage.h"
#include "InteriorController.h"
#include "InteriorId.h"
#include "InteriorsExplorer.h"
#include "InteriorsExplorerCameraController.h"
#include "InteriorSelectionModel.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            class TransitionToInteriorPointStage : public ICameraTransitionStage
            {
            public:
                
                TransitionToInteriorPointStage(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                               const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                               InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                               InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& cameraController,
                                               const Eegeo::dv3& newInterestPoint,
                                               float newDistanceToInterest,
                                               const Eegeo::Resources::Interiors::InteriorId &interiorId,
                                               int targetFloorIndex,
                                               bool jumpIfFar=true);
                
                void Start();
                void Update(float dt);
                void End();
                const bool StageIsComplete() const;
                const bool StageHasFailed() const;
                
            private:
                
                bool ShouldJumpTo(Eegeo::dv3& newInterestPoint);
                
                Eegeo::Resources::Interiors::InteriorController& m_interiorController;
                const Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel;
                InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& m_cameraController;
                
                Eegeo::dv3 m_newInterestPoint;
                Eegeo::dv3 m_startInterestPoint;
                float m_startDistanceToInterest;
                float m_transitionTime;
                float m_transitionDuration;
                float m_startCameraInterestAltitude;
                float m_endCameraInterestAltitude;
                float m_cameraInterestAltitudeStartTime;
                
                const float m_targetDistanceToInterest;
                Eegeo::Resources::Interiors::InteriorId m_interiorId;
                int m_targetFloorIndex;
                bool m_jumpIfFar;
                
                bool m_failed;
                bool m_initialisedNextInterior;
            };
        }
    }
}