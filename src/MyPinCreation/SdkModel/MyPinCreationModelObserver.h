// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "NativeToUiMessageBus.h"
#include "ICallback.h"
#include "IMyPinCreationModel.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class MyPinCreationModelObserver : public Eegeo::NonCopyable
        {
        public:
            MyPinCreationModelObserver(IMyPinCreationModel& myPinCreationModel,
                                       ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);
            
            ~MyPinCreationModelObserver();
        
        private:
            IMyPinCreationModel& m_myPinCreationModel;
            ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
            
            Eegeo::Helpers::TCallback1<MyPinCreationModelObserver, MyPinCreationStage> m_callback;
            
            void HandlePoiCreationModelStateChange(MyPinCreationStage& stage);
        };
    }
}
