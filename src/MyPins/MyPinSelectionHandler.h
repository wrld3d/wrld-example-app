// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IWorldPinSelectionHandler.h"
#include "MyPinModel.h"
#include "NativeToUiMessageBus.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinSelectionHandler : public WorldPins::IWorldPinSelectionHandler
        {
        private:
            MyPinModel& m_myPinModel;
            ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
            
        public:
            MyPinSelectionHandler(MyPinModel& myPinModel,
                                  ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);
            
            void SelectPin();
        };
    }
}