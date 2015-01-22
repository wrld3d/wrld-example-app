// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "Menu.h"
#include "ICallback.h"
#include "NativeToUiMessageBus.h"

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
                                     ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);
            
            ~MyPinsRepositoryObserver();

        private:
            MyPinsRepository& m_myPinsRepository;
            MyPinsFileIO& m_myPinsFileIO;
            ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;

            Eegeo::Helpers::TCallback1<MyPinsRepositoryObserver, MyPinModel*> m_pinAddedCallback;
            Eegeo::Helpers::TCallback1<MyPinsRepositoryObserver, MyPinModel*> m_pinRemovedCallback;
            
            void HandlePinAddedToRepository(MyPinModel*& myPinModel);
            void HandlePinRemovedFromRepository(MyPinModel*& myPinModel);
        };
    }
}
