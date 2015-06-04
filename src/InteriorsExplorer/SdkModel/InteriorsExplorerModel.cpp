// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerModel.h"
#include "InteriorsController.h"
#include "InteriorsExplorerStateChangedMessage.h"
#include "InteriorsExplorerFloorSelectedMessage.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorsExplorerModel::InteriorsExplorerModel(Eegeo::Resources::Interiors::InteriorsController& controller,
                                                           ExampleAppMessaging::TMessageBus& messageBus)
            : m_controller(controller)
            , m_messageBus(messageBus)
            , m_controllerStateChangedCallback(this, &InteriorsExplorerModel::OnControllerStateChanged)
            , m_exitCallback(this, &InteriorsExplorerModel::OnExit)
            , m_selectFloorCallback(this, &InteriorsExplorerModel::OnSelectFloor)
            {
                m_controller.RegisterStateChangedCallback(m_controllerStateChangedCallback);
                
                m_messageBus.SubscribeNative(m_exitCallback);
                m_messageBus.SubscribeNative(m_selectFloorCallback);
            }
            
            InteriorsExplorerModel::~InteriorsExplorerModel()
            {
                m_messageBus.UnsubscribeNative(m_selectFloorCallback);
                m_messageBus.UnsubscribeNative(m_exitCallback);
                
                m_controller.UnregisterStateChangedCallback(m_controllerStateChangedCallback);
            }
            
            void InteriorsExplorerModel::OnControllerStateChanged()
            {
                int floorCount = m_controller.ShowingInterior() ? m_controller.GetFloorCount() : 0;
                int floor = m_controller.ShowingInterior() ? m_controller.GetCurrentFloorNumber() : 0;
                m_messageBus.Publish(InteriorsExplorerStateChangedMessage(m_controller.ShowingInterior(),
                                                                          floorCount,
                                                                          floor));
            }
            
            void InteriorsExplorerModel::OnExit(const InteriorsExplorerExitMessage& message)
            {
                m_controller.ExitInterior();
            }
            
            void InteriorsExplorerModel::OnSelectFloor(const InteriorsExplorerSelectFloorMessage &message)
            {
                SelectFloor(message.GetFloor());
            }
            
            void InteriorsExplorerModel::Exit()
            {
                m_controller.ExitInterior();
            }
            
            void InteriorsExplorerModel::SelectFloor(int floor)
            {
                m_controller.SelectFloor(floor);
                m_messageBus.Publish(InteriorsExplorerFloorSelectedMessage(m_controller.GetCurrentFloorNumber()));
            }
        }
    }
}