// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavTurnByTurnModel.h"
#include "RouteHelpers.h"
#include "ILocationService.h"
#include "INavRoutingModel.h"
#include "Point3Spline.h"
#include "CameraHelpers.h"
#include "NavRouteInteriorModelHelper.h"

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
                    double CalculateDuration(double t, double duration)
                    {
                        return (1.0-Eegeo::Math::Clamp01(t))*duration;
                    }

                    double CalculateDistanceToEndOfStep(const Eegeo::Routes::Webservice::RouteStep& step, double paramAlongStep)
                    {
                        return step.Distance * (1.0 - Eegeo::Math::Clamp01(paramAlongStep));
                    }

                    float CalculatePathHeading(const Eegeo::Routes::Webservice::RouteStep& step, unsigned int vertIndex)
                    {
                        float fallbackHeading = static_cast<float>(step.Directions.BearingAfter);
                        if(step.Path.size() <= 1 ||
                           step.Distance <= 0.0)
                        {
                           return fallbackHeading;
                        }
                        vertIndex = Eegeo::Min(vertIndex, static_cast<unsigned int>(step.Path.size()-2));
                        Eegeo::dv3 ecefPoint = step.Path.at(vertIndex).ToECEF();
                        Eegeo::dv3 nextPoint = step.Path.at(vertIndex+1).ToECEF();
                        Eegeo::v3 forward = (nextPoint-ecefPoint).Norm().ToSingle();
                        if(forward.LengthSq() == 0.0)
                        {
                            return fallbackHeading;
                        }
                        float headingRadians = Eegeo::Camera::CameraHelpers::GetAbsoluteBearingRadians(ecefPoint, forward);

                        return Eegeo::Math::Rad2Deg(headingRadians);
                    }
                }

                NavTurnByTurnModel::NavTurnByTurnModel(const NavTurnByTurnConfig &config,
                                                       Eegeo::Location::ILocationService &locationService,
                                                       Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository)
                : m_config(config)
                , m_locationService(locationService)
                , m_interiorsModelRepository(interiorsModelRepository)
                , m_closestPointOnRoute(0,0)
                , m_enabled(false)
                , m_remainingDuration(0.0)
                , m_currentStepIndex(0)
                , m_paramAlongStep(0.0)
                , m_paramAlongRoute(0.0)
                , m_distanceFromRoute(0.0)
                , m_indexOfPathSegmentStartVertex(0)
                , m_updateTime(0.0f)
                {
                }

                NavTurnByTurnModel::~NavTurnByTurnModel()
                {
                }

                void NavTurnByTurnModel::Update(float dt) {

                    if(!TurnByTurnEnabled())
                    {
                        return;
                    }

                    m_updateTime += dt;

                    if(m_updateTime >= m_config.updateRateSeconds) {
                        m_updateTime = 0;
                        UpdateTurnByTurn();
                    }
                }

                void NavTurnByTurnModel::UpdateTurnByTurn() {

                    Eegeo::Space::LatLong currentLocation(0,0);
                    bool gotLocation = m_locationService.GetLocation(currentLocation);
                    if(!gotLocation)
                    {
                        // TODO: Handle failure to get current location
                        return;
                    }

                    // TODO: Check this actually works if you're not looking at the indoor model itself.
                    Eegeo::Routes::PointOnRouteOptions options;
                    if(m_locationService.IsIndoors())
                    {
                        const auto& indoorMapId = m_locationService.GetInteriorId().Value();
                        options.IndoorMapId = indoorMapId;

                        int floorIndex;
                        m_locationService.GetFloorIndex(floorIndex);

                        int indoorMapFloorId = 0;
                        const bool interiorDetailsAvailable = NavRouteInteriorModelHelper::TryGetIndoorMapFloorId(m_interiorsModelRepository,
                                                                                                                  indoorMapId,
                                                                                                                  floorIndex,
                                                                                                                  indoorMapFloorId);
                        if (!interiorDetailsAvailable)
                        {
                            return;
                        }

                        options.IndoorMapFloorId = indoorMapFloorId;
                    }

                    Eegeo::Routes::PointOnRoute pointOnRouteResult = Eegeo::Routes::RouteHelpers::GetPointOnRoute(currentLocation, m_route, options);

                    double distanceToRouteAtCurrentPoint = pointOnRouteResult.GetPointOnPathForClosestRouteStep().GetDistanceFromInputPoint();
                    bool shouldReroute = distanceToRouteAtCurrentPoint > m_config.distanceToPathToTriggerReroute;
                    if(shouldReroute)
                    {
                        m_shouldRerouteCallbacks.ExecuteCallbacks();
                    }

                    // TODO: First test is just use the results from here. Actually need to decide at what threshold to advance to next point
                    int nextSectionIndex = pointOnRouteResult.GetRouteSectionIndex();
                    int nextStepIndex = pointOnRouteResult.GetRouteStepIndex();
                    bool isOnCurrentOrNextStep = nextSectionIndex >= m_currentSectionIndex && nextStepIndex >= m_currentStepIndex;
                    if(!isOnCurrentOrNextStep) {
                        return;
                    }

                    bool tooFarFromPath = distanceToRouteAtCurrentPoint > m_config.distanceToPathRangeMeters;
                    if(tooFarFromPath) {
                        return;
                    }

                    m_closestPointOnRoute = pointOnRouteResult.GetPointOnPathForClosestRouteStep().GetResultPoint();
                    m_distanceFromRoute = pointOnRouteResult.GetPointOnPathForClosestRouteStep().GetDistanceFromInputPoint();

                    // NOTE: Duration is currently just a fraction of the total route duration from the service / your progress.
                    m_remainingDuration = CalculateDuration(pointOnRouteResult.GetFractionAlongRoute(), m_route.Duration);

                    m_currentSectionIndex = nextSectionIndex;
                    m_currentStepIndex = nextStepIndex;

                    m_paramAlongStep = pointOnRouteResult.GetFractionAlongRouteStep();
                    m_paramAlongRoute = pointOnRouteResult.GetFractionAlongRoute();
                    const Eegeo::Routes::Webservice::RouteSection& currentSection = m_route.Sections.at(
                            static_cast<unsigned long>(m_currentSectionIndex));
                    const Eegeo::Routes::Webservice::RouteStep& currentStep = currentSection.Steps.at(
                            static_cast<unsigned long>(m_currentStepIndex));

                    m_distanceToNextStep = CalculateDistanceToEndOfStep(currentStep, pointOnRouteResult.GetFractionAlongRouteStep());

                    m_indexOfPathSegmentStartVertex = pointOnRouteResult.GetPointOnPathForClosestRouteStep().GetIndexOfPathSegmentStartVertex();
                    m_pathHeadingDegrees = CalculatePathHeading(currentStep, static_cast<unsigned int>(m_indexOfPathSegmentStartVertex));

                    m_updateCallbacks.ExecuteCallbacks();
                }

                void NavTurnByTurnModel::Start(const Eegeo::Routes::Webservice::RouteData& route)
                {
                    if(TurnByTurnEnabled()) {
                        return;
                    }

                    m_route = route;
                    m_distanceFromRoute = 0.0;
                    m_remainingDuration = route.Duration;
                    m_distanceToNextStep = 0;
                    m_currentSectionIndex = 0;
                    m_currentStepIndex = 0;
                    m_paramAlongRoute = 0.0;
                    m_paramAlongStep = 0.0;
                    m_updateTime = 0.0f;
                    m_pathHeadingDegrees = GetPathHeadingDegrees();
                    m_indexOfPathSegmentStartVertex = 0;
                    Eegeo_ASSERT(route.Sections.size() > 0, "No sections in route");
                    Eegeo_ASSERT(route.Sections.at(0).Steps.size() > 0, "No Steps in Section");
                    Eegeo_ASSERT(route.Sections.at(0).Steps.at(0).Path.size() > 0, "No Path in step");
                    m_closestPointOnRoute = route.Sections.at(0).Steps.at(0).Path.at(0);
                    m_enabled = true;

                    m_startedCallbacks.ExecuteCallbacks();

                    UpdateTurnByTurn();
                }

                void NavTurnByTurnModel::Stop()
                {
                    if(TurnByTurnEnabled())
                    {
                        m_enabled = false;

                        m_stoppedCallbacks.ExecuteCallbacks();
                    }
                }

                void NavTurnByTurnModel::InsertStartedCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_startedCallbacks.AddCallback(callback);
                }

                void NavTurnByTurnModel::RemoveStartedCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_startedCallbacks.RemoveCallback(callback);
                }

                void NavTurnByTurnModel::InsertStoppedCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_stoppedCallbacks.AddCallback(callback);
                }

                void NavTurnByTurnModel::RemoveStoppedCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_stoppedCallbacks.RemoveCallback(callback);
                }

                void NavTurnByTurnModel::InsertUpdatedCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_updateCallbacks.AddCallback(callback);
                }

                void NavTurnByTurnModel::RemoveUpdatedCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_updateCallbacks.RemoveCallback(callback);
                }

                void NavTurnByTurnModel::InsertShouldRerouteCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_shouldRerouteCallbacks.AddCallback(callback);
                }

                void NavTurnByTurnModel::RemoveShouldRerouteCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_shouldRerouteCallbacks.RemoveCallback(callback);
                }
            }
        }
    }
}
