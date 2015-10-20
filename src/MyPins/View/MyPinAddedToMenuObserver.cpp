// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include "MyPinAddedToMenuObserver.h"
#include "MyPinsHelpers.h"
#include "IMenuOptionsModel.h"
#include "MyPinModel.h"
#include "MyPinMenuOption.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace View
        {
            MyPinAddedToMenuObserver::MyPinAddedToMenuObserver(Menu::View::IMenuViewModel& menuViewModel,
                                                               Menu::View::IMenuOptionsModel& menuOptionsModel,
                                                               ExampleAppMessaging::TMessageBus& messageBus)
                : m_menuViewModel(menuViewModel)
                , m_menuOptionsModel(menuOptionsModel)
                , m_messageBus(messageBus)
                , m_handlerBinding(this, &MyPinAddedToMenuObserver::OnMyPinAddedToMenuMessage)
            {
                m_messageBus.SubscribeUi(m_handlerBinding);
            }

            MyPinAddedToMenuObserver::~MyPinAddedToMenuObserver()
            {
                m_messageBus.UnsubscribeUi(m_handlerBinding);
            }

            void MyPinAddedToMenuObserver::OnMyPinAddedToMenuMessage(const MyPinAddedToMenuMessage& message)
            {
                const std::string& myPinIcon(message.GetMyPinIcon());

                m_menuOptionsModel.AddItem(ConvertModelDetailToString(message.GetMyPinId()),
                                           message.GetMyPinTitle(),
                                           "",
                                           myPinIcon,
                                           Eegeo_NEW(MyPinMenuOption)(message.GetMyPinId(),
                                                                      message.GetMyPinLocation(),
                                                                      message.GetMyPinInteriorId(),
                                                                      message.GetMyPinFloorIndex(),
                                                                      m_menuViewModel,
                                                                      m_messageBus));
            }
        }
    }
}
