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
#include "Rendering.h"
#include "PlatformConfig.h"

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
                    PoiRingController(const std::shared_ptr<MyPinCreation::SdkModel::IMyPinCreationModel>& myPinCreationModel,
                                      const std::shared_ptr<PoiRingView>& poiRingView,
                                      const std::shared_ptr<Eegeo::Rendering::EnvironmentFlatteningService>& environmentFlatteningService,
                                      const std::shared_ptr<Eegeo::Resources::Terrain::Heights::TerrainHeightProvider>& terrainHeightProvider,
                                      const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel>& interiorInteractionModel,
                                      const std::shared_ptr<Eegeo::Resources::Interiors::InteriorTransitionModel>& interiorTransitionModel,
                                      const std::shared_ptr<Eegeo::Rendering::ScreenProperties>& screenProperties,
                                      const std::shared_ptr<Eegeo::Config::PlatformConfig>& platformConfig);

                    void Update(float dt, const Eegeo::Camera::RenderCamera& renderCamera, const Eegeo::dv3& cameraEcefInterestPoint);

                    void GetIconPositionAndSize(Eegeo::dv3& out_positionEcef, float& out_sizeMeters) const;
                    void GetSpherePositionAndRadius(Eegeo::dv3& out_sphereCenterEcef, float& out_sphereRadius) const;

                private:
                    const std::shared_ptr<Eegeo::Rendering::EnvironmentFlatteningService> m_environmentFlatteningService;
                    const std::shared_ptr<Eegeo::Resources::Terrain::Heights::TerrainHeightProvider> m_terrainHeightProvider;
                    const std::shared_ptr<const Eegeo::Resources::Interiors::InteriorInteractionModel> m_interiorInteractionModel;
                    const std::shared_ptr<const Eegeo::Resources::Interiors::InteriorTransitionModel> m_interiorTransitionModel;
                    const std::shared_ptr<MyPinCreation::SdkModel::IMyPinCreationModel> m_myPinCreationModel;
                    const std::shared_ptr<Eegeo::Rendering::ScreenProperties> m_screenProperties;
                    const std::shared_ptr<PoiRingView> m_poiRingView;

                    float m_scaleInterpolationParam;
                    float m_easeDurationInSeconds;
                    Eegeo::dv3 m_iconPosition;
                    float m_iconSize;
                    float m_ringRadius;
                    const bool m_interiorsAffectedByFlattening;

                    Eegeo::v3 CalculateQuadScreenSpaceTranslation(const Eegeo::Camera::RenderCamera& renderCamera) const;
                    float CalculateTransitionScale(float dt);
                };
            }
        }
    }
}
