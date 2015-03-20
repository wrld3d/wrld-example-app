// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationInitiationView.h"
#include "MyPinCreationInitiationViewIncludes.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationInitiationViewInterop : public IMyPinCreationInitiationView
            {
            private:
                MyPinCreationInitiationView* m_pView;
                Eegeo::Helpers::CallbackCollection0 m_callbacks;

            public:
                MyPinCreationInitiationViewInterop(MyPinCreationInitiationView* pView)
                    : m_pView(pView)
                {
                }

                void SetOnScreenStateToIntermediateValue(float value);

                void SetFullyOnScreen();

                void SetFullyOffScreen();

                void OnSelected();

                void InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback);
            };
        }
    }
}
