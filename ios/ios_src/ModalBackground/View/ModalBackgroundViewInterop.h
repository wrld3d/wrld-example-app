// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IModalBackgroundView.h"
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

            private:

                ModalBackgroundView* m_pView;
            };
        }
    }
}
