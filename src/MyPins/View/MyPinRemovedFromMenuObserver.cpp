// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinRemovedFromMenuObserver.h"
#include "IMenuOptionsModel.h"
#include "MyPinsHelpers.h"

namespace ExampleApp
{
    namespace MyPins
    {
       
        MyPinRemovedFromMenuObserver::MyPinRemovedFromMenuObserver(Menu::IMenuOptionsModel& menuOptionsModel,
                                     ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
        : m_menuOptionsModel(menuOptionsModel)
        , m_nativeToUiMessageBus(nativeToUiMessageBus)
        , m_handlerBinding(this, &MyPinRemovedFromMenuObserver::HandleReceivedMyRemovedFromMenuMessage)
        {
            m_nativeToUiMessageBus.Subscribe(m_handlerBinding);
        }
        
        MyPinRemovedFromMenuObserver::~MyPinRemovedFromMenuObserver()
        {
            m_nativeToUiMessageBus.Unsubscribe(m_handlerBinding);
        }
    
        void MyPinRemovedFromMenuObserver::HandleReceivedMyRemovedFromMenuMessage(const MyPinRemovedFromMenuMessage& message)
        {
            MyPinModel* myPinModel = message.GetMyPinModel();
            m_menuOptionsModel.RemoveItem(ConvertModelDetailToString(myPinModel->Identifier()));
        }
    }
}
