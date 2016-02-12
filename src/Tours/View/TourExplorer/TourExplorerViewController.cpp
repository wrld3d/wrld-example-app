// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourExplorerViewController.h"
#include "ITourExplorerViewModel.h"
#include "ITourExplorerView.h"
#include "ApplyScreenControl.h"
#include "ITourExplorerCompositeViewController.h"
#include "TourActiveStateChangedMessage.h"
#include "ActiveTourQuitSelectedMessage.h"
#include "CurrentTourCardTappedMessage.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourExplorer
            {
                TourExplorerViewController::TourExplorerViewController(ITourExplorerViewModel& viewModel,
                                                                       ITourExplorerCompositeViewController& tourExplorerCompositeViewController,
                                                                       ITourExplorerView& view,
                                                                       ExampleAppMessaging::TMessageBus& messageBus)
                : m_viewModel(viewModel)
                , m_tourExplorerCompositeViewController(tourExplorerCompositeViewController)
                , m_view(view)
                , m_messageBus(messageBus)
                , m_dismissedCallback(this, &TourExplorerViewController::OnDismissed)
                , m_exitedCallback(this, &TourExplorerViewController::OnExited)
                , m_stateChangedCallback(this, &TourExplorerViewController::OnStateChanged)
                , m_viewStateCallback(this, &TourExplorerViewController::OnViewStateChangeScreenControl)
                , m_tourChangeRequestCallback(this, &TourExplorerViewController::OnTourChangeRequested)
                , m_currentTourCardTappedCallback(this, &TourExplorerViewController::OnCurrentTourCardTapped)
                {
                    m_viewModel.InsertOnScreenStateChangedCallback(m_viewStateCallback);
                    
                    m_view.InsertStateChangedCallback(m_stateChangedCallback);
                    m_view.InsertDismissedCallback(m_dismissedCallback);
                    m_view.InsertExitedCallback(m_exitedCallback);
                    m_view.InsertChangeTourRequestCallback(m_tourChangeRequestCallback);
                    m_view.InsertCurrentTourCardTappedCallback(m_currentTourCardTappedCallback);
                    
                    m_view.SetOnScreenStateToIntermediateValue(m_viewModel.OnScreenState());
                }
                
                TourExplorerViewController::~TourExplorerViewController()
                {
                    m_view.RemoveCurrentTourCardTappedCallback(m_currentTourCardTappedCallback);
                    m_view.RemoveStateChangedCallback(m_stateChangedCallback);
                    m_view.RemoveExitedCallback(m_exitedCallback);
                    m_view.RemoveDismissedCallback(m_dismissedCallback);
                    m_view.RemoveChangeTourRequestCallback(m_tourChangeRequestCallback);
                    
                    m_viewModel.RemoveOnScreenStateChangedCallback(m_viewStateCallback);
                }
                
                void TourExplorerViewController::OnStateChanged(int& activeStateIndex)
                {
                    //m_metricsService.SetEvent("TourExplorerViewController: Changed State");
                    m_messageBus.Publish(TourActiveStateChangedMessage(activeStateIndex));
                }
                
                void TourExplorerViewController::OnTourChangeRequested(std::string& tourName)
                {
                    m_messageBus.Publish(TourChangeRequestMessage(tourName));
                }
                
                void TourExplorerViewController::OnDismissed()
                {
                    //scott -- should probably do this in the SDKModel ActiveTourQuitSelectedMessageHandler, or an SDK domain event?
                    m_messageBus.Publish(GpsMarker::GpsMarkerVisibilityMessage(true));
                    
                    //m_metricsService.SetEvent("TourExplorerViewController: Exited");
                    m_tourExplorerCompositeViewController.CloseTourExplorer();
                    m_messageBus.Publish(ActiveTourQuitSelectedMessage(false));
                }
                
                void TourExplorerViewController::OnExited()
                {
                    //scott -- should probably do this in the SDKModel ActiveTourQuitSelectedMessageHandler, or an SDK domain event?
                    m_messageBus.Publish(GpsMarker::GpsMarkerVisibilityMessage(true));
                    
                    m_tourExplorerCompositeViewController.CloseTourExplorer();
                    m_messageBus.Publish(ActiveTourQuitSelectedMessage(true));
                }
                
                void TourExplorerViewController::OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel &viewModel,
                                                                                float &state)
                {
                    
                    if(m_view.GetCurrentTour() != m_viewModel.GetCurrentTour() && state > 0.0f)
                    {
                        m_view.SetCurrentTour(m_viewModel.GetCurrentTour(), m_viewModel.GetInitialCard(), m_viewModel.GetShowBackButton());
                    }
                    
                    ScreenControl::View::Apply(m_viewModel, m_view);

                    //scott -- should probably do this in the SDKModel dispatcher, or an equivalent SDK domain event?
                    if(!m_viewModel.IsFullyOffScreen())
                    {
                        m_messageBus.Publish(GpsMarker::GpsMarkerVisibilityMessage(false));
                    }
                }
                
                void TourExplorerViewController::OnCurrentTourCardTapped()
                {
                    m_messageBus.Publish(Tours::CurrentTourCardTappedMessage());
                }
            }
        }
    }
}
