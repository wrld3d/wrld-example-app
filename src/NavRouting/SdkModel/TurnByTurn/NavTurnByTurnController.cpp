// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavTurnByTurnController.h"
#include "INavTurnByTurnModel.h"
#include "INavRoutingModel.h"
#include "NavigationService.h"
#include "GpsMarkerModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            namespace TurnByTurn
            {
                namespace
                {
                    int GetDirectionIndexFromRouteIndices(const Eegeo::Routes::Webservice::RouteData& route,
                                                         int sectionIndex,
                                                         int stepIndex)
                    {
                        int currentIndex = 0;
                        for(int routeSectionIndex = 0; routeSectionIndex < route.Sections.size(); ++routeSectionIndex)
                        {
                            const Eegeo::Routes::Webservice::RouteSection& currentSection = route.Sections.at(
                                    static_cast<unsigned long>(routeSectionIndex));

                            for(int routeStepIndex = 0; routeStepIndex < currentSection.Steps.size(); ++routeStepIndex)
                            {
                                if(routeSectionIndex == sectionIndex && routeStepIndex == stepIndex)
                                {
                                    return currentIndex;
                                }

                                currentIndex++;
                            }
                        }

                        return 0;
                    }
                }

                NavTurnByTurnController::NavTurnByTurnController(
                        INavTurnByTurnModel &turnByTurnModel,
                        INavRoutingModel& navRoutingModel,
                        Eegeo::Location::NavigationService& navigationService,
                        GpsMarker::SdkModel::GpsMarkerModel& gpsMarkerModel)
                : m_turnByTurnModel(turnByTurnModel)
                , m_navRoutingModel(navRoutingModel)
                , m_navigationService(navigationService)
                , m_gpsMarkerModel(gpsMarkerModel)
                , m_turnByTurnStartedCallback(this, &NavTurnByTurnController::HandleTurnByTurnStarted)
                , m_turnByTurnStoppedCallback(this, &NavTurnByTurnController::HandleTurnByTurnStopped)
                , m_turnByTurnWillUpdateCallback(this, &NavTurnByTurnController::HandleTurnByTurnWillUpdate)
                {
                    m_turnByTurnModel.InsertStartedCallback(m_turnByTurnStartedCallback);
                    m_turnByTurnModel.InsertStoppedCallback(m_turnByTurnStoppedCallback);
                    m_turnByTurnModel.InsertWillUpdateCallback(m_turnByTurnWillUpdateCallback);
                }

                NavTurnByTurnController::~NavTurnByTurnController()
                {
                    m_turnByTurnModel.RemoveWillUpdateCallback(m_turnByTurnWillUpdateCallback);
                    m_turnByTurnModel.RemoveStoppedCallback(m_turnByTurnStoppedCallback);
                    m_turnByTurnModel.RemoveStartedCallback(m_turnByTurnStartedCallback);
                }

                void NavTurnByTurnController::Update(float dt)
                {
                    m_turnByTurnModel.Update(dt);
                }

                void NavTurnByTurnController::HandleTurnByTurnStarted()
                {
                    m_navRoutingModel.SetSelectedDirection(0);
                    m_navRoutingModel.SetCurrentDirection(0);
                    m_navRoutingModel.SetNavMode(NavRoutingMode::Active);
                    m_gpsMarkerModel.SetAccuracyRingEnabled(true);
                }

                void NavTurnByTurnController::HandleTurnByTurnStopped()
                {
                    m_gpsMarkerModel.SetAccuracyRingEnabled(false);
                    m_navigationService.SetGpsMode(Eegeo::Location::NavigationService::GpsMode::GpsModeOff);

                    if(m_navRoutingModel.HasRoute())
                    {
                        m_navRoutingModel.SetNavMode(NavRoutingMode::Ready);
                    }
                    else
                    {
                        m_navRoutingModel.SetNavMode(NavRoutingMode::NotReady);
                    }
                }

                void NavTurnByTurnController::HandleTurnByTurnWillUpdate()
                {
                    SdkModel::NavRoutingRouteModel currentRouteModel;
                    if(!m_navRoutingModel.TryGetRoute(currentRouteModel)) {
                        return;
                    }

                    int directionIndex = GetDirectionIndexFromRouteIndices(currentRouteModel.GetSourceRouteData(),
                                                                           m_turnByTurnModel.GetCurrentSectionIndex(),
                                                                           m_turnByTurnModel.GetCurrentStepIndex());

                    bool currentDirectionIsSelected = m_navRoutingModel.GetSelectedDirection() == m_navRoutingModel.GetCurrentDirection();
                    m_navRoutingModel.SetCurrentDirection(directionIndex);
                    if(currentDirectionIsSelected)
                    {
                        m_navRoutingModel.SetSelectedDirection(directionIndex);
                    }
                    m_navRoutingModel.SetRemainingRouteDuration(m_turnByTurnModel.GetRemainingDuration());

                    auto currentDirection = currentRouteModel.GetDirections()[directionIndex];
                    currentDirection.SetDistance(m_turnByTurnModel.GetDistanceToNextStep());
                    m_navRoutingModel.UpdateCurrentDirection(currentDirection);
                }
            }
        }
    }
}
