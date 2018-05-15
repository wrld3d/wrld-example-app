
#include "NavTurnByTurnModel.h"
#include "RouteHelpers.h"
#include "ILocationService.h"
#include "INavRoutingModel.h"

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
                        return (1.0-t)*duration;
                    }

                    int GetStepIndexFromRouteIndices(const Eegeo::Routes::Webservice::RouteData& route,
                        int sectionIndex,
                        int stepIndex)
                    {
                        int currentIndex = 0;
                        for(int routeSectionIndex = 0; routeSectionIndex < route.Sections.size(); ++routeSectionIndex)
                        {
                            const Eegeo::Routes::Webservice::RouteSection& currentSection = route.Sections.at(
                                    static_cast<unsigned long>(sectionIndex));

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

                NavTurnByTurnModel::NavTurnByTurnModel(const NavTurnByTurnConfig &config,
                                                       INavRoutingModel &navRoutingModel,
                                                       Eegeo::Location::ILocationService &locationService)
                : m_config(config)
                , m_navRoutingModel(navRoutingModel)
                , m_locationService(locationService)
                , m_closestPointOnRoute(0,0)
                , m_enabled(false)
                , m_remainingDuration(0.0)
                , m_currentStepIndex(0)
                , m_paramAlongStep(0.0)
                , m_paramAlongRoute(0.0)
                , m_distanceFromRoute(0.0)
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

                    SdkModel::NavRoutingRouteModel currentRouteModel;
                    bool gotRoute = m_navRoutingModel.TryGetRoute(currentRouteModel);
                    if(!gotRoute)
                    {
                        Stop();
                        return;
                    }

                    const Eegeo::Routes::Webservice::RouteData& sourceRoute = currentRouteModel.GetSourceRouteData();

                    // TODO: Check this actually works if you're not looking at the indoor model itself.
                    Eegeo::Routes::PointOnRouteOptions options;
                    if(m_locationService.IsIndoors())
                    {
                        Eegeo::Resources::Interiors::InteriorId indoorId = m_locationService.GetInteriorId();
                        options.IndoorMapId = indoorId.Value();

                        int floorIndex;
                        m_locationService.GetFloorIndex(floorIndex);
                        // TODO: FloorIndex != FloorID.  Check how to convert these
                        // (Might require Indoor model which only exists if you're in it)
                        options.IndoorMapFloorId = floorIndex;
                    }

                    Eegeo::Routes::PointOnRoute pointOnRouteResult = Eegeo::Routes::RouteHelpers::GetPointOnRoute(currentLocation, sourceRoute, options);

                    m_closestPointOnRoute = pointOnRouteResult.GetPointOnPathForClosestRouteStep().GetResultPoint();
                    m_distanceFromRoute = pointOnRouteResult.GetPointOnPathForClosestRouteStep().GetDistanceFromInputPoint();

                    // NOTE: Duration is just a fraction of the total route duration from the service / your progress.
                    // This isn't accurate - discuss a better way of calculating remaining duration based on average speed or by recalling the
                    // service with more information?
                    m_remainingDuration = CalculateDuration(pointOnRouteResult.GetFractionAlongRoute(), currentRouteModel.GetDuration());

                    // TODO: First test is just use the results from here. Actually need to decide at what threshold to advance to next point
                    // TODO: Also, should maybe guard against going backwards or jumping several points due to error.
                    // Also this step is a linear index through the whole route - need to translate that from Section/Step index format
                    //int currentStep = m_navRoutingModel.GetCurrentDirection();
                    m_currentStepIndex = GetStepIndexFromRouteIndices(currentRouteModel.GetSourceRouteData(),
                                                                      pointOnRouteResult.GetRouteSectionIndex(),
                                                                      pointOnRouteResult.GetRouteStepIndex());

                    m_paramAlongStep = pointOnRouteResult.GetFractionAlongRouteStep();
                    m_paramAlongRoute = pointOnRouteResult.GetFractionAlongRoute();

                    m_updateCallbacks.ExecuteCallbacks();
                }

                void NavTurnByTurnModel::Start()
                {
                    if(TurnByTurnEnabled()) {
                        return;
                    }

                    if(!m_navRoutingModel.HasRoute())
                    {
                        return;
                    }

                    m_distanceFromRoute = 0.0;
                    m_remainingDuration = m_navRoutingModel.GetRemainingRouteDuration();
                    m_currentStepIndex = 0;
                    m_paramAlongRoute = 0.0;
                    m_paramAlongStep = 0.0;
                    m_updateTime = 0.0f;
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

            }
        }
    }
}