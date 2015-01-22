// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationModelObserver.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace SdkModel
        {
            MyPinCreationModelObserver::MyPinCreationModelObserver(IMyPinCreationModel& myPinCreationModel,
                    ExampleAppMessaging::TMessageBus& messageBus)
                : m_myPinCreationModel(myPinCreationModel)
                , m_messageBus(messageBus)
                , m_callback(this, &MyPinCreationModelObserver::HandlePoiCreationModelStateChange)
            {
                m_myPinCreationModel.InsertStateChangedCallback(m_callback);
            }

            MyPinCreationModelObserver::~MyPinCreationModelObserver()
            {
                m_myPinCreationModel.RemoveStateChangedCallback(m_callback);
            }

            void MyPinCreationModelObserver::HandlePoiCreationModelStateChange(MyPinCreationStage& stage)
            {
                m_messageBus.Publish(MyPinCreationStateChangedMessage(stage));
            }
        }
    }
}
