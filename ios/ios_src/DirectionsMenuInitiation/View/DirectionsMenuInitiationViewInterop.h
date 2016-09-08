// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IDirectionsMenuInitiationView.h"
#include "DirectionsMenuInitiationViewIncludes.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        namespace View
        {
            class DirectionsMenuInitiationViewInterop : public IDirectionsMenuInitiationView
            {
            private:
                DirectionsMenuInitiationView* m_pView;
                Eegeo::Helpers::CallbackCollection1<bool> m_callbacks;

            public:
                DirectionsMenuInitiationViewInterop(DirectionsMenuInitiationView* pView)
                    : m_pView(pView)
                {
                }

                void SetOnScreenStateToIntermediateValue(float value);

                void SetFullyOnScreen();

                void SetFullyOffScreen();

                void OnToggle(bool toggled);

                void InsertToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback);

                void RemoveToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback);
                
            };
        }
    }
}
