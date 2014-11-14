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
                                       ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
            : m_myPinCreationModel(myPinCreationModel)
            , m_nativeToUiMessageBus(nativeToUiMessageBus)
            , m_callback(this, &MyPinCreationModelObserver::HandlePoiCreationModelStateChange)
            {
                m_myPinCreationModel.AddStateChangedCallback(m_callback);
            }
            
            ~MyPinCreationModelObserver()
            {
                m_myPinCreationModel.RemoveStateChangedCallback(m_callback);
            }
        
        private:
            IMyPinCreationModel& m_myPinCreationModel;
            ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
            
            Eegeo::Helpers::TCallback1<MyPinCreationModelObserver, MyPinCreationStage> m_callback;
            
            void HandlePoiCreationModelStateChange(MyPinCreationStage& stage)
            {
                m_nativeToUiMessageBus.Publish(MyPinCreationStateChangedMessage(stage));
            }
        };
    }
}
