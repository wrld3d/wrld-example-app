// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "IMenuOption.h"
#include "MyPinModel.h"
#include "UiToNativeMessageBus.h"
#include "MyPinSelectedMessage.h"
#include "IMenuViewModel.h"

#include <string>

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinMenuOption : public Menu::IMenuOption
        {
        public:
            MyPinMenuOption(MyPinModel myPinModel,
                            ExampleApp::Menu::IMenuViewModel& menuViewModel,
                            ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
            : m_myPinModel(myPinModel)
            , m_menuViewModel(menuViewModel)
            , m_uiToNativeMessageBus(uiToNativeMessageBus)
            {
                
            }
            
            void Select()
            {
                m_menuViewModel.Close();
                m_uiToNativeMessageBus.Publish(MyPinSelectedMessage(m_myPinModel));
            }
        private:
            MyPinModel m_myPinModel;
            ExampleApp::Menu::IMenuViewModel& m_menuViewModel;
            ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
        };
    }
}