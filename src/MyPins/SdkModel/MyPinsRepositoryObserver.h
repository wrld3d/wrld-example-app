// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "Menu.h"
#include "ICallback.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinsRepositoryObserver
            {
            public:
                typedef MyPinModel* TModel;

                MyPinsRepositoryObserver(MyPinsRepository& myPinsRepository,
                                         IMyPinBoundObjectRepository& myPinBoundObjectRepository,
                                         MyPinsFileIO& myPinsFileIO,
                                         ExampleAppMessaging::TMessageBus& messageBus);

                ~MyPinsRepositoryObserver();

            private:
                MyPinsRepository& m_myPinsRepository;
                IMyPinBoundObjectRepository& m_myPinBoundObjectRepository;
                MyPinsFileIO& m_myPinsFileIO;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback1<MyPinsRepositoryObserver, MyPinModel*> m_pinAddedCallback;
                Eegeo::Helpers::TCallback1<MyPinsRepositoryObserver, MyPinModel*> m_pinRemovedCallback;

                void HandlePinAddedToRepository(MyPinModel*& myPinModel);
                void HandlePinRemovedFromRepository(MyPinModel*& myPinModel);
            };
        }
    }
}
