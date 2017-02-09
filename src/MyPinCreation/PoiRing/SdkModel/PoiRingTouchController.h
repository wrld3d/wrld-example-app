// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IPoiRingTouchController.h"
#include "Types.h"
#include "MyPinCreation.h"
#include "AppInterface.h"
#include "IRayPicker.h"
#include "Camera.h"
#include "GpsGlobeCameraController.h"
#include "VectorMathDecl.h"
#include "AppModes.h"
#include "Interiors.h"

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
                    PoiRingTouchController(MyPinCreation::SdkModel::IMyPinCreationModel& myPinCreationModel,
                                           Eegeo::Collision::IRayPicker& rayPicker,
                                           const IPoiRingController& poiRingController,
                                           ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                           const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                           const Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel);

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
                    
                    
                    MyPinCreation::SdkModel::IMyPinCreationModel& m_myPinCreationModel;
                    Eegeo::Collision::IRayPicker& m_rayPicker;
                    const IPoiRingController& m_poiRingController;
                    
                    ExampleApp::AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                    const Eegeo::Resources::Interiors::InteriorTransitionModel& m_interiorTransitionModel;

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
