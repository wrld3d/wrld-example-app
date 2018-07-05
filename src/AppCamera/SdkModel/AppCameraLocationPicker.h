// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IAppCameraLocationPicker.h"
#include "LatLongAltitude.h"
#include "AppCamera.h"
#include "Interiors.h"
#include "Terrain.h"
#include "VectorMathDecl.h"
#include "LatLongAltitude.h"
#include "Collision.h"
#include "InteriorId.h"
#include "Geometry.h"
#include <string>

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            struct AppCameraLocationPickerResult
            {
            public:

                AppCameraLocationPickerResult()
                : m_validResult(false)
                , m_location(0,0)
                , m_isIndoors(false)
                , m_indoorId(Eegeo::Resources::Interiors::InteriorId::NullId())
                , m_indoorFloorNumber(-1)
                {
                }

                AppCameraLocationPickerResult(bool validResult,
                    const Eegeo::Space::LatLong& location,
                    bool isIndoors,
                    const Eegeo::Resources::Interiors::InteriorId& indoorId,
                    int indoorFloorNumber)
                : m_validResult(validResult)
                , m_location(location)
                , m_isIndoors(isIndoors)
                , m_indoorId(indoorId)
                , m_indoorFloorNumber(indoorFloorNumber)
                {

                }

                bool IsValidResult() const { return m_validResult; }
                const Eegeo::Space::LatLong& GetLocation() const { return m_location; }
                bool IsIndoors() const { return m_isIndoors; }
                const Eegeo::Resources::Interiors::InteriorId& GetIndoorId() const { return m_indoorId; }
                int GetIndoorFloorNumber() const { return m_indoorFloorNumber; }

            private:
                Eegeo::Space::LatLong m_location;
                Eegeo::Resources::Interiors::InteriorId m_indoorId;
                int m_indoorFloorNumber;
                bool m_validResult;
                bool m_isIndoors;

            };

            class AppCameraLocationPicker : public IAppCameraLocationPicker
            {
            public:
                AppCameraLocationPicker( AppCamera::SdkModel::IAppCameraController& cameraController,
                                         Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                         Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                         Eegeo::Collision::IFeatureRayCastingService& featureRayCastingService);
                ~AppCameraLocationPicker();

                AppCameraLocationPickerResult PickLocation(float screenX, float screenY);

            private:

                AppCameraLocationPickerResult RayPickInInterior(const Eegeo::Geometry::Ray& ray);
                AppCameraLocationPickerResult RayPickInExterior(const Eegeo::Geometry::Ray& ray);

                AppCamera::SdkModel::IAppCameraController& m_cameraController;
                Eegeo::Resources::Interiors::InteriorTransitionModel& m_interiorTransitionModel;
                Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                Eegeo::Collision::IFeatureRayCastingService& m_featureRayCastingService;
            };
        }
    }
}