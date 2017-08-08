// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerModel.h"
#include "InteriorsExplorerStateChangedMessage.h"
#include "InteriorsExplorerFloorSelectedMessage.h"

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
#include "InteriorInteractionModel.h"

#include "ICameraTransitionController.h"
#include "IPersistentSettingsModel.h"

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
				const std::string InteriorExitTutorialViewedCount = "InteriorsExplorerModel_InteriorExitTutorialViewedCount";
				const std::string InteriorChangeFloorTutorialViewedCount = "InteriorsExplorerModel_InteriorChangeFloorTutorialViewedCount";
                
                std::string ToFloorName(const Eegeo::Resources::Interiors::InteriorsFloorModel* pFloorModel)
                {
                    return pFloorModel->GetFloorName();
                }
            }
            
            InteriorsExplorerModel::InteriorsExplorerModel(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                           Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                           VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                           ExampleAppMessaging::TMessageBus& messageBus,
                                                           Metrics::IMetricsService& metricsService,
                                                           PersistentSettings::IPersistentSettingsModel& persistentSettings)
            : m_interiorInteractionModel(interiorInteractionModel)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_visualMapService(visualMapService)
            , m_messageBus(messageBus)
            , m_metricsService(metricsService)
            , m_interactionModelStateChangedCallback(this, &InteriorsExplorerModel::HandleInteractionModelStateChanged)
            , m_exitCallback(this, &InteriorsExplorerModel::OnExit)
            , m_selectFloorCallback(this, &InteriorsExplorerModel::OnSelectFloor)
            , m_floorSelectionDraggedCallback(this, &InteriorsExplorerModel::OnFloorSelectionDragged)
            , m_interiorExplorerEnabled(false)
            , m_currentInteriorFloorIndex(0)
            , m_persistentSettings(persistentSettings)
            , m_interiorExitTutorialViewedCount(0)
			, m_interiorChangeFloorTutorialViewedCount(0)
            , m_lastEntryAttemptSuccessful(false)
            {
                m_interiorInteractionModel.RegisterInteractionStateChangedCallback(m_interactionModelStateChangedCallback);
                
                m_messageBus.SubscribeNative(m_exitCallback);
                m_messageBus.SubscribeNative(m_selectFloorCallback);
                m_messageBus.SubscribeNative(m_floorSelectionDraggedCallback);
            }
            
            InteriorsExplorerModel::~InteriorsExplorerModel()
            {
                m_messageBus.UnsubscribeNative(m_floorSelectionDraggedCallback);
                m_messageBus.UnsubscribeNative(m_selectFloorCallback);
                m_messageBus.UnsubscribeNative(m_exitCallback);

                m_interiorInteractionModel.UnregisterInteractionStateChangedCallback(m_interactionModelStateChangedCallback);
            }

            void InteriorsExplorerModel::ChangeToInteriorMapState()
            {
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
                Eegeo_ASSERT(m_interiorInteractionModel.HasInteriorModel(), "Can't show interior explorer without a selected and streamed interior");
                
				if(!fromAnotherInterior)
				{
					m_interiorExitTutorialViewedCount = 0;

					if(!m_persistentSettings.TryGetValue(InteriorExitTutorialViewedCount, m_interiorExitTutorialViewedCount))
					{
						m_interiorExitTutorialViewedCount = 0;
					}

					m_interiorChangeFloorTutorialViewedCount = 0;

					if(!m_persistentSettings.TryGetValue(InteriorChangeFloorTutorialViewedCount, m_interiorChangeFloorTutorialViewedCount))
					{
						m_interiorChangeFloorTutorialViewedCount = 0;
					}
				}

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
                    m_interiorExplorerEnteredCallbacks.ExecuteCallbacks();
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
            
            int InteriorsExplorerModel::GetInteriorExitTutorialViewedCount()
            {
                return m_interiorExitTutorialViewedCount;
            }
            
            void InteriorsExplorerModel::RecordHasViewedInteriorExitTutorial()
            {
                ++m_interiorExitTutorialViewedCount;
            }

			int InteriorsExplorerModel::GetInteriorChangeFloorTutorialViewedCount()
			{
				return m_interiorChangeFloorTutorialViewedCount;
			}

			void InteriorsExplorerModel::RecordHasViewedInteriorChangeFloorTutorial()
			{
				++m_interiorChangeFloorTutorialViewedCount;
			}
            
           
            void InteriorsExplorerModel::HandleInteractionModelStateChanged()
            {
                if (!m_interiorExplorerEnabled)
                {
                    return;
                }
                
                if (!m_interiorInteractionModel.HasInteriorModel())
                {
                    return;
                }
                
                const Eegeo::Resources::Interiors::InteriorsFloorModel* pFloorModel = m_interiorInteractionModel.GetSelectedFloorModel();
                Eegeo_ASSERT(pFloorModel, "Could not fetch current floor model");
                
                if(m_currentInteriorFloorIndex != m_interiorInteractionModel.GetSelectedFloorIndex())
                {
                	m_currentInteriorFloorIndex = m_interiorInteractionModel.GetSelectedFloorIndex();
                    m_messageBus.Publish(InteriorsExplorerFloorSelectedMessage(m_interiorInteractionModel.GetSelectedFloorIndex(), pFloorModel->GetReadableFloorName()));
                }

            }
            
        
            void InteriorsExplorerModel::OnExit(const InteriorsExplorerExitMessage& message)
            {
                Exit();
            }
            
            void InteriorsExplorerModel::Exit()
            {

                if(m_interiorExplorerEnabled)
                {
                    m_persistentSettings.SetValue(InteriorExitTutorialViewedCount, m_interiorExitTutorialViewedCount);
                    m_persistentSettings.SetValue(InteriorChangeFloorTutorialViewedCount, m_interiorChangeFloorTutorialViewedCount);

                    HideInteriorExplorer();
                    m_metricsService.SetEvent(MetricEventInteriorExitPressed);
                    m_interiorExplorerExitedCallbacks.ExecuteCallbacks();
                }
            }
            
            void InteriorsExplorerModel::OnSelectFloor(const InteriorsExplorerSelectFloorMessage &message)
            {
                SelectFloor(message.GetFloor());
            }
            
            void InteriorsExplorerModel::OnFloorSelectionDragged(const InteriorsExplorerFloorSelectionDraggedMessage &message)
            {
                const Eegeo::Resources::Interiors::InteriorsModel* pModel = m_interiorInteractionModel.GetInteriorModel();
                Eegeo_ASSERT(pModel, "Could not fetch current model");
                
                const float dragParameter = Eegeo::Math::Clamp01(message.GetDragParam());
                const float floorParam = dragParameter * (pModel->GetFloorCount()-1);

                const bool shouldEnterExpandedMode = m_interiorInteractionModel.IsCollapsed() || m_interiorInteractionModel.IsExitingExpanded();
                if (shouldEnterExpandedMode)
                {
                    m_interiorInteractionModel.ToggleExpanded();
                }
                m_interiorInteractionModel.SetFloorParam(floorParam);
                
                const int nearestFloorIndex = static_cast<int>(roundf(floorParam));
                const Eegeo::Resources::Interiors::InteriorsFloorModel& floorModel = pModel->GetFloorAtIndex(nearestFloorIndex);
                m_messageBus.Publish(InteriorsExplorerFloorSelectedMessage(nearestFloorIndex, floorModel.GetReadableFloorName()));
                
                m_interiorExplorerFloorSelectionDraggedCallbacks.ExecuteCallbacks();
            }

            void InteriorsExplorerModel::SelectFloor(int floor)
            {
                if (!m_interiorInteractionModel.HasInteriorModel())
                {
                    return;
                }
                
                const bool shouldExitExpandedMode = m_interiorInteractionModel.IsFullyExpanded() || m_interiorInteractionModel.IsEnteringExpanded();
                if (shouldExitExpandedMode)
                {
                    m_interiorInteractionModel.ToggleExpanded();
                }
                
                if (m_interiorInteractionModel.GetSelectedFloorIndex() == floor)
                {
                    return;
                }
                
                m_interiorInteractionModel.SetSelectedFloorIndex(floor);
                
                const Eegeo::Resources::Interiors::InteriorsFloorModel* pFloorModel = m_interiorInteractionModel.GetSelectedFloorModel();
                Eegeo_ASSERT(pFloorModel, "Could not fetch current floor model");

                m_metricsService.SetEvent(MetricEventInteriorFloorSelected, "InteriorId", m_interiorSelectionModel.GetSelectedInteriorId().Value(), "FloorName", pFloorModel->GetFloorName());
            }

            void InteriorsExplorerModel::PublishInteriorExplorerStateChange()
            {
            	m_currentInteriorFloorIndex = m_interiorInteractionModel.GetSelectedFloorIndex();

                std::string floorName;
                std::vector<std::string> floorShortNames;
                
                if (m_interiorInteractionModel.HasInteriorModel())
                {
                    const Eegeo::Resources::Interiors::InteriorsModel* pModel = m_interiorInteractionModel.GetInteriorModel();
                    Eegeo_ASSERT(pModel != NULL, "Couldn't get current model for interior");
                    const Eegeo::Resources::Interiors::TFloorModelVector& floorModels = pModel->GetFloors();
                    
                    std::transform(floorModels.begin(), floorModels.end(), std::back_inserter(floorShortNames), ToFloorName);
                    
                    const Eegeo::Resources::Interiors::InteriorsFloorModel* pFloorModel = m_interiorInteractionModel.GetSelectedFloorModel();
                    Eegeo_ASSERT(pFloorModel, "Could not fetch current floor model");
                    floorName = pFloorModel->GetReadableFloorName();
                }
                
                m_messageBus.Publish(InteriorsExplorerStateChangedMessage(m_interiorExplorerEnabled,
                														  m_currentInteriorFloorIndex,
                                                                          floorName,
                                                                          floorShortNames));
            }
            
            void InteriorsExplorerModel::InsertInteriorExplorerEnteredCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_interiorExplorerEnteredCallbacks.AddCallback(callback);
            }
            void InteriorsExplorerModel::RemoveInteriorExplorerEnteredCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_interiorExplorerEnteredCallbacks.RemoveCallback(callback);
            }
            
            void InteriorsExplorerModel::InsertInteriorExplorerExitedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_interiorExplorerExitedCallbacks.AddCallback(callback);
            }
            void InteriorsExplorerModel::RemoveInteriorExplorerExitedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_interiorExplorerExitedCallbacks.RemoveCallback(callback);
            }
            
            void InteriorsExplorerModel::InsertInteriorExplorerFloorSelectionDraggedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_interiorExplorerFloorSelectionDraggedCallbacks.AddCallback(callback);
            }
            
            void InteriorsExplorerModel::RemoveInteriorExplorerFloorSelectionDraggedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_interiorExplorerFloorSelectionDraggedCallbacks.RemoveCallback(callback);
            }
            
            void InteriorsExplorerModel::SetLastEntryAttemptSuccessful(bool successful)
            {
                m_lastEntryAttemptSuccessful = successful;
            }
            
            bool InteriorsExplorerModel::GetLastEntryAttemptSuccessful() const
            {
                return m_lastEntryAttemptSuccessful;
            }
            
            bool InteriorsExplorerModel::IsEnabled() const
            {
                return m_interiorExplorerEnabled;
            }

        }
    }
}
