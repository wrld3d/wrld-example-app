// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppCameraLocationPicker.h"
#include "CameraHelpers.h"
#include "RenderCamera.h"
#include "IAppCameraController.h"
#include "Ray.h"
#include "InteriorTransitionModel.h"
#include "CollisionGroup.h"
#include "IFeatureRayCastingService.h"
#include "InteriorInteractionModel.h"
#include "InteriorsModel.h"
#include "InteriorsFloorModel.h"
#include "InteriorHeightHelpers.h"
#include "EarthConstants.h"
#include "IntersectionTests.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {

            AppCameraLocationPicker::AppCameraLocationPicker(
                    AppCamera::SdkModel::IAppCameraController& cameraController,
                    Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                    Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                    Eegeo::Collision::IFeatureRayCastingService& featureRayCastingService)
            : m_cameraController(cameraController)
            , m_interiorTransitionModel(interiorTransitionModel)
            , m_interiorInteractionModel(interiorInteractionModel)
            , m_featureRayCastingService(featureRayCastingService)
            {
            }

            AppCameraLocationPicker::~AppCameraLocationPicker()
            {

            }

            AppCameraLocationPickerResult AppCameraLocationPicker::PickLocation(float screenX, float screenY)
            {
                const Eegeo::Camera::RenderCamera& camera = m_cameraController.GetRenderCamera();
                Eegeo::v2 screenPoint(screenX, screenY);
                Eegeo::v2 screenDimensions(camera.GetViewportWidth(), camera.GetViewportHeight());

                Eegeo::Geometry::Ray screenRay = Eegeo::Camera::CameraHelpers::ScreenPointToRay(screenPoint,
                                                                                                screenDimensions,
                                                                                                camera.GetInverseViewProjectionMatrix(),
                                                                                                m_cameraController.GetNonFlattenedCameraPosition());

                if(m_interiorInteractionModel.HasInteriorModel() && m_interiorTransitionModel.InteriorIsVisible())
                {
                    return RayPickInInterior(screenRay);
                }
                else
                {
                    return RayPickInExterior(screenRay);
                }

            }

            AppCameraLocationPickerResult AppCameraLocationPicker::RayPickInInterior(const Eegeo::Geometry::Ray& ray)
            {
                const Eegeo::Resources::Interiors::InteriorsModel* interiorsModel = m_interiorInteractionModel.GetInteriorModel();

                Eegeo_ASSERT(interiorsModel, "Couldn't get current interiorsModel");

                const Eegeo::dv3 originNormal = interiorsModel->GetTangentBasis().GetUp();

                const int selectedFloorIndex = m_interiorInteractionModel.GetSelectedFloorIndex();

                float floorHeightAboveSeaLevel = interiorsModel->GetFloorAltitude(selectedFloorIndex);

                const Eegeo::dv3 point = originNormal * (floorHeightAboveSeaLevel + Eegeo::Space::EarthConstants::Radius);

                double intersectionParam = 0;
                Eegeo::dv3 intersectionPoint = Eegeo::dv3::Zero();
                bool didIntersect = Eegeo::Geometry::IntersectionTests::RayIntersectsWithPlane(ray.GetOrigin(),
                                                                                               ray.GetDirection(),
                                                                                               originNormal,
                                                                                               point,
                                                                                               intersectionParam,
                                                                                               intersectionPoint);
                bool isIndoors = true;
                return AppCameraLocationPickerResult(didIntersect,
                                                     Eegeo::Space::LatLong::FromECEF(intersectionPoint),
                                                     isIndoors,
                                                     m_interiorInteractionModel.GetInteriorModel()->GetId(),
                                                     m_interiorInteractionModel.GetSelectedFloorModel()->GetFloorNumber());
            }

            AppCameraLocationPickerResult AppCameraLocationPicker::RayPickInExterior(const Eegeo::Geometry::Ray& ray)
            {
                u32 collisionMask = Eegeo::Collision::CollisionGroup::CollideAll;

                const auto& featureRayCastResult = m_featureRayCastingService.FindFirstRayIntersection(ray, collisionMask);

                bool isIndoors = false;
                return AppCameraLocationPickerResult(featureRayCastResult.DidIntersect(),
                                                     Eegeo::Space::LatLong::FromECEF(featureRayCastResult.GetIntersectionPointEcef()),
                                                     isIndoors,
                                                     Eegeo::Resources::Interiors::InteriorId::NullId(),
                                                     -1);


            }


        }
    }
}