// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "ICameraTransitionController.h"
#include "GlobeCamera.h"
#include "Location.h"
#include "VectorMath.h"
#include "Terrain.h"

namespace ExampleApp
{
	namespace CameraTransitions
	{
		class CameraTransitionController : public ICameraTransitionController
		{
		public:

			CameraTransitionController(Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& cameraController,
			                           Eegeo::Location::NavigationService& navigationService,
                                       Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider);

			void StartTransitionTo(Eegeo::dv3 newInterestPoint, float distanceFromInterest, bool jumpIfFar=true);
			void StartTransitionTo(Eegeo::dv3 newInterestPoint, float distanceFromInterest, float newHeadingRadians, bool jumpIfFar=true);
			void StopCurrentTransition();
			void Update(float dt);

			const bool IsTransitioning() const
			{
				return m_isTransitioning;
			}

		private:

			bool ShouldJumpTo(Eegeo::dv3& newInterestPoint);

			Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_cameraController;
			Eegeo::Location::NavigationService& m_navigationService;
            Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& m_terrainHeightProvider;
			Eegeo::dv3 m_startTransitionInterestPointEcef;
			Eegeo::dv3 m_endTransitionInterestPointEcef;
			float m_startInterestDistance;
			float m_endInterestDistance;
			float m_startInterestHeading;
			float m_endInterestHeading;
			float m_transitionTime;
			float m_transitionDuration;
			bool m_isTransitioning;
		};
	}
}
