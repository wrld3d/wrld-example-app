// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationInitiationView.h"
#include "ICallback.h"
#include "WindowsNativeState.h"
#include "MyPinCreation.h"
#include "MyPinCreationViewIncludes.h"
#include "CallbackCollection.h"

#include "ReflectionHelpers.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationInitiationView: public IMyPinCreationInitiationView
            {
            public:
                MyPinCreationInitiationView(WindowsNativeState& nativeState);
                ~MyPinCreationInitiationView();

                void OnSelected();
                void ShouldOffsetButton(bool shouldOffset);
                void InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback);

                void SetOnScreenStateToIntermediateValue(float value);
                void SetFullyOnScreen();
                void SetFullyOffScreen();

            private:
                Helpers::ReflectionHelpers::Method<void> mDestroy;
                Helpers::ReflectionHelpers::Method<void> mAnimateToInactive;
                Helpers::ReflectionHelpers::Method<void> mAnimateToActive;
                Helpers::ReflectionHelpers::Method<float> mAnimateToIntermediateOnScreenState;
                Helpers::ReflectionHelpers::Method<bool> mShouldOffsetButtonCSharp;

                WindowsNativeState& m_nativeState;

                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;

                Eegeo::Helpers::CallbackCollection0 m_callbacks;
            };
        }
    }
}
