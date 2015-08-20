// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerModel.h"
#include "InteriorsController.h"
#include "InteriorsExplorerStateChangedMessage.h"
#include "InteriorsExplorerFloorSelectedMessage.h"

#include "InteriorsModel.h"
#include "InteriorsFloorModel.h"
#include "InteriorSelectionModel.h"
#include "IMapModeModel.h"
#include "IMetricsService.h"

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
                
                
                void GetFloorNumberList(Eegeo::Resources::Interiors::InteriorsController& interiorsController,
                                        std::vector<int>& out_floorNumbers)
                {
                    out_floorNumbers.clear();
                    
                    const Eegeo::Resources::Interiors::InteriorsModel* pModel = NULL;
                    interiorsController.TryGetCurrentModel(pModel);
                    
                    Eegeo_ASSERT(pModel != NULL, "Couldn't get current model for interior");

                    out_floorNumbers.reserve(pModel->GetFloorCount());
                    
                    const Eegeo::Resources::Interiors::TFloorModelVector& floors = pModel->GetFloors();
                    for (Eegeo::Resources::Interiors::TFloorModelVector::const_reverse_iterator rit = floors.rbegin(); rit != floors.rend(); ++rit)
                    {

                        // Floor numbers currently match Micello's 'z-level', which starts at 0 for ground floor.
                        // However, Micello's names follow US conventions, with ground floor being 1.
                        // Incrementing floor numbers by one so that the z-level and names visually match in UI.
                        int floorNumber = (*rit)->GetFloorNumber();
                        if (floorNumber >= 0)
                        {
                            ++floorNumber;
                        }
                        
                        out_floorNumbers.push_back(floorNumber);
                    }
                    
                }
            }
            
            InteriorsExplorerModel::InteriorsExplorerModel(Eegeo::Resources::Interiors::InteriorsController& controller,
                                                           Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                           MapMode::SdkModel::IMapModeModel& mapModeModel,
                                                           ExampleAppMessaging::TMessageBus& messageBus,
                                                           Metrics::IMetricsService& metricsService)
            : m_controller(controller)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_mapModeModel(mapModeModel)
            , m_messageBus(messageBus)
            , m_metricsService(metricsService)
            , m_controllerStateChangedCallback(this, &InteriorsExplorerModel::OnControllerStateChanged)
            , m_exitCallback(this, &InteriorsExplorerModel::OnExit)
            , m_selectFloorCallback(this, &InteriorsExplorerModel::OnSelectFloor)
            , m_interiorSelectionModelChangedCallback(this, &InteriorsExplorerModel::OnInteriorSelectionModelChanged)
            , m_previouslyInMapMode(false)
            {
                m_controller.RegisterStateChangedCallback(m_controllerStateChangedCallback);
                m_interiorSelectionModel.RegisterSelectionChangedCallback(m_interiorSelectionModelChangedCallback);
                
                m_messageBus.SubscribeNative(m_exitCallback);
                m_messageBus.SubscribeNative(m_selectFloorCallback);
            }
            
            InteriorsExplorerModel::~InteriorsExplorerModel()
            {
                m_messageBus.UnsubscribeNative(m_selectFloorCallback);
                m_messageBus.UnsubscribeNative(m_exitCallback);

                m_interiorSelectionModel.UnregisterSelectionChangedCallback(m_interiorSelectionModelChangedCallback);
                m_controller.UnregisterStateChangedCallback(m_controllerStateChangedCallback);
            }
            
            void InteriorsExplorerModel::OnControllerStateChanged()
            {
                int floor = m_controller.ShowingInterior() ? m_controller.GetCurrentFloorIndex() : 0;
                
                std::string floorName;
                std::vector<int> floorNumbers;

                if (m_controller.ShowingInterior())
                {
                    GetFloorNumberList(m_controller, floorNumbers);
                    floorName = m_controller.GetCurrentFloorModel().GetFloorName();
                }
                
                m_messageBus.Publish(InteriorsExplorerStateChangedMessage(m_controller.ShowingInterior(),
                                                                          floor,
                                                                          floorName,
                                                                          floorNumbers));
            }
        
            void InteriorsExplorerModel::OnExit(const InteriorsExplorerExitMessage& message)
            {
                m_metricsService.SetEvent(MetricEventInteriorExitPressed);
                m_controller.ExitInterior();
            }
            
            void InteriorsExplorerModel::OnSelectFloor(const InteriorsExplorerSelectFloorMessage &message)
            {
                SelectFloor(message.GetFloor());
            }

            void InteriorsExplorerModel::SelectFloor(int floor)
            {
                m_controller.SelectFloorAtIndex(floor);
                const Eegeo::Resources::Interiors::InteriorsFloorModel& currentFloor = m_controller.GetCurrentFloorModel();
                
                m_messageBus.Publish(InteriorsExplorerFloorSelectedMessage(m_controller.GetCurrentFloorIndex(), currentFloor.GetFloorName()));

                m_metricsService.SetEvent(MetricEventInteriorFloorSelected, "InteriorId", m_interiorSelectionModel.GetSelectedInteriorId().Value(), "FloorName", currentFloor.GetFloorName());
            }

            void InteriorsExplorerModel::OnInteriorSelectionModelChanged(const Eegeo::Resources::Interiors::InteriorId& previousInteriorId)
            {
                if (m_interiorSelectionModel.IsInteriorSelected())
                {
                    m_previouslyInMapMode = m_mapModeModel.IsInMapMode();
                    m_mapModeModel.SetInMapMode(false);
                    m_metricsService.BeginTimedEvent(MetricEventInteriorsVisible);
                    
                    const Eegeo::Resources::Interiors::InteriorId& interiorId = m_interiorSelectionModel.GetSelectedInteriorId();
                    m_metricsService.SetEvent(MetricEventInteriorSelected, "InteriorId", interiorId.Value());
                }
                else
                {
                    m_mapModeModel.SetInMapMode(m_previouslyInMapMode);
                    m_metricsService.EndTimedEvent(MetricEventInteriorsVisible);
                }
            }
        }
    }
}