// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IModalBackgroundView.h"

#include "CallbackCollection.h"
#include "ICallback.h"
#include "ModalBackgroundViewIncludes.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace View
        {
            class ModalBackgroundViewInterop : public Modality::View::IModalBackgroundView
            {
            public:

                ModalBackgroundViewInterop(ModalBackgroundView* pView)
                    : m_pView(pView)
                {
                }

                void SetFullyActive();
                void SetFullyInactive();
                void SetActiveStateToIntermediateValue(float modality);
                
                void InsertTappedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveTappedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void HandleViewTapped();

            private:

                ModalBackgroundView* m_pView;
                
                Eegeo::Helpers::CallbackCollection0 m_tappedCallbacks;
            };
        }
    }
}
