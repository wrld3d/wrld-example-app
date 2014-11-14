// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "IMenuOption.h"
#include "MyPinModel.h"
#include "UiToNativeMessageBus.h"
#include "PlaceJumpsModel.h"
#include "PlaceJumpSelectedMessage.h"
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
                
                std::string name = m_myPinModel.GetTitle();
                std::string dummy = "";
                
                PlaceJumps::PlaceJumpModel placeJumpModel(name,
                                                          m_myPinModel.GetLatLong(),
                                                          0.f,
                                                          1500.f,
                                                          dummy);
                
                m_uiToNativeMessageBus.Publish(PlaceJumps::PlaceJumpSelectedMessage(placeJumpModel));
            }
        private:
            MyPinModel m_myPinModel;
            ExampleApp::Menu::IMenuViewModel& m_menuViewModel;
            ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
        };
    }
}