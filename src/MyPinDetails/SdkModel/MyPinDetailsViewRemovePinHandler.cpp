// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinDetailsViewRemovePinHandler.h"
#include "MyPinsService.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        MyPinDetailsViewRemovePinHandler::MyPinDetailsViewRemovePinHandler(MyPins::IMyPinsService& myPinsService,
                                                                           ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
        : m_myPinsService(myPinsService)
        , m_uiToNativeMessageBus(uiToNativeMessageBus)
        , m_handler(this, &MyPinDetailsViewRemovePinHandler::OnMyPinCreationViewSavePinMessageReceived)
        {
            m_uiToNativeMessageBus.Subscribe(m_handler);
        }
            
        MyPinDetailsViewRemovePinHandler::~MyPinDetailsViewRemovePinHandler()
        {
            m_uiToNativeMessageBus.Unsubscribe(m_handler);
        }
        
            
        void MyPinDetailsViewRemovePinHandler::OnMyPinCreationViewSavePinMessageReceived(const MyPinDetailsViewRemovePinMessage& message)
        {
            m_myPinsService.RemovePinWithId(message.GetMyPinModelId());
        }
    }
}
