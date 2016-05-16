// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IFlattenButtonView.h"
#include "AndroidNativeState.h"
#include "CallbackCollection.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            class FlattenButtonView : public IFlattenButtonView
            {
            private:
                Eegeo::Helpers::CallbackCollection1<bool> m_callbacks;
                AndroidNativeState& m_nativeState;

                jclass m_uiViewClass;
                jobject m_uiView;
            public:
                FlattenButtonView(AndroidNativeState& nativeState);
                ~FlattenButtonView();

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
