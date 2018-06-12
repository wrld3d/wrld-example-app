// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "ILocationService.h"
#include "VectorMath.h"
#include "BlueSphereModel.h"
#include "Interiors.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class GpsMarkerModel
            {
            public:
                GpsMarkerModel(Eegeo::Location::ILocationService& locationService,
                               Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                               Eegeo::BlueSphere::BlueSphereModel& blueSphereModel);
                ~GpsMarkerModel();

                bool UpdateGpsPosition(float dt);

                const Eegeo::dv3& GetCurrentLocationEcef() const { return m_currentLocationEcef; }

                void UpdateHeading(float dt);

                void SetEnabled(bool enabled);

                void SetAccuracyRingEnabled(bool enabled);

                bool IsAccuracyRingEnabled() const;

                const float GetSphereHeightAboveBase() const;

                const double GetAccuracy() const { return m_currentAccuracyMeters; }

                bool IsLocationIndoors() const;

            private:
                Eegeo::Location::ILocationService& m_locationService;
                Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                Eegeo::BlueSphere::BlueSphereModel& m_blueSphereModel;

                Eegeo::dv3 m_currentLocationEcef;

                double m_currentAccuracyMeters;
                float m_currentHeadingRadians;
                float m_currentHeadingVelocity;
                bool m_accuracyRingEnabled;

                bool TryGetLocationServiceIndoorMapFloorId(const Eegeo::Resources::Interiors::InteriorId& locationServiceInteriorId, int& out_indoorMapFloorId) const;
                bool TryGetFloorIdFromIndex(int floorIndex, int& out_indoorMapFloorId) const;

            };
        }
    }
}
