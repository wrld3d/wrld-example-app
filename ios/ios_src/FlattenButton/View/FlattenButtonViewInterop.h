// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IFlattenButtonView.h"
#include "FlattenButtonView.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            class FlattenButtonViewInterop : public IFlattenButtonView
            {
            private:
                FlattenButtonView* m_pView;
                Eegeo::Helpers::CallbackCollection1<bool> m_callbacks;

            public:
                FlattenButtonViewInterop(FlattenButtonView* pView)
                    : m_pView(pView)
                {
                }

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
