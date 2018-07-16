// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavTurnByTurnCompletionHandler.h"
#include "INavTurnByTurnModel.h"
#include "INavRoutingModel.h"
#include "ILocationService.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            namespace TurnByTurn
            {
                NavTurnByTurnCompletionHandler::NavTurnByTurnCompletionHandler(INavTurnByTurnModel& turnByTurnModel,
                                                                               INavRoutingModel& navRoutingModel,
                                                                               Eegeo::Location::ILocationService& locationService,
                                                                               float accuracyMultiplier,
                                                                               float minDistanceToFinish)
                : m_turnByTurnModel(turnByTurnModel)
                , m_navRoutingModel(navRoutingModel)
                , m_locationService(locationService)
                , m_accuracyMultiplier(accuracyMultiplier)
                , m_minDistanceToFinish(minDistanceToFinish)
                , m_directionCount(0)
                , m_turnByTurnStartedCallback(this, &NavTurnByTurnCompletionHandler::HandleTurnByTurnStarted)
                , m_turnByTurnUpdatedCallback(this, &NavTurnByTurnCompletionHandler::HandleTurnByTurnUpdated)
                {
                    m_turnByTurnModel.InsertStartedCallback(m_turnByTurnStartedCallback);
                    m_turnByTurnModel.InsertUpdatedCallback(m_turnByTurnUpdatedCallback);
                }
                
                NavTurnByTurnCompletionHandler::~NavTurnByTurnCompletionHandler()
                {
                    m_turnByTurnModel.RemoveUpdatedCallback(m_turnByTurnUpdatedCallback);
                    m_turnByTurnModel.RemoveStartedCallback(m_turnByTurnStartedCallback);
                }
                
                void NavTurnByTurnCompletionHandler::HandleTurnByTurnStarted()
                {
                    ExampleApp::NavRouting::SdkModel::NavRoutingRouteModel out_routeModel;
                    if (m_navRoutingModel.TryGetRoute(out_routeModel))
                    {
                        m_directionCount = static_cast<int>(out_routeModel.GetDirections().size());
                    }
                }
                
                void NavTurnByTurnCompletionHandler::HandleTurnByTurnUpdated()
                {
                    bool isSecondLastStep = m_navRoutingModel.GetCurrentDirection() == (m_directionCount - 2);
                    
                    if (isSecondLastStep)
                    {
                        float distanceThresholdToComplete = m_minDistanceToFinish;
                        
                        double accuracy;
                        if (m_locationService.GetHorizontalAccuracy(accuracy))
                        {
                            float distanceBasedOnAccuracy = accuracy * m_accuracyMultiplier;
                            
                            if (distanceBasedOnAccuracy < distanceThresholdToComplete)
                            {
                                distanceThresholdToComplete = distanceBasedOnAccuracy;
                            }
                        }
                        
                        if (m_turnByTurnModel.GetDistanceToNextStep() <= distanceThresholdToComplete)
                        {
                            m_turnByTurnModel.Stop();
                        }
                    }
                }
            }
        }
    }
}
