// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassModel.h"
#include "EnvironmentFlatteningService.h"
#include "GpsGlobeCameraController.h"
#include "CameraHelpers.h"
#include "RenderCamera.h"
#include "VectorMath.h"
#include "NavigationService.h"
#include "FlurryWrapper.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            CompassModel::CompassModel(Eegeo::Location::NavigationService& navigationService,
                                       Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& controller)
                :m_navigationService(navigationService)
                ,m_cameraController(controller)
            {
                m_compassGpsModeToNavigationGpsMode[Eegeo::Location::NavigationService::GpsModeOff] = GpsMode::GpsDisabled;
                m_compassGpsModeToNavigationGpsMode[Eegeo::Location::NavigationService::GpsModeFollow] = GpsMode::GpsFollow;
                m_compassGpsModeToNavigationGpsMode[Eegeo::Location::NavigationService::GpsModeCompass] = GpsMode::GpsCompassMode;

                m_navigationGpsModeToCompassGpsMode[GpsMode::GpsDisabled] = Eegeo::Location::NavigationService::GpsModeOff;
                m_navigationGpsModeToCompassGpsMode[GpsMode::GpsFollow] = Eegeo::Location::NavigationService::GpsModeFollow;
                m_navigationGpsModeToCompassGpsMode[GpsMode::GpsCompassMode] = Eegeo::Location::NavigationService::GpsModeCompass;
                
                m_gpsModeToString[GpsMode::GpsDisabled] = "GpsDisabled";
                m_gpsModeToString[GpsMode::GpsFollow] = "GpsFollow";
                m_gpsModeToString[GpsMode::GpsCompassMode] = "GpsCompassMode";
            }

            CompassModel::~CompassModel()
            {

            }

            bool CompassModel::GetGpsModeActive() const
            {
                return GetGpsMode() != GpsMode::GpsDisabled;
            }

            GpsMode::Values CompassModel::GetGpsMode() const
            {
                return m_gpsMode;
            }

            void CompassModel::CycleToNextGpsMode()
            {
                int gpsMode = static_cast<int>(m_gpsMode);
                gpsMode = (gpsMode + 1) % static_cast<int>(GpsMode::GpsMode_Max);
                GpsMode::Values newGpsMode = static_cast<GpsMode::Values>(gpsMode);

                if(GetGpsModeActive() && newGpsMode == GpsMode::GpsDisabled)
                {
                    m_gpsMode = newGpsMode;
                    CycleToNextGpsMode();
                }
                else
                {
                    SetGpsMode(newGpsMode);
                }
            }

            void CompassModel::TryUpdateToNavigationServiceGpsMode(Eegeo::Location::NavigationService::GpsMode value)
            {
                GpsMode::Values gpsModeValueFromNavigationService = m_compassGpsModeToNavigationGpsMode[value];

                if(gpsModeValueFromNavigationService != GetGpsMode())
                {
                    SetGpsMode(gpsModeValueFromNavigationService);
                }
            }

            void CompassModel::DisableGpsMode()
            {
                SetGpsMode(GpsMode::GpsDisabled);
            }

            void CompassModel::SetGpsMode(GpsMode::Values gpsMode)
            {
                m_gpsMode = gpsMode;
                m_navigationService.SetGpsMode(m_navigationGpsModeToCompassGpsMode[gpsMode]);
                
                FLURRY_SET_EVENT("SetGpsMode", "GpsMode", m_gpsModeToString[m_gpsMode]);
            
                m_gpsModeChangedCallbacks.ExecuteCallbacks();
            }

            float CompassModel::GetHeadingRadians() const
            {
                const Eegeo::Camera::RenderCamera renderCamera = m_cameraController.GetRenderCamera();
                const Eegeo::m44& cameraModelMatrix = renderCamera.GetModelMatrix();

                const Eegeo::v3& viewDirection = cameraModelMatrix.GetRow(2);

                Eegeo::v3 ecefUp = renderCamera.GetEcefLocation().ToSingle().Norm();
                const float epsilon = 0.001f;
                Eegeo::v3 heading;
                if (Eegeo::Math::Abs(Eegeo::v3::Dot(viewDirection, ecefUp)) > (1.f - epsilon))
                {
                    const Eegeo::v3& viewUp = cameraModelMatrix.GetRow(1);
                    heading = viewUp;
                }
                else
                {
                    heading = viewDirection;
                }

                return Eegeo::Camera::CameraHelpers::GetAbsoluteBearingRadians(renderCamera.GetEcefLocation(), heading);
            }

            float CompassModel::GetHeadingDegrees() const
            {
                float headingRadians = GetHeadingRadians();
                return Eegeo::Math::Rad2Deg(headingRadians);
            }

            void CompassModel::InsertGpsModeChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_gpsModeChangedCallbacks.AddCallback(callback);
            }

            void CompassModel::RemoveGpsModeChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_gpsModeChangedCallbacks.RemoveCallback(callback);
            }
        }
    }
}
