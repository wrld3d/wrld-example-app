// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerModel.h"
#include "InteriorController.h"
#include "InteriorsExplorerStateChangedMessage.h"
#include "InteriorsExplorerFloorSelectedMessage.h"
#include "InteriorsExplorerEnteredMessage.h"

#include "InteriorsModel.h"
#include "InteriorsFloorModel.h"
#include "InteriorSelectionModel.h"
#include "IMetricsService.h"
#include "IAppModeModel.h"
#include "InteriorsModel.h"
#include "InteriorId.h"
#include "InteriorsFloorModel.h"
#include "IVisualMapService.h"
#include "VisualMapState.h"

#include "CurrentInteriorViewModel.h"

#include "ICameraTransitionController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace
            {
            
                const std::string MetricEventInteriorsVisible = "TimedEvent: Interiors Visible";
                const std::string MetricEventInteriorSelected = "Interior Selected";
                const std::string MetricEventInteriorFloorSelected = "Interior Floor Selected";
                const std::string MetricEventInteriorExitPressed = "Interior Exit Pressed";
                
                std::string ToFloorName(const Eegeo::Resources::Interiors::InteriorsFloorModel* pFloorModel)
                {
                    return pFloorModel->GetFloorName();
                }
            }
            
            InteriorsExplorerModel::InteriorsExplorerModel(Eegeo::Resources::Interiors::InteriorController& controller,
                                                           Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                           VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                           ExampleAppMessaging::TMessageBus& messageBus,
                                                           ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus,
                                                           Metrics::IMetricsService& metricsService)
            : m_controller(controller)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_visualMapService(visualMapService)
            , m_messageBus(messageBus)
            , m_sdkModelDomainEventBus(sdkModelDomainEventBus)
            , m_metricsService(metricsService)
            , m_controllerStateChangedCallback(this, &InteriorsExplorerModel::OnControllerStateChanged)
            , m_controllerVisibilityChangedCallback(this, &InteriorsExplorerModel::OnControllerVisibilityChanged)
            , m_controllerFloorChangedCallback(this, &InteriorsExplorerModel::OnControllerFloorChanged)
            , m_exitCallback(this, &InteriorsExplorerModel::OnExit)
            , m_selectFloorCallback(this, &InteriorsExplorerModel::OnSelectFloor)
            , m_floorSelectionDraggedCallback(this, &InteriorsExplorerModel::OnFloorSelectionDragged)
            , m_interiorExplorerEnabled(false)
            {
                m_controller.RegisterStateChangedCallback(m_controllerStateChangedCallback);
                m_controller.RegisterVisibilityChangedCallback(m_controllerVisibilityChangedCallback);
                m_controller.RegisterFloorChangedCallback(m_controllerFloorChangedCallback);
                
                m_messageBus.SubscribeNative(m_exitCallback);
                m_messageBus.SubscribeNative(m_selectFloorCallback);
                m_messageBus.SubscribeNative(m_floorSelectionDraggedCallback);
            }
            
            InteriorsExplorerModel::~InteriorsExplorerModel()
            {
                m_messageBus.UnsubscribeNative(m_floorSelectionDraggedCallback);
                m_messageBus.UnsubscribeNative(m_selectFloorCallback);
                m_messageBus.UnsubscribeNative(m_exitCallback);

                m_controller.UnregisterStateChangedCallback(m_controllerStateChangedCallback);
                m_controller.UnregisterVisibilityChangedCallback(m_controllerVisibilityChangedCallback);
                m_controller.UnregisterFloorChangedCallback(m_controllerFloorChangedCallback);
            }

            void InteriorsExplorerModel::ChangeToInteriorMapState()
            {
                m_visualMapService.StoreCurrentMapState();
                const VisualMap::SdkModel::VisualMapState& currentState = m_visualMapService.GetCurrentVisualMapState();
                m_visualMapService.SetVisualMapState(currentState.GetTheme(), "DayDefault", true);
            }
            
            void InteriorsExplorerModel::ResumePreviousMapState()
            {
                m_visualMapService.RestorePreviousMapState();
            }
            
            void InteriorsExplorerModel::ShowInteriorExplorer()
            {
                ShowInteriorExplorer(false);
            }
            
            void InteriorsExplorerModel::ShowInteriorExplorer(bool fromAnotherInterior)
            {
                Eegeo_ASSERT(m_controller.InteriorInScene(), "Can't show interior explorer without a selected and streamed interior");
                
                if(!m_interiorExplorerEnabled)
                {
                    // stop the state stack from growing when going from interior to another interior.
                    if (!fromAnotherInterior)
                    {
                        ChangeToInteriorMapState();
                    }
                    
                    const Eegeo::Resources::Interiors::InteriorId& interiorId = m_interiorSelectionModel.GetSelectedInteriorId();
                    m_metricsService.SetEvent(MetricEventInteriorSelected, "InteriorId", interiorId.Value());
                    
                    m_metricsService.BeginTimedEvent(MetricEventInteriorsVisible);
                    m_interiorExplorerEnabled = true;
                    PublishInteriorExplorerStateChange();
                    m_sdkModelDomainEventBus.Publish(InteriorsExplorerEnteredMessage(interiorId));
                }
            }
            
            void InteriorsExplorerModel::HideInteriorExplorer()
            {
                if(m_interiorExplorerEnabled)
                {
                    m_metricsService.EndTimedEvent(MetricEventInteriorsVisible);
                    m_interiorExplorerEnabled = false;
                    PublishInteriorExplorerStateChange();
                }
            }
            
            void InteriorsExplorerModel::OnControllerStateChanged()
            {
            }
            
            void InteriorsExplorerModel::OnControllerFloorChanged()
            {
                const Eegeo::Resources::Interiors::InteriorsFloorModel* pFloorModel = NULL;
                Eegeo_ASSERT(m_controller.TryGetCurrentFloorModel(pFloorModel), "Could not fetch current floor model");
                
                Eegeo::Resources::Interiors::CurrentInteriorViewModel* pViewModel;
                m_controller.TryGetCurrentViewModel(pViewModel);
                
                m_messageBus.Publish(InteriorsExplorerFloorSelectedMessage(m_controller.GetCurrentFloorIndex(), pFloorModel->GetReadableFloorName()));
            }
            
            void InteriorsExplorerModel::OnControllerVisibilityChanged()
            {

            }
        
            void InteriorsExplorerModel::OnExit(const InteriorsExplorerExitMessage& message)
            {
                Exit();
            }
            
            void InteriorsExplorerModel::Exit()
            {
                HideInteriorExplorer();
                m_metricsService.SetEvent(MetricEventInteriorExitPressed);
                m_interiorExplorerExitedCallbacks.ExecuteCallbacks();
            }
            
            void InteriorsExplorerModel::OnSelectFloor(const InteriorsExplorerSelectFloorMessage &message)
            {
                SelectFloor(message.GetFloor());
            }
            
            void InteriorsExplorerModel::OnFloorSelectionDragged(const InteriorsExplorerFloorSelectionDraggedMessage &message)
            {
                const Eegeo::Resources::Interiors::InteriorsModel* pModel = NULL;
                Eegeo_ASSERT(m_controller.TryGetCurrentModel(pModel), "Could not fetch current model");
                
                const float dragParameter = message.GetDragParam();
                const float floorParam = dragParameter * (pModel->GetFloorCount()-1);
                
                // Need to expose
                // - Being able to toggle expanded mode on off
                // - Disabling the floor animation and setting the floor parameter manually.
                //m_controller.Set
                Eegeo::Resources::Interiors::CurrentInteriorViewModel* pViewModel = NULL;
                if(m_controller.TryGetCurrentViewModel(pViewModel))
                {
                    Eegeo_TTY("SDKMODEL: DRAGGING %f", floorParam);
                    pViewModel->SetExpandedModeEnabled(true);
                    pViewModel->SetFloorParameter(floorParam);
                }
            }

            void InteriorsExplorerModel::SelectFloor(int floor)
            {
                Eegeo_TTY("SDKMODEL: DRAG STOPPED SELECT FLOOR %d", floor);
                if(!m_controller.InteriorIsVisible())
                {
                    return;
                }
                Eegeo_TTY("SDKMODEL: DRAG STOPPED GET VM");
                Eegeo::Resources::Interiors::CurrentInteriorViewModel* pViewModel = NULL;
                if(m_controller.TryGetCurrentViewModel(pViewModel))
                {
                    Eegeo_TTY("SDKMODEL: DRAG STOPPED EXPANDED OFF");
                    pViewModel->SetExpandedModeEnabled(false);
                }
                
                if(m_controller.GetCurrentFloorIndex() == floor)
                {
                    return;
                }
                
                m_controller.SetCurrentFloor(floor);
                
                const Eegeo::Resources::Interiors::InteriorsFloorModel* pFloorModel = NULL;
                Eegeo_ASSERT(m_controller.TryGetCurrentFloorModel(pFloorModel), "Could not fetch current floor model");

                m_metricsService.SetEvent(MetricEventInteriorFloorSelected, "InteriorId", m_interiorSelectionModel.GetSelectedInteriorId().Value(), "FloorName", pFloorModel->GetFloorName());
            }

            void InteriorsExplorerModel::PublishInteriorExplorerStateChange()
            {
                
                int floor = m_controller.InteriorInScene() ? m_controller.GetCurrentFloorIndex() : 0;
                
                std::string floorName;
                std::vector<std::string> floorShortNames;
                
                if (m_controller.InteriorInScene())
                {
                    const Eegeo::Resources::Interiors::InteriorsModel* pModel = NULL;
                    m_controller.TryGetCurrentModel(pModel);
                    
                    Eegeo_ASSERT(pModel != NULL, "Couldn't get current model for interior");
                    const Eegeo::Resources::Interiors::TFloorModelVector& floorModels = pModel->GetFloors();
                    
                    std::transform(floorModels.begin(), floorModels.end(), std::back_inserter(floorShortNames), ToFloorName);
                    
                    const Eegeo::Resources::Interiors::InteriorsFloorModel* pFloorModel = NULL;
                    Eegeo_ASSERT(m_controller.TryGetCurrentFloorModel(pFloorModel), "Could not fetch current floor model");
                    floorName = pFloorModel->GetReadableFloorName();
                }
                
                m_messageBus.Publish(InteriorsExplorerStateChangedMessage(m_interiorExplorerEnabled,
                                                                          floor,
                                                                          floorName,
                                                                          floorShortNames));
            }
            
            void InteriorsExplorerModel::InsertInteriorExplorerExitedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_interiorExplorerExitedCallbacks.AddCallback(callback);
            }
            void InteriorsExplorerModel::RemoveInteriorExplorerExitedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_interiorExplorerExitedCallbacks.RemoveCallback(callback);
            }
        }
    }
}
