// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMyPinSelectionHandlerFactory.h"
#include "MyPins.h"
#include "NativeToUiMessageBus.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinSelectionHandlerFactory : public IMyPinSelectionHandlerFactory
        {
        private:
            ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
            
        public:
            MyPinSelectionHandlerFactory(ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);
            
            MyPinSelectionHandler* CreateMyPinSelectionHandler(MyPinModel& myPinModel) const;
        };
    }
}