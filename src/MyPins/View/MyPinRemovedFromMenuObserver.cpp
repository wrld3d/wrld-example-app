// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinRemovedFromMenuObserver.h"
#include "IMenuOptionsModel.h"
#include "MyPinsHelpers.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace View
        {
            MyPinRemovedFromMenuObserver::MyPinRemovedFromMenuObserver(Menu::View::IMenuOptionsModel& menuOptionsModel,
                    ExampleAppMessaging::TMessageBus& messageBus)
                : m_menuOptionsModel(menuOptionsModel)
                , m_messageBus(messageBus)
                , m_handlerBinding(this, &MyPinRemovedFromMenuObserver::OnMyRemovedFromMenuMessage)
            {
                m_messageBus.SubscribeUi(m_handlerBinding);
            }

            MyPinRemovedFromMenuObserver::~MyPinRemovedFromMenuObserver()
            {
                m_messageBus.UnsubscribeUi(m_handlerBinding);
            }

            void MyPinRemovedFromMenuObserver::OnMyRemovedFromMenuMessage(const MyPinRemovedFromMenuMessage& message)
            {
                m_menuOptionsModel.RemoveItem(ConvertModelDetailToString(message.GetMyPinId()));
            }
        }
    }
}
