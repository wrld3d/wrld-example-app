// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerController.h"
#include "InteriorsExplorerModel.h"
#include "InteriorsExplorerViewModel.h"
#include "IInteriorsExplorerView.h"
#include "IMenuViewModel.h"
#include "IScreenControlViewModel.h"
#include "IMyPinCreationInitiationViewModel.h"
#include "InteriorsExplorerFloorSelectionDraggedMessage.h"
#include "ApplyScreenControl.h"
#include "WorldPinVisibility.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            InteriorsExplorerController::InteriorsExplorerController(SdkModel::InteriorsExplorerModel& model,
                                                                     IInteriorsExplorerView& view,
                                                                     InteriorsExplorerViewModel& viewModel,
                                                                     ExampleAppMessaging::TMessageBus& messageBus,
                                                                     Eegeo::Location::NavigationService& navigationService)
            : m_model(model)
            , m_view(view)
            , m_viewModel(viewModel)
            , m_replayTutorials(false)
            , m_messageBus(messageBus)
            , m_appMode(AppModes::SdkModel::WorldMode)
            , m_navigationService(navigationService)
            , m_dismissedCallback(this, &InteriorsExplorerController::OnDismiss)
            , m_selectFloorCallback(this, &InteriorsExplorerController::OnSelectFloor)
            , m_stateChangedCallback(this, &InteriorsExplorerController::OnStateChanged)
            , m_floorSelectedCallback(this, &InteriorsExplorerController::OnFloorSelected)
            , m_draggingFloorSelectionCallback(this, &InteriorsExplorerController::OnFloorSelectionDragged)
            , m_viewStateCallback(this, &InteriorsExplorerController::OnViewStateChangeScreenControl)
            , m_appModeChangedCallback(this, &InteriorsExplorerController::OnAppModeChanged)
            , m_interiorsUINotificationCallback(this, &InteriorsExplorerController::OnInteriorsUINotificationRequired)
            {
                m_messageBus.SubscribeUi(m_stateChangedCallback);
                m_messageBus.SubscribeUi(m_floorSelectedCallback);
                m_messageBus.SubscribeUi(m_appModeChangedCallback);
                m_messageBus.SubscribeUi(m_interiorsUINotificationCallback);
                
                m_viewModel.InsertOnScreenStateChangedCallback(m_viewStateCallback);
                
                m_view.InsertDismissedCallback(m_dismissedCallback);
                m_view.InsertFloorSelectedCallback(m_selectFloorCallback);
                m_view.InsertFloorSelectionDraggedCallback(m_draggingFloorSelectionCallback);
            }
        
            InteriorsExplorerController::~InteriorsExplorerController()
            {
                m_view.RemoveFloorSelectionDraggedCallback(m_draggingFloorSelectionCallback);
                m_view.RemoveDismissedCallback(m_dismissedCallback);
                m_view.RemoveFloorSelectedCallback(m_selectFloorCallback);
                
                m_viewModel.RemoveOnScreenStateChangedCallback(m_viewStateCallback);
                
                m_messageBus.UnsubscribeUi(m_interiorsUINotificationCallback);
                m_messageBus.UnsubscribeUi(m_stateChangedCallback);
                m_messageBus.UnsubscribeUi(m_floorSelectedCallback);
                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);
            }
            
            void InteriorsExplorerController::OnDismiss()
            {
                m_navigationService.SetGpsMode(Eegeo::Location::NavigationService::GpsMode::GpsModeOff);
                m_messageBus.Publish(InteriorsExplorerExitMessage());
                m_view.SetTouchEnabled(false);
            }
            
            void InteriorsExplorerController::OnSelectFloor(int& selected)
            {
                m_messageBus.Publish(InteriorsExplorerSelectFloorMessage(selected));
            }
            
            void InteriorsExplorerController::OnFloorSelectionDragged(float &dragParam)
            {
                m_messageBus.Publish(InteriorsExplorerFloorSelectionDraggedMessage(dragParam));
            }
            
            void InteriorsExplorerController::OnFloorSelected(const InteriorsExplorerFloorSelectedMessage& message)
            {
                m_view.SetFloorName(message.GetFloorName());
                
                if(m_viewModel.IsFullyOnScreen())
                {
                    m_view.SetSelectedFloorIndex(message.GetFloorIndex());
                }
            }
            
            void InteriorsExplorerController::OnStateChanged(const InteriorsExplorerStateChangedMessage& message)
            {
                if(message.IsInteriorVisible())
                {
                    m_view.UpdateFloors(message.GetFloorShortNames(), message.GetSelectedFloorIndex());
                    m_view.SetTouchEnabled(true);

                    OnFloorSelected(InteriorsExplorerFloorSelectedMessage(message.GetSelectedFloorIndex(), message.GetSelectedFloorName()));

					const int maxTutorialViews = 2;
					bool showExitTutorial = m_replayTutorials || m_model.GetInteriorExitTutorialViewedCount() < maxTutorialViews;
					bool showChangeFloorTutorial = (m_replayTutorials || m_model.GetInteriorChangeFloorTutorialViewedCount() < maxTutorialViews) && m_view.GetCanShowChangeFloorTutorialDialog();

					if(showExitTutorial || showChangeFloorTutorial)
					{
						m_view.AddTutorialDialogs(showExitTutorial, showChangeFloorTutorial);

						if(showExitTutorial)
						{
							m_model.RecordHasViewedInteriorExitTutorial();
						}

						if(showChangeFloorTutorial)
						{
							m_model.RecordHasViewedInteriorChangeFloorTutorial();
						}
					}
                    ReplayTutorials(false);

                    m_viewModel.AddToScreen();
                }
                else
                {
                    m_viewModel.RemoveFromScreen();
                }
            }
            
            void InteriorsExplorerController::OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel &viewModel, float &state)
            {
                ScreenControl::View::Apply(m_viewModel, m_view);
            }
            
            void InteriorsExplorerController::OnAppModeChanged(const AppModes::AppModeChangedMessage& message)
            {
                m_appMode = message.GetAppMode();
                if (m_appMode == AppModes::SdkModel::AppMode::AttractMode)
                {
                    ReplayTutorials(true);
                }
            }

            void InteriorsExplorerController::OnInteriorsUINotificationRequired(const InteriorsExplorerUINotifyMessage & message)
            {
                m_view.PlaySliderAnim();
            }

            void InteriorsExplorerController::ReplayTutorials(const bool enableTutorials)
            {
                m_replayTutorials = enableTutorials;
                m_replayTutorialsCallbacks.ExecuteCallbacks(m_replayTutorials);
            }

            void InteriorsExplorerController::InsertReplayTutorialsChangedCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_replayTutorialsCallbacks.AddCallback(callback);
            }

            void InteriorsExplorerController::RemoveReplayTutorialsChangedCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_replayTutorialsCallbacks.RemoveCallback(callback);
            }
        }
    }
}
