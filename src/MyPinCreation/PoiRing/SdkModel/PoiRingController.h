// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPinCreation.h"
#include "Interiors.h"
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
            namespace SdkModel
            {
                class PoiRingController : public IPoiRingController
                {
                public:
                    PoiRingController(MyPinCreation::SdkModel::IMyPinCreationModel& myPinCreationModel,
                                      PoiRingView& poiRingView,
                                      Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                      Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                                      Eegeo::Resources::Interiors::InteriorController& interiorController);

                    void Update(float dt, const Eegeo::Camera::RenderCamera& renderCamera, const Eegeo::dv3& cameraEcefInterestPoint);

                    void GetIconPositionAndSize(Eegeo::dv3& out_positionEcef, float& out_sizeMeters) const;
                    void GetSpherePositionAndRadius(Eegeo::dv3& out_sphereCenterEcef, float& out_sphereRadius) const;

                private:
                    Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
                    Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& m_terrainHeightProvider;
                    Eegeo::Resources::Interiors::InteriorController& m_interiorController;

                    MyPinCreation::SdkModel::IMyPinCreationModel& m_myPinCreationModel;

                    PoiRingView& m_poiRingView;

                    float m_scaleInterpolationParam;
                    float m_easeDurationInSeconds;
                    Eegeo::dv3 m_iconPosition;
                    float m_iconSize;
                    float m_ringRadius;

                    Eegeo::v3 CalculateQuadScreenSpaceTranslation(const Eegeo::Camera::RenderCamera& renderCamera) const;
                    float CalculateTransitionScale(float dt);
                };
            }
        }
    }
}
