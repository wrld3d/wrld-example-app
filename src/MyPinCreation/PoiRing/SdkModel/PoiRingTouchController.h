// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPinCreation.h"
#include "IPoiRingTouchController.h"
#include "AppInterface.h"
#include "IRayPicker.h"
#include "Camera.h"
#include "GpsGlobeCameraController.h"
#include "VectorMathDecl.h"
#include "AppModes.h"
#include "Interiors.h"
#include "Types.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            namespace SdkModel
            {
                class PoiRingTouchController : public IPoiRingTouchController, private Eegeo::NonCopyable
                {
                public:
                    PoiRingTouchController(const std::shared_ptr<MyPinCreation::SdkModel::IMyPinCreationModel>& myPinCreationModel,
                                           const std::shared_ptr<Eegeo::Collision::IRayPicker>& rayPicker,
                                           const std::shared_ptr<const IPoiRingController>& poiRingController,
                                           const std::shared_ptr<ExampleApp::AppModes::SdkModel::IAppModeModel>& appModeModel,
                                           const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel>& interiorInteractionModel,
                                           const std::shared_ptr<Eegeo::Resources::Interiors::InteriorTransitionModel>& interiorTransitionModel);

                    bool HandleTouchDown(const AppInterface::TouchData& data, const Eegeo::Camera::RenderCamera& renderCamera, const Eegeo::dv3& nonFlattenedCameraPosition);
                    bool HandleTouchUp(const AppInterface::TouchData& data);
                    bool HandleTouchMove(const AppInterface::TouchData& data, const Eegeo::Camera::RenderCamera& renderCamera, const Eegeo::dv3& nonFlattenedCameraPosition);

                    bool IsDragging() const;

                private:
                    
                    bool TouchDownRaycast(const AppInterface::TouchData &data,
                                          const Eegeo::Camera::RenderCamera &renderCamera,
                                          const Eegeo::dv3 &rayOrigin);
                    
                    bool TouchMoveRaycast(const AppInterface::TouchData &data,
                                          const Eegeo::Camera::RenderCamera &renderCamera,
                                          const Eegeo::dv3 &rayOrigin);
                    
                    
                    
                    const std::shared_ptr<MyPinCreation::SdkModel::IMyPinCreationModel> m_myPinCreationModel;
                    const std::shared_ptr<Eegeo::Collision::IRayPicker> m_rayPicker;
                    const std::shared_ptr<const IPoiRingController> m_poiRingController;
                    
                    const std::shared_ptr<ExampleApp::AppModes::SdkModel::IAppModeModel> m_appModeModel;
                    const std::shared_ptr<const Eegeo::Resources::Interiors::InteriorInteractionModel> m_interiorInteractionModel;
                    const std::shared_ptr<const Eegeo::Resources::Interiors::InteriorTransitionModel> m_interiorTransitionModel;

                    bool m_isDragging;
                    Eegeo::dv3 m_dragOffset;
                    
                    float m_initialCameraAltitiude;

                    bool PerformRayPick(const Eegeo::dv3& rayOrigin,
                                        Eegeo::dv3& rayDirection,
                                        Eegeo::dv3& out_rayIntersectionPoint,
                                        double& out_intersectionParam,
                                        float& out_terrainHeight,
                                        float& out_heightAboveTerrain);
                };
            }
        }
    }
}
