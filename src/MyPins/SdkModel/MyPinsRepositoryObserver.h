// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "Menu.h"
#include "ICallback.h"
#include "BidirectionalBus.h"
#include "Types.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinsRepositoryObserver : private Eegeo::NonCopyable
            {
            public:
                typedef MyPinModel* TModel;

                MyPinsRepositoryObserver(const std::shared_ptr<IMyPinsRepository>& myPinsRepository,
                                         const std::shared_ptr<IMyPinBoundObjectRepository>& myPinBoundObjectRepository,
                                         const std::shared_ptr<MyPinsFileIO>& myPinsFileIO,
                                         const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~MyPinsRepositoryObserver();

            private:
                const std::shared_ptr<IMyPinsRepository> m_myPinsRepository;
                const std::shared_ptr<IMyPinBoundObjectRepository> m_myPinBoundObjectRepository;
                const std::shared_ptr<MyPinsFileIO> m_myPinsFileIO;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;

                Eegeo::Helpers::TCallback1<MyPinsRepositoryObserver, MyPinModel*> m_pinAddedCallback;
                Eegeo::Helpers::TCallback1<MyPinsRepositoryObserver, MyPinModel*> m_pinRemovedCallback;

                void HandlePinAddedToRepository(MyPinModel*& myPinModel);
                void HandlePinRemovedFromRepository(MyPinModel*& myPinModel);
            };
        }
    }
}
