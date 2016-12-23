// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "CameraTransitionService.h"
#include "CompassModeObserver.h"
#include "CoordinateConversion.h"
#include "FixedIndoorLocationCompassModeObserver.h"
#include "InteriorsCameraController.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            FixedIndoorLocationCompassModeObserver::FixedIndoorLocationCompassModeObserver(
                ICompassModel& model,
                ExampleAppMessaging::TMessageBus& messageBus,
                CameraTransitions::SdkModel::CameraTransitionService& cameraTransitionService,
                Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                const Eegeo::Space::LatLong latlong,
                const Eegeo::Resources::Interiors::InteriorId& interiorId,
                const int floorIndex,
                const double fixedHeadingRadians)
                : CompassModeObserver(model, messageBus)
                , m_cameraTransitionService(cameraTransitionService)
                , m_interiorsCameraController(interiorsCameraController)
                , m_location(Eegeo::Space::ConvertLatLongAltitudeToEcef(latlong.GetLatitude(), latlong.GetLongitude(), 0.0))
                , m_interiorId(interiorId)
                , m_floorIndex(floorIndex)
                , m_fixedHeadingRadians(fixedHeadingRadians)
            {
            }

            void FixedIndoorLocationCompassModeObserver::OnGpsModeChanged()
            {
                const GpsMode::Values gpsMode = m_model.GetGpsMode();
                if (gpsMode == GpsMode::GpsFollow || gpsMode == GpsMode::GpsCompassMode)
                {
                    m_cameraTransitionService.StartTransitionTo(m_location, m_interiorsCameraController.GetDistanceToInterest(), m_fixedHeadingRadians, m_interiorId, m_floorIndex);
                }
                CompassModeObserver::OnGpsModeChanged();
            }
        }
    }
}
