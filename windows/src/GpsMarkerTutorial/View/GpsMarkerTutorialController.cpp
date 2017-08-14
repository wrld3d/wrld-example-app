// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "GpsMarkerTutorialController.h"
#include "GpsMarkerTutorialView.h"
#include "CompassGpsMode.h"
#include "TerrainHeightProvider.h"
#include "GpsMarkerModel.h"
#include "EnvironmentFlatteningService.h"
#include "InteriorsExplorerStateChangedMessage.h"

namespace ExampleApp
{
	namespace GpsMarkerTutorial
	{
		namespace View
		{
			GpsMarkerTutorialController::GpsMarkerTutorialController(GpsMarkerTutorialView& gpsMarkerTutorialView,
                                                                     ExampleAppMessaging::TMessageBus& messageBus,
                                                                     const GpsMarker::SdkModel::GpsMarkerModel& gpsMarkerModel,
                                                                     Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService)
				: m_gpsMarkerTutorialView(gpsMarkerTutorialView)
				, m_messageBus(messageBus)
				, m_gpsMarkerModel(gpsMarkerModel)
				, m_markerLocationEcef(Eegeo::dv3::Zero())
				, m_environmentFlatteningService(environmentFlatteningService)
				, m_currAppMode(AppModes::SdkModel::WorldMode)
				, m_shouldShowTutorial(false)
				, m_isInInterior(false)
				, m_oldCameraPosition(Eegeo::dv3::Zero())
				, m_cameraIsMoving(false)
				, m_oldGpsMode(ExampleApp::Compass::GpsMode::Values::GpsDisabled)
				, m_compassModeChangedHandler(this, &GpsMarkerTutorialController::OnCompassModeChangedMessage)
				, m_appModeChangedHandler(this, &GpsMarkerTutorialController::OnAppModeChangedMessage)
				, m_interiorStateChangedCallback(this, &GpsMarkerTutorialController::OnInteriorStateChanged)
			{
				m_messageBus.SubscribeUi(m_compassModeChangedHandler);
				m_messageBus.SubscribeUi(m_appModeChangedHandler);
				m_messageBus.SubscribeUi(m_interiorStateChangedCallback);
			}

			GpsMarkerTutorialController::~GpsMarkerTutorialController()
			{
				m_messageBus.UnsubscribeUi(m_interiorStateChangedCallback);
				m_messageBus.UnsubscribeUi(m_appModeChangedHandler);
				m_messageBus.UnsubscribeUi(m_compassModeChangedHandler);
			}

			void GpsMarkerTutorialController::UpdateScreenLocation(const Eegeo::Camera::RenderCamera& renderCamera,
                                                                   const float screenOversampleScale)
			{
				Eegeo::dv3 cameraPosition = renderCamera.GetEcefLocation();
				const double cameraMoveDistanceSq = (cameraPosition - m_oldCameraPosition).LengthSq();
				const double cameraMoveThreshold = 0.0001;

				if (!m_cameraIsMoving)
				{
					if(m_shouldShowTutorial && m_isInInterior && cameraMoveDistanceSq < cameraMoveThreshold)
					{
						m_shouldShowTutorial = false;
						m_gpsMarkerTutorialView.SetFullyOnScreen();
					}
				}
				else
				{
					const double fadeOutCameraMoveThreshold = 0.01;
					if(cameraMoveDistanceSq > fadeOutCameraMoveThreshold)
					{
						m_gpsMarkerTutorialView.SetFullyOffScreen();
					}
				}

				Eegeo::v3 cameraLocal = Eegeo::Camera::CameraHelpers::CameraRelativePoint(GetScaledMarkerPoint(), cameraPosition);
				Eegeo::v3 screenPos;
				renderCamera.Project(cameraLocal, screenPos);
				m_gpsMarkerTutorialView.UpdateScreenLocation(screenPos.GetX() / screenOversampleScale, screenPos.GetY() / screenOversampleScale);

				m_cameraIsMoving = cameraMoveDistanceSq > cameraMoveThreshold;

				m_oldCameraPosition = cameraPosition;
			}

			Eegeo::dv3 GpsMarkerTutorialController::GetScaledMarkerPoint()
			{
				Eegeo::dv3 newMarkerLocationEcef = m_gpsMarkerModel.GetCurrentLocationEcef();
				if(newMarkerLocationEcef.LengthSq() > 0)
				{
					m_markerLocationEcef = newMarkerLocationEcef;
				}

				float currentScale = m_environmentFlatteningService.GetCurrentScale();
				if(m_gpsMarkerModel.IsLocationIndoors())
				{
					currentScale = 1;
				}

				Eegeo::dv3 scaledPoint = m_environmentFlatteningService.GetScaledPointEcef(m_markerLocationEcef, currentScale);
				scaledPoint += scaledPoint.Norm() * m_gpsMarkerModel.GetSphereHeightAboveBase();
				return scaledPoint;
			}

			void GpsMarkerTutorialController::OnCompassModeChangedMessage(const ExampleApp::Compass::CompassModeChangedMessage& message)
			{
				switch (message.GetMode())
				{
				case ExampleApp::Compass::GpsMode::GpsFollow:
					if(m_oldGpsMode == ExampleApp::Compass::GpsMode::GpsDisabled)
					{
						m_cameraIsMoving = true;
						m_shouldShowTutorial = true;
					}
					break;
				case ExampleApp::Compass::GpsMode::GpsCompassMode:
					m_cameraIsMoving = true;
					m_shouldShowTutorial = true;
					break;
				case ExampleApp::Compass::GpsMode::GpsMode_Max:
					Eegeo_ASSERT(false, "Invalid gps mode");
					break;
				}
				
				m_oldGpsMode = message.GetMode();
			}

			void GpsMarkerTutorialController::OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message)
			{
				AppModes::SdkModel::AppMode newAppMode = message.GetAppMode();
				if (newAppMode == AppModes::SdkModel::AttractMode)
				{
					m_gpsMarkerTutorialView.SetFullyOffScreen();
				}
				else
				{
					if (m_currAppMode == AppModes::SdkModel::AttractMode)
					{
						m_cameraIsMoving = true;
						m_shouldShowTutorial = true;
					}
				}

				m_currAppMode = newAppMode;
			}

			void GpsMarkerTutorialController::OnInteriorStateChanged(const InteriorsExplorer::InteriorsExplorerStateChangedMessage& message)
			{
				m_isInInterior = message.IsInteriorVisible();
				if(m_isInInterior)
				{
					m_cameraIsMoving = true;
				}
			}
		}
	}
}