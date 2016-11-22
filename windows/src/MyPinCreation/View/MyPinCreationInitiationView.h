// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationInitiationView.h"
#include "ICallback.h"
#include "WindowsNativeState.h"
#include "MyPinCreation.h"
#include "MyPinCreationViewIncludes.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationInitiationViewImpl;

            class MyPinCreationInitiationView: public IMyPinCreationInitiationView
            {
            public:
                MyPinCreationInitiationView(const std::shared_ptr<WindowsNativeState>& nativeState);
                ~MyPinCreationInitiationView();

                void OnSelected();
                void ShouldOffsetButton(bool shouldOffset);
                void InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback);

                void SetOnScreenStateToIntermediateValue(float value);
                void SetFullyOnScreen();
                void SetFullyOffScreen();

            private:
                MyPinCreationInitiationViewImpl* m_pImpl;
            };
        }
    }
}
