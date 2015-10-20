// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICameraTransitionStage.h"
#include "VectorMath.h"
#include "GlobeCamera.h"
#include "GpsGlobeCameraController.h"
#include "Terrain.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            class TransitionToWorldPointStage : public ICameraTransitionStage
            {
            public:
                
                TransitionToWorldPointStage(Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& gpsGlobeCameraController,
                                            Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                                            const Eegeo::dv3& newInterestPoint,
                                            float distanceFromInterest,
                                            float newHeadingRadians,
                                            bool jumpIfFar=true);
                
                void Start();
                void Update(float dt);
                void End();
                
                const bool StageIsComplete() const;
                const bool StageHasFailed() const;
                
            private:
                
                bool ShouldJumpTo(Eegeo::dv3& newInterestPoint);
                
                Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_gpsGlobeCameraController;
                Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& m_terrainHeightProvider;
                
                Eegeo::dv3 m_startTransitionInterestPointEcef;
                Eegeo::dv3 m_endTransitionInterestPointEcef;
                float m_startInterestDistance;
                float m_endInterestDistance;
                float m_startInterestHeading;
                float m_endInterestHeading;
                float m_transitionTime;
                float m_transitionDuration;
                const bool m_jumpIfFar;
            };
        }
    }
}