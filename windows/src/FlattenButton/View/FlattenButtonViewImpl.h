// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IFlattenButtonView.h"
#include "WindowsNativeState.h"
#include "CallbackCollection.h"
#include "ICallback.h"

#include "ReflectionHelpers.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            class FlattenButtonViewImpl : public IFlattenButtonView
            {
            private:
                Eegeo::Helpers::CallbackCollection1<bool> m_callbacks;
                const std::shared_ptr<WindowsNativeState> m_nativeState;

                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;

                Helpers::ReflectionHelpers::Method<void> mDestroy;
                Helpers::ReflectionHelpers::Method<bool> mUpdateViewStateBasedOnFlattening;
                Helpers::ReflectionHelpers::Method<float> mAnimateToIntermediateOnScreenState;
                Helpers::ReflectionHelpers::Method<void> mAnimateToActive;
                Helpers::ReflectionHelpers::Method<void> mAnimateToInActive;
                Helpers::ReflectionHelpers::Method<bool> mSetViewEnabled;
                
            public:
                FlattenButtonViewImpl(const std::shared_ptr<WindowsNativeState>& nativeState);
                ~FlattenButtonViewImpl();

                void SetToggled(bool toggled);

                void SetOnScreenStateToIntermediateValue(float value);

                void SetFullyOnScreen();

                void SetFullyOffScreen();

                void OnToggle(bool toggled);

                void InsertToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback);

                void RemoveToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback);

                void SetViewEnabled(bool enabled);
            };
        }
    }
}
