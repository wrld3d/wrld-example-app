// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinSelectionHandlerFactory.h"
#include "MyPinSelectionHandler.h"

namespace ExampleApp
{
    namespace MyPins
    {

        MyPinSelectionHandlerFactory::MyPinSelectionHandlerFactory(ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
        : m_nativeToUiMessageBus(nativeToUiMessageBus)
        {
            
        }
            
        MyPinSelectionHandler* MyPinSelectionHandlerFactory::CreateMyPinSelectionHandler(MyPinModel& myPinModel) const
        {
            return Eegeo_NEW(MyPinSelectionHandler)(myPinModel, m_nativeToUiMessageBus);
        }
    }
}