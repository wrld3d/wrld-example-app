// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPinCreation.h"
#include "IPoiRingController.h"
#include "AppInterface.h"
#include "Camera.h"
#include "Terrain.h"
#include "EnvironmentFlatteningService.h"
#include "VectorMathDecl.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            class PoiRingController : public IPoiRingController
            {
            public:
                PoiRingController(IMyPinCreationModel& myPinCreationModel,
                                  PoiRingView& poiRingView,
                                  Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                  Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider);
            
                void Update(float dt, const Eegeo::Camera::RenderCamera& renderCamera, const Eegeo::dv3& cameraEcefInterestPoint);
                
                void GetIconPositionAndSize(Eegeo::dv3& out_positionEcef, float& out_sizeMeters) const;
                
            private:
                Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
                Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& m_terrainHeightProvider;
                
                IMyPinCreationModel& m_pMyPinCreationModel;
                
                PoiRingView& m_poiRingView;
                
                float m_scaleInterpolationParam;
                float m_easeDurationInSeconds;
                Eegeo::dv3 m_iconPosition;
                float m_iconSize;
                
                Eegeo::v3 CalculateQuadScreenSpaceTranslation(const Eegeo::Camera::RenderCamera& renderCamera) const;
                float CalculateTransitionScale(float dt);
            };
        }
    }
}