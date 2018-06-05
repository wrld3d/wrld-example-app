//
// Created by malcolm.brown on 31/05/2018.
//

#include <platform/Rendering/Colors.h>
#include "NavTurnByTurnLocationService.h"
#include "INavTurnByTurnModel.h"
#include "ILocationService.h"
#include "INavRoutingModel.h"
#include "DebugRenderer.h"
#include "InteriorsModelRepository.h"
#include "InteriorsModel.h"
#include "InteriorHelpers.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            namespace TurnByTurn
            {
                NavTurnByTurnLocationService::NavTurnByTurnLocationService(
                        INavTurnByTurnModel& turnByTurnModel,
                        INavRoutingModel& navRoutingModel,
                        Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                        Eegeo::DebugRendering::DebugRenderer& debugRenderer)
                : m_pInternalLocationService(NULL)
                , m_turnByTurnModel(turnByTurnModel)
                , m_navRoutingModel(navRoutingModel)
                , m_interiorsModelRepository(interiorsModelRepository)
                , m_debugRenderer(debugRenderer)
                , m_turnByTurnStartedCallback(this, &NavTurnByTurnLocationService::OnTurnByTurnStarted)
                , m_turnByTurnEndedCallback(this, &NavTurnByTurnLocationService::OnTurnByTurnEnded)
                , m_turnByTurnUpdatedCallback(this, &NavTurnByTurnLocationService::OnTurnByTurnUpdated)
                , m_followingRoute(false)
                , m_debugRenderingEnabled(true)
                {
                    m_turnByTurnModel.InsertStartedCallback(m_turnByTurnStartedCallback);
                    m_turnByTurnModel.InsertStoppedCallback(m_turnByTurnEndedCallback);
                    m_turnByTurnModel.InsertUpdatedCallback(m_turnByTurnUpdatedCallback);
                }

                NavTurnByTurnLocationService::~NavTurnByTurnLocationService()
                {
                    m_turnByTurnModel.RemoveUpdatedCallback(m_turnByTurnUpdatedCallback);
                    m_turnByTurnModel.RemoveStoppedCallback(m_turnByTurnEndedCallback);
                    m_turnByTurnModel.RemoveStartedCallback(m_turnByTurnStartedCallback);
                }

                void NavTurnByTurnLocationService::OnTurnByTurnStarted()
                {
                    m_followingRoute = true;
                    m_targetHeading = m_turnByTurnModel.GetPathHeadingDegrees();
                    m_currentHeading = m_turnByTurnModel.GetPathHeadingDegrees();
                    Eegeo_TTY("WTF: Route GO!");
                }

                void NavTurnByTurnLocationService::OnTurnByTurnEnded()
                {
                    m_followingRoute = false;
                    Eegeo_TTY("WTF: Route STOP!");
                }

                void NavTurnByTurnLocationService::OnTurnByTurnUpdated()
                {
                    Eegeo_TTY("WTF: Route UPDAT");
                    m_targetHeading = m_turnByTurnModel.GetPathHeadingDegrees();
                    // Refresh averaged coordinates/headings and such.

                    DrawLocation(Eegeo::Rendering::Colors::YELLOW, 1.0f);
                }

                void NavTurnByTurnLocationService::SetLocationService(Eegeo::Location::ILocationService& internalLocationService)
                {
                    Eegeo_TTY("WTF: LOCATION SERVICE CHANGE");
                    m_pInternalLocationService = &internalLocationService;
                }

                const Eegeo::Routes::Webservice::RouteStep& NavTurnByTurnLocationService::GetCurrentRouteStep()
                {
                    NavRoutingRouteModel navRoutingModel;
                    Eegeo_ASSERT(m_navRoutingModel.TryGetRoute(navRoutingModel))

                    const Eegeo::Routes::Webservice::RouteData& routeData = navRoutingModel.GetSourceRouteData();
                    const Eegeo::Routes::Webservice::RouteSection& routeSection = routeData.Sections.at(
                            static_cast<unsigned int>(m_turnByTurnModel.GetCurrentSectionIndex()));
                    const Eegeo::Routes::Webservice::RouteStep& routeStep = routeSection.Steps.at(
                            static_cast<unsigned int>(m_turnByTurnModel.GetCurrentStepIndex()));

                    return routeStep;
                }

                const Eegeo::Routes::Webservice::RouteStep& NavTurnByTurnLocationService::GetNextRouteStep()
                {
                    NavRoutingRouteModel navRoutingModel;
                    Eegeo_ASSERT(m_navRoutingModel.TryGetRoute(navRoutingModel))

                    const Eegeo::Routes::Webservice::RouteData& routeData = navRoutingModel.GetSourceRouteData();
                    const Eegeo::Routes::Webservice::RouteSection& routeSection = routeData.Sections.at(
                            static_cast<unsigned int>(m_turnByTurnModel.GetCurrentSectionIndex()));
                    const Eegeo::Routes::Webservice::RouteStep& routeStep = routeSection.Steps.at(
                            static_cast<unsigned int>(m_turnByTurnModel.GetCurrentStepIndex()+1));

                    return routeStep;
                }


                const bool NavTurnByTurnLocationService::GetIsAuthorized() const
                {
                    if(!m_pInternalLocationService)
                    {
                        return false;
                    }
                    return m_pInternalLocationService->GetIsAuthorized();
                }

                bool NavTurnByTurnLocationService::IsIndoors()
                {
                    if(m_followingRoute)
                    {
                        const auto& routeStep = GetCurrentRouteStep();
                        return routeStep.IsIndoors;
                    }
                    else if(m_pInternalLocationService)
                    {
                        return m_pInternalLocationService->IsIndoors();
                    }
                    return false;
                }

                Eegeo::Resources::Interiors::InteriorId NavTurnByTurnLocationService::GetInteriorId()
                {
                    if(m_followingRoute)
                    {
                        const auto& routeStep = GetCurrentRouteStep();
                        return Eegeo::Resources::Interiors::InteriorId(routeStep.IndoorId);
                    }
                    else if(m_pInternalLocationService)
                    {
                        return m_pInternalLocationService->GetInteriorId();
                    }

                    return Eegeo::Resources::Interiors::InteriorId::NullId();
                }

                bool NavTurnByTurnLocationService::GetLocation(Eegeo::Space::LatLong& latlong)
                {
                    if(!m_pInternalLocationService)
                    {
                        return false;
                    }


                    // TODO: smoothed!
                    if(m_followingRoute)
                    {
                        //Eegeo_TTY("WTF: Getting location on path");
                        latlong.SetLatitude(m_turnByTurnModel.GetClosestPointOnRoute().GetLatitude());
                        latlong.SetLongitude(m_turnByTurnModel.GetClosestPointOnRoute().GetLongitude());
                        return true;
                    }
                    else
                    {
                        //Eegeo_TTY("WTF: Getting location from service");
                        return m_pInternalLocationService->GetLocation(latlong);
                    }
                }

                bool NavTurnByTurnLocationService::GetAltitude(double& altitude)
                {
                    if(!m_pInternalLocationService)
                    {
                        return false;
                    }

                    return m_pInternalLocationService->GetAltitude(altitude);
                }

                bool NavTurnByTurnLocationService::GetFloorIndex(int& floorIndex)
                {
                    if(!m_pInternalLocationService)
                    {
                        return false;
                    }
                    return m_pInternalLocationService->GetFloorIndex(floorIndex);
                }

                bool NavTurnByTurnLocationService::GetHorizontalAccuracy(double& accuracy)
                {
                    if(!m_pInternalLocationService)
                    {
                        return false;
                    }
                    if(m_followingRoute)
                    {
                        accuracy = m_turnByTurnModel.GetDistanceFromRoute();
                        return true;
                    }
                    else return m_pInternalLocationService->GetHorizontalAccuracy(accuracy);
                }

                // Need to follow path but ease it.
                bool NavTurnByTurnLocationService::GetHeadingDegrees(double& headingDegrees)
                {
                    if(!m_pInternalLocationService)
                    {
                        return false;
                    }
                    if(m_followingRoute)
                    {
                        headingDegrees = m_currentHeading;
                        return true;
                    }
                    else return m_pInternalLocationService->GetHeadingDegrees(headingDegrees);
                }

                void NavTurnByTurnLocationService::StopListening()
                {
                    Eegeo_TTY("WTF: Stop listening");
                    if(m_pInternalLocationService)
                    {
                        m_pInternalLocationService->StopListening();
                    }
                }

                void NavTurnByTurnLocationService::Update(float dt)
                {
                    // Smooth things here.
                    //m_currentHeading += (m_targetHeading-m_currentHeading)*Eegeo::Math::Clamp01(dt)*0.1f;
                    m_currentHeading = m_targetHeading;
                    
                    DrawLocation(Eegeo::Rendering::Colors::RED, 0.0f);
                }
                
                void NavTurnByTurnLocationService::DrawLocation(const Eegeo::v4& color, float time)
                {
                    
                    if(m_debugRenderingEnabled && m_pInternalLocationService != NULL)
                    {
                        
                        Eegeo::Space::LatLong truePos = Eegeo::Space::LatLong::FromDegrees(0,0);
                        if(m_pInternalLocationService->GetLocation(truePos) && GetInteriorId().IsValid())
                        {
                            // Get Interior Floor.
                            Eegeo::dv3 truePosEcef = truePos.ToECEF();
                            float offset = 0.0f;
                            int floorIndex = 0;
                            const auto& interiorModel = m_interiorsModelRepository.GetInterior(GetInteriorId().Value());
                            if(GetFloorIndex(floorIndex))
                            {
                                const float untransformedFloorHeightAboveBase = Eegeo::Resources::Interiors::GetFloorHeight(floorIndex) + Eegeo::Resources::Interiors::INTERIOR_FLOOR_THICKNESS;
                                
                                const float baseAltitude = interiorModel.GetBaseAltitude();
                                
                                offset = (baseAltitude*0.2f) + untransformedFloorHeightAboveBase;
                                //offset = interiorModel.GetFloorAltitude(floorIndex);
                            }
                            
                            Eegeo::v3 verticalOffset = truePosEcef.Norm().ToSingle() * (offset);
                            
                            m_debugRenderer.DrawSphere(truePosEcef + verticalOffset, 1.0f, color, time);
                        }
                        
                        
                    }
                }
            }
        }
    }
}
