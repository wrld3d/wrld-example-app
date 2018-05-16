
#include "NavTurnByTurnController.h"
#include "INavTurnByTurnModel.h"
#include "INavRoutingModel.h"
#include "NavigationService.h"


namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            namespace TurnByTurn
            {
                NavTurnByTurnController::NavTurnByTurnController(
                        INavTurnByTurnModel &turnByTurnModel,
                        INavRoutingModel& navRoutingModel,
                        Eegeo::Location::NavigationService& navigationService)
                : m_turnByTurnModel(turnByTurnModel)
                , m_navRoutingModel(navRoutingModel)
                , m_navigationService(navigationService)
                , m_turnByTurnStartedCallback(this, &NavTurnByTurnController::HandleTurnByTurnStarted)
                , m_turnByTurnStoppedCallback(this, &NavTurnByTurnController::HandleTurnByTurnStopped)
                , m_turnByTurnUpdatedCallback(this, &NavTurnByTurnController::HandleTurnByTurnUpdated)
                {
                    m_turnByTurnModel.InsertStartedCallback(m_turnByTurnStartedCallback);
                    m_turnByTurnModel.InsertStoppedCallback(m_turnByTurnStoppedCallback);
                    m_turnByTurnModel.InsertUpdatedCallback(m_turnByTurnUpdatedCallback);
                }

                NavTurnByTurnController::~NavTurnByTurnController()
                {
                    m_turnByTurnModel.InsertUpdatedCallback(m_turnByTurnUpdatedCallback);
                    m_turnByTurnModel.InsertStoppedCallback(m_turnByTurnStoppedCallback);
                    m_turnByTurnModel.InsertStartedCallback(m_turnByTurnStartedCallback);
                }

                void NavTurnByTurnController::Update(float dt)
                {
                    m_turnByTurnModel.Update(dt);
                }

                void NavTurnByTurnController::HandleTurnByTurnStarted()
                {
                    m_navRoutingModel.SetNavMode(NavRoutingMode::Active);
                    m_navigationService.SetGpsMode(Eegeo::Location::NavigationService::GpsMode::GpsModeCompass);
                }

                void NavTurnByTurnController::HandleTurnByTurnStopped()
                {
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

                void NavTurnByTurnController::HandleTurnByTurnUpdated()
                {
                    m_navRoutingModel.SetCurrentDirection(m_turnByTurnModel.GetCurrentStepIndex());
                    m_navRoutingModel.SetRemainingRouteDuration(m_turnByTurnModel.GetRemainingDuration());

                    // TODO: Update distance - this is done on a per step basis so might need to regen whole route
                    // TODO: Update route draw progress
                }
            }
        }
    }
}