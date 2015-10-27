// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsNavigationService.h"
#include "GlobeCameraTouchController.h"
#include "ILocationService.h"
#include "InteriorsExplorerCameraController.h"
#include "InteriorHeightHelpers.h"
#include "CameraHelpers.h"
#include "EcefTangentBasis.h"
#include "GlobeCameraController.h"
#include "LatLongAltitude.h"
#include "InteriorController.h"

namespace ExampleApp
{
    namespace InteriorsNavigation
    {
        namespace SdkModel
        {
            
            InteriorsNavigationService::InteriorsNavigationService(Eegeo::Location::ILocationService& locationService,
                                                                   InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& interiorsExplorerCameraController,
                                                                   Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
                                                                   Eegeo::Resources::Interiors::InteriorController& interiorController)
            : m_locationService(locationService)
            , m_interiorsExplorerCameraController(interiorsExplorerCameraController)
            , m_cameraTouchController(cameraTouchController)
            , m_gpsMode(Eegeo::Location::NavigationService::GpsModeOff)
            , m_interiorController(interiorController)
            {
                
            }
            
            InteriorsNavigationService::~InteriorsNavigationService()
            {
                
            }
                
            void InteriorsNavigationService::SetGpsMode(Eegeo::Location::NavigationService::GpsMode mode)
            {
                m_gpsMode = mode;
                
                if(m_gpsMode != Eegeo::Location::NavigationService::GpsModeOff)
                {
                    m_interiorsExplorerCameraController.SetPanEnabled(false);
                }
                else
                {
                    m_interiorsExplorerCameraController.SetPanEnabled(true);
                }
                
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
                
                double heading = m_interiorsExplorerCameraController.GetHeadingDegrees();
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
                
                const Eegeo::Resources::Interiors::InteriorsModel* pInteriorsModel;
                float targetAltitude = 0.0f;
                
                if(m_interiorController.TryGetCurrentModel(pInteriorsModel))
                {
                    targetAltitude = Helpers::InteriorHeightHelpers::GetFloorHeightAboveSeaLevel(*pInteriorsModel, m_interiorController.GetCurrentFloorIndex());
                }
                
                m_interiorsExplorerCameraController.SetInterestLocation(Eegeo::Space::LatLongAltitude::FromDegrees(m_targetLatitude,
                                                                                                                   m_targetLongitude,
                                                                                                                   targetAltitude).ToECEF());
                m_interiorsExplorerCameraController.SetHeading(static_cast<float>(heading));
            }
            
            void InteriorsNavigationService::ResetTargetLatLong()
            {
                Eegeo::Space::LatLong latLong = Eegeo::Space::LatLong::FromDegrees(0.0, 0.0);
                
                if(m_locationService.GetLocation(latLong))
                {
                    const Eegeo::Space::EcefTangentBasis& cameraInterestBasis =  m_interiorsExplorerCameraController.GetGlobeCameraController().GetInterestBasis();
                    m_currentHeading = Eegeo::Camera::CameraHelpers::GetAbsoluteBearingRadians(cameraInterestBasis.GetPointEcef(),
                                                                                               cameraInterestBasis.GetForward());
                    
                    m_currentLatitude = latLong.GetLatitudeInDegrees();
                    m_currentLongitude = latLong.GetLongitudeInDegrees();
                    
                    m_targetLatitude = latLong.GetLatitudeInDegrees();
                    m_targetLongitude = latLong.GetLongitudeInDegrees();
                }
            }
        }
    }
}