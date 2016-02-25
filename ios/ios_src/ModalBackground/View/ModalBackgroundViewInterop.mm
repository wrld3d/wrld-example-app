// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalBackgroundViewInterop.h"
#include "ModalBackgroundView.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace View
        {
            void ModalBackgroundViewInterop::SetFullyActive()
            {
                [m_pView setFullyActive];
            }

            void ModalBackgroundViewInterop::SetFullyInactive()
            {
                [m_pView setFullyInactive];
            }

            void ModalBackgroundViewInterop::SetActiveStateToIntermediateValue(float modality)
            {
                [m_pView setActiveStateToIntermediateValue:modality];
            }
            
            void ModalBackgroundViewInterop::InsertTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_tappedCallbacks.AddCallback(callback);
            }
            
            void ModalBackgroundViewInterop::RemoveTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_tappedCallbacks.RemoveCallback(callback);
            }
            
            void ModalBackgroundViewInterop::HandleViewTapped()
            {
                m_tappedCallbacks.ExecuteCallbacks();
            }
        }
    }
}