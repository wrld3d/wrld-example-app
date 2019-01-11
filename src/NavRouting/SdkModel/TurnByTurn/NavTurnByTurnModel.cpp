// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavTurnByTurnModel.h"
#include "RouteHelpers.h"
#include "ILocationService.h"
#include "INavRoutingModel.h"
#include "Point3Spline.h"
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
                }

                NavTurnByTurnModel::NavTurnByTurnModel(const NavTurnByTurnConfig &config,
                                                       Eegeo::Location::ILocationService &locationService,
                                                       Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository)
                : m_config(config)
                , m_locationService(locationService)
                , m_interiorsModelRepository(interiorsModelRepository)
                , m_closestPointOnRoute(0,0)
                , m_enabled(false)
                , m_shouldDisable(false)
                , m_remainingDuration(0.0)
                , m_currentStepIndex(0)
                , m_paramAlongStep(0.0)
                , m_paramAlongRoute(0.0)
                , m_distanceFromRoute(0.0)
                , m_indexOfPathSegmentStartVertex(0)
                , m_updateTime(0.0f)
                , m_secondsElapsedSinceOffRoute(0.0f)
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

                    if (m_shouldDisable)
                    {
                        DisableTurnByTurn();
                        return;
                    }
                    
                    if(HasLostLocationService())
                    {
                        return;
                    }

                    m_updateTime += dt;
                    m_secondsElapsedSinceOffRoute += dt;

                    if(m_updateTime >= m_config.updateRateSeconds) {
                        m_updateTime = 0;
                        UpdateTurnByTurn();
                    }
                }

                void NavTurnByTurnModel::DisableTurnByTurn()
                {
                    m_enabled = false;
                    m_shouldDisable = false;
                    m_stoppedCallbacks.ExecuteCallbacks();
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

                    if (!pointOnRouteResult.IsValidResult())
                    {
                        return;
                    }

                    double distanceToRouteAtCurrentPoint = pointOnRouteResult.GetPointOnPathForClosestRouteStep().GetDistanceFromInputPoint();

                    bool tooFarFromPath = IsTooFarFromPath(distanceToRouteAtCurrentPoint);

                    if(!tooFarFromPath)
                    {
                        m_secondsElapsedSinceOffRoute = 0.0f;
                    }

                    if(m_secondsElapsedSinceOffRoute > m_config.timeInSecondsToTriggerReroute)
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
                    
                    m_willUpdateCallbacks.ExecuteCallbacks();
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
                    m_indexOfPathSegmentStartVertex = 0;
                    m_secondsElapsedSinceOffRoute = 0.f;
                    m_enabled = true;
                    m_shouldDisable = false;

                    m_startedCallbacks.ExecuteCallbacks();
                }

                void NavTurnByTurnModel::Stop()
                {
                    if(TurnByTurnEnabled())
                    {
                        m_shouldDisable = true;
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

                void NavTurnByTurnModel::InsertWillUpdateCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_willUpdateCallbacks.AddCallback(callback);
                }

                void NavTurnByTurnModel::RemoveWillUpdateCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_willUpdateCallbacks.RemoveCallback(callback);
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
                
                void NavTurnByTurnModel::InsertInteriorLocationLostCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_interiorLocationLostCallbacks.AddCallback(callback);
                }
                
                void NavTurnByTurnModel::RemoveInteriorLocationLostCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_interiorLocationLostCallbacks.RemoveCallback(callback);
                }

                bool NavTurnByTurnModel::IsTooFarFromPath(double distanceToRouteAtCurrentPoint)
                {
                    double accuracy;
                    bool accuracyFetchSuccessful = m_locationService.GetHorizontalAccuracy(accuracy);

                    if(accuracyFetchSuccessful){
                        return distanceToRouteAtCurrentPoint > (m_config.distanceToPathToTriggerReroute + accuracy);
                    }
                    else{
                        return distanceToRouteAtCurrentPoint > m_config.distanceToPathToTriggerReroute;
                    }
                }
                
                bool NavTurnByTurnModel::HasLostLocationService()
                {
                    if(!m_locationService.GetIsAuthorized())
                    {
                        Stop();
                        m_interiorLocationLostCallbacks.ExecuteCallbacks();
                        return true;
                    }
                    
                    return false;
                    
                }
            }
        }
    }
}
