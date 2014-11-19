// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "Menu.h"
#include "ICallback.h"
#include "UiToNativeMessageBus.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinsRepositoryObserver
        {
        public:
            typedef MyPinModel* TModel;
            
            MyPinsRepositoryObserver(MyPinsRepository& myPinsRepository,
                                     MyPinsFileIO& myPinsFileIO,
                                     Menu::IMenuOptionsModel& menuOptionsModel,
                                     Menu::IMenuViewModel& menuViewModel,
                                     ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);
            
            ~MyPinsRepositoryObserver();

        private:
            MyPinsRepository& m_myPinsRepository;
            MyPinsFileIO& m_myPinsFileIO;
            Menu::IMenuOptionsModel& m_menuOptionsModel;
            Menu::IMenuViewModel& m_menuViewModel;
            ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
            
            Eegeo::Helpers::TCallback1<MyPinsRepositoryObserver, MyPinModel*> m_pinAddedCallback;
            Eegeo::Helpers::TCallback1<MyPinsRepositoryObserver, MyPinModel*> m_pinRemovedCallback;
            
            void HandlePinAddedToRepository(MyPinModel*& myPinModel);
            void HandlePinRemovedFromRepository(MyPinModel*& myPinModel);
        };
    }
}