// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinSelectionHandler.h"
#include "MyPinDetailsModelSelectedMessage.h"

namespace ExampleApp
{
    namespace MyPins
    {
        MyPinSelectionHandler::MyPinSelectionHandler(MyPinModel& myPinModel,
                                                     ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
        : m_myPinModel(myPinModel)
        , m_nativeToUiMessageBus(nativeToUiMessageBus)
        {
            
        }
            
        void MyPinSelectionHandler::SelectPin()
        {
            m_nativeToUiMessageBus.Publish(MyPinDetails::MyPinDetailsModelSelectedMessage(m_myPinModel));
        }
    }
}