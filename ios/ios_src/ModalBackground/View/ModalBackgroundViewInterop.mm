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
        }
    }
}