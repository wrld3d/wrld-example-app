// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationInitiationView.h"
#include "ICallback.h"
#include "AndroidNativeState.h"
#include "MyPinCreation.h"
#include "MyPinCreationViewIncludes.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationInitiationView: public IMyPinCreationInitiationView
            {
            public:
                MyPinCreationInitiationView(AndroidNativeState& nativeState);
                ~MyPinCreationInitiationView();

                void OnSelected();
                void ShouldOffsetButton(bool shouldOffset);
                void InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback);

                void SetOnScreenStateToIntermediateValue(float value);
                void SetFullyOnScreen();
                void SetFullyOffScreen();

            private:

                AndroidNativeState& m_nativeState;

                jclass m_uiViewClass;
                jobject m_uiView;

                Eegeo::Helpers::CallbackCollection0 m_callbacks;
            };
        }
    }
}
