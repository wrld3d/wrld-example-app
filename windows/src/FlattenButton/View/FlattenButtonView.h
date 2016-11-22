// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IFlattenButtonView.h"
#include "WindowsNativeState.h"
#include "CallbackCollection.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            class FlattenButtonViewImpl;

            class FlattenButtonView : public IFlattenButtonView
            {
            private:
                FlattenButtonViewImpl* m_pImpl;
                
            public:
                FlattenButtonView(const std::shared_ptr<WindowsNativeState>& nativeState);
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
