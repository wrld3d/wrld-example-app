// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingCameraController.h"
#include "INavRoutingModel.h"
#include "ICameraTransitionController.h"
#include "NavigationService.h"
#include "NavRoutingRouteModel.h"
#include "CameraTransitionOptionsBuilder.h"
#include "InteriorsExplorer.h"
#include "ICompassModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRoutingCameraController::NavRoutingCameraController(INavRoutingModel& navRoutingModel,
                                                                   CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                   Eegeo::Location::NavigationService& navigationService,
                                                                   Compass::SdkModel::ICompassModel& compassModel)
            : m_navRoutingModel(navRoutingModel)
            , m_cameraTransitionController(cameraTransitionController)
            , m_navigationService(navigationService)
            , m_compassModel(compassModel)
            , m_routeSetCallback(this, &NavRoutingCameraController::OnRouteSet)
            , m_selectedDirectionSetCallback(this, &NavRoutingCameraController::OnSelectedDirectionSet)
            , m_navModeSetCallback(this, &NavRoutingCameraController::OnNavModeSet)
            , m_gpsModeChangedCallback(this, &NavRoutingCameraController::OnGpsModeChanged)
            {
                m_navRoutingModel.InsertRouteSetCallback(m_routeSetCallback);
                m_navRoutingModel.InsertSelectedDirectionSetCallback(m_selectedDirectionSetCallback);
                m_navRoutingModel.InsertNavModeSetCallback(m_navModeSetCallback);
                
                m_compassModel.InsertGpsModeChangedCallback(m_gpsModeChangedCallback);
            }
            
            NavRoutingCameraController::~NavRoutingCameraController()
            {
                m_compassModel.RemoveGpsModeChangedCallback(m_gpsModeChangedCallback);
                
                m_navRoutingModel.RemoveNavModeSetCallback(m_navModeSetCallback);
                m_navRoutingModel.RemoveSelectedDirectionSetCallback(m_selectedDirectionSetCallback);
                m_navRoutingModel.RemoveRouteSetCallback(m_routeSetCallback);
            }
            
            void NavRoutingCameraController::OnRouteSet(const NavRoutingRouteModel& routeModel)
            {
                UpdateCamera();
            }
            
            void NavRoutingCameraController::OnSelectedDirectionSet(const int& selectedDirection)
            {
                if(m_navRoutingModel.GetCurrentDirection() != selectedDirection || !m_navigationService.IsGPSActive())
                {
                    m_navigationService.SetGpsMode(Eegeo::Location::NavigationService::GpsModeOff);
                    UpdateCamera();
                }
            }
            
            void NavRoutingCameraController::OnNavModeSet(const NavRoutingMode& navMode)
            {
                if(navMode == NavRoutingMode::Active)
                {
                    m_cameraTransitionController.StopCurrentTransition();
                    m_navigationService.SetGpsMode(Eegeo::Location::NavigationService::GpsModeCompass);
                }
            }
            
            void NavRoutingCameraController::OnGpsModeChanged()
            {
                if(m_navRoutingModel.GetNavMode() == NavRoutingMode::Active &&
                   m_compassModel.GetGpsMode() != Compass::GpsMode::GpsDisabled)
                {
                    if(m_navRoutingModel.GetCurrentDirection() != m_navRoutingModel.GetSelectedDirection())
                    {
                        m_navRoutingModel.SetSelectedDirection(m_navRoutingModel.GetCurrentDirection());
                    }
                }
            }
            
            void NavRoutingCameraController::UpdateCamera()
            {
                SetCameraToSelectedDirection();
            }
            
            void NavRoutingCameraController::SetCameraToSelectedDirection()
            {
                SdkModel::NavRoutingRouteModel routeModel;
                bool hasRouteModel = m_navRoutingModel.TryGetRoute(routeModel);
                
                if(!hasRouteModel)
                {
                    return;
                }
                
                int selectedIndex = m_navRoutingModel.GetSelectedDirection();
                
                if(selectedIndex < 0 || selectedIndex >= routeModel.GetDirections().size())
                {
                    return;
                }
                
                const NavRoutingDirectionModel& selectedDirection = routeModel.GetDirections().at(selectedIndex);
                const Eegeo::Space::LatLong& location = selectedDirection.GetPath().back();
                
                CameraTransitions::SdkModel::CameraTransitionOptionsBuilder builder;
                builder.SetInterestPoint(location.ToECEF());
                if(selectedDirection.GetIsIndoors())
                {
                    int floorId = selectedDirection.GetIndoorMapFloorId();
                    
                    // NOTE: Multifloor directions have wrong floor ID so use next direction's instead
                    if(selectedDirection.GetIsMultiFloor() && selectedIndex < routeModel.GetDirections().size()-1)
                    {
                        const NavRoutingDirectionModel& nextDirection = routeModel.GetDirections().at(selectedIndex+1);
                        floorId = nextDirection.GetIndoorMapFloorId();
                    }
                    
                    builder.SetIndoorPosition(selectedDirection.GetIndoorMapId(), floorId);
                    builder.SetTargetFloorIndexIsFloorId(true);
                }
                builder.SetDistanceFromInterest(InteriorsExplorer::DefaultInteriorSearchResultTransitionInterestDistance);
                m_cameraTransitionController.StartTransition(builder.Build());
            }
        }
    }
}
