// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsNavigationService.h"
#include "GlobeCameraTouchController.h"
#include "ILocationService.h"
#include "InteriorsCameraController.h"
#include "InteriorHeightHelpers.h"
#include "CameraHelpers.h"
#include "EcefTangentBasis.h"
#include "GlobeCameraController.h"
#include "LatLongAltitude.h"
#include "InteriorInteractionModel.h"
#include "InteriorSelectionModel.h"
#include "InteriorsModel.h"
#include "InteriorsFloorModel.h"

namespace ExampleApp
{
    namespace InteriorsNavigation
    {
        namespace SdkModel
        {
            
            InteriorsNavigationService::InteriorsNavigationService(Eegeo::Location::ILocationService& locationService,
                                                                   Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                                                                   Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
                                                                   Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                   const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel)
            : m_locationService(locationService)
            , m_interiorsCameraController(interiorsCameraController)
            , m_cameraTouchController(cameraTouchController)
            , m_gpsMode(Eegeo::Location::NavigationService::GpsModeOff)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_interiorInteractionModel(interiorInteractionModel)
            , m_interiorSelectionModelChangedHandler(this, &InteriorsNavigationService::HandleInteriorSelectionModelChanged)
            {
                m_interiorSelectionModel.RegisterSelectionChangedCallback(m_interiorSelectionModelChangedHandler);
            }
            
            InteriorsNavigationService::~InteriorsNavigationService()
            {
                m_interiorSelectionModel.UnregisterSelectionChangedCallback(m_interiorSelectionModelChangedHandler);
            }
                
            void InteriorsNavigationService::SetGpsMode(Eegeo::Location::NavigationService::GpsMode mode)
            {
                m_gpsMode = mode;
                
                Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCam = m_interiorsCameraController.GetGlobeCameraController();
                Eegeo::Camera::GlobeCamera::GlobeCameraTouchSettings touchSettings = Eegeo::Camera::GlobeCamera::GlobeCameraTouchSettings::CreateDefault();
                
                touchSettings.PanEnabled = (m_gpsMode == Eegeo::Location::NavigationService::GpsModeOff);
                touchSettings.RotateEnabled = (m_gpsMode != Eegeo::Location::NavigationService::GpsModeCompass);

                globeCam.SetTouchSettings(touchSettings);
                
                ResetTargetLatLong();
            }
                
            Eegeo::Location::NavigationService::GpsMode InteriorsNavigationService::GetGpsMode() const
            {
                return m_gpsMode;
            }
                
            void InteriorsNavigationService::Update(float dt)
            {
                if(m_gpsMode == Eegeo::Location::NavigationService::GpsModeOff)
                {
                    return;
                }
                
                const float panThresholdSqrd = 100.0f;
                
                if(m_cameraTouchController.GetPanPixelDelta().Length() > panThresholdSqrd)
                {
                    SetGpsMode(Eegeo::Location::NavigationService::GpsModeOff);
                }
                
                double heading = m_interiorsCameraController.GetHeadingDegrees();
                const double rotationDampening = (double)Eegeo::Math::Clamp01(dt*3.0f);
                
                if(m_gpsMode == Eegeo::Location::NavigationService::GpsModeCompass)
                {
                    m_locationService.GetHeadingDegrees(m_targetHeading);
                    
                    if(m_targetHeading < m_currentHeading)
                    {
                        double offset = m_currentHeading - Eegeo::Math::Rad2Deg(Eegeo::Math::kPI*2.0f);
                        if(Eegeo::Math::Abs((float)(m_targetHeading-offset)) < m_currentHeading-m_targetHeading)
                        {
                            m_currentHeading = offset;
                        }
                    }
                    else
                    {
                        double offset = m_currentHeading + Eegeo::Math::Rad2Deg(Eegeo::Math::kPI*2.0f);
                        if(Eegeo::Math::Abs((float)(m_targetHeading-offset)) < m_targetHeading-m_currentHeading)
                        {
                            m_currentHeading = offset;
                        }
                    }
                    m_currentHeading = Eegeo::Math::Lerp(m_currentHeading, m_targetHeading, rotationDampening);
                    
                    heading = m_currentHeading;
                }
                
                
                Eegeo::Space::LatLong latLong = Eegeo::Space::LatLong(0.0f, 0.0f);
                
                if(m_locationService.GetLocation(latLong))
                {
                    m_currentLatitude = latLong.GetLatitudeInDegrees();
                    m_currentLongitude = latLong.GetLongitudeInDegrees();
                }
                
                const double positionDampening = (double)Eegeo::Math::Clamp01(dt*3.0f);
                
                m_targetLatitude = Eegeo::Math::Lerp(m_targetLatitude, m_currentLatitude, positionDampening);
                m_targetLongitude = Eegeo::Math::Lerp(m_targetLongitude, m_currentLongitude, positionDampening);
                
                float targetAltitude = 0.0f;
                
                if (m_interiorInteractionModel.HasInteriorModel())
                {
                    const Eegeo::Resources::Interiors::InteriorsModel& interiorModel = *m_interiorInteractionModel.GetInteriorModel();
                    targetAltitude = Helpers::InteriorHeightHelpers::GetFloorHeightAboveSeaLevel(interiorModel, m_interiorInteractionModel.GetSelectedFloorIndex());
                }
                
                m_interiorsCameraController.SetInterestLocation(Eegeo::Space::LatLongAltitude::FromDegrees(m_targetLatitude,
                                                                                                                   m_targetLongitude,
                                                                                                                   targetAltitude).ToECEF());
                m_interiorsCameraController.SetHeading(static_cast<float>(heading));
            }
            
            void InteriorsNavigationService::ResetTargetLatLong()
            {
                Eegeo::Space::LatLong latLong = Eegeo::Space::LatLong::FromDegrees(0.0, 0.0);
                
                if(m_locationService.GetLocation(latLong))
                {
                    m_currentHeading = m_interiorsCameraController.GetHeadingDegrees();
                    
                    m_currentLatitude = latLong.GetLatitudeInDegrees();
                    m_currentLongitude = latLong.GetLongitudeInDegrees();
                    
                    m_targetLatitude = latLong.GetLatitudeInDegrees();
                    m_targetLongitude = latLong.GetLongitudeInDegrees();
                }
            }
            
            bool InteriorsNavigationService::IsPositionInInterior()
            {
                Eegeo::Space::LatLong latLong = Eegeo::Space::LatLong(0.0f, 0.0f);
                
                
                if(m_locationService.GetLocation(latLong) && m_interiorInteractionModel.HasInteriorModel())
                {
                    const Eegeo::Resources::Interiors::InteriorsModel& interiorsModel = *m_interiorInteractionModel.GetInteriorModel();
                    const Eegeo::Geometry::Bounds3D& tangentBounds = interiorsModel.GetTangentSpaceBounds();
                    const Eegeo::dv3& boundsEcefOrigin = interiorsModel.GetTangentBasis().GetPointEcef();
                    float targetAltitude = Helpers::InteriorHeightHelpers::GetFloorHeightAboveSeaLevel(interiorsModel, m_interiorInteractionModel.GetSelectedFloorIndex());
                    
                    Eegeo::Geometry::SingleSphere toleranceSphere;
                    const Eegeo::v3 reletaivePoint = (Eegeo::Space::LatLongAltitude::FromRadians(latLong.GetLatitude(),
                                                                                                 latLong.GetLongitude(),
                                                                                                 targetAltitude).ToECEF() - boundsEcefOrigin).ToSingle();
                    
                    toleranceSphere.centre = Eegeo::v3::MulRotate(reletaivePoint, interiorsModel.GetTangentBasis().GetEcefToTangentTransform());
                    
                    toleranceSphere.radius = 10.0f;
                    
                    if(tangentBounds.intersectsSphere(toleranceSphere))
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            
            void InteriorsNavigationService::HandleInteriorSelectionModelChanged(const Eegeo::Resources::Interiors::InteriorId& prevId)
            {
                if (!m_interiorSelectionModel.IsInteriorSelected())
                {
                    SetGpsMode(Eegeo::Location::NavigationService::GpsModeOff);
                }
            }
        }
    }
}