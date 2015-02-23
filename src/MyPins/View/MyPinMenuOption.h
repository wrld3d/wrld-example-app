// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "IMenuOption.h"
#include "MyPinModel.h"
#include "BidirectionalBus.h"
#include "MyPinSelectedMessage.h"
#include "IMenuViewModel.h"

#include <string>

namespace ExampleApp
{
    namespace MyPins
    {
        namespace View
        {
            class MyPinMenuOption : public Menu::View::IMenuOption
            {
            public:
                MyPinMenuOption(SdkModel::MyPinModel myPinModel,
                                Menu::View::IMenuViewModel& menuViewModel,
                                ExampleAppMessaging::TMessageBus& messageBus)
                    : m_myPinModel(myPinModel)
                    , m_menuViewModel(menuViewModel)
                    , m_messageBus(messageBus)
                {

                }

                void Select()
                {
                    m_menuViewModel.Close();
                    m_messageBus.Publish(MyPinSelectedMessage(m_myPinModel));
                }
            private:
                SdkModel::MyPinModel m_myPinModel;
                Menu::View::IMenuViewModel& m_menuViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
            };
        }
    }
}
