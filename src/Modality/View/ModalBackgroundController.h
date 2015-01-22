// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Modality.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace Modality
    {
        namespace View
        {
            class ModalBackgroundController : protected Eegeo::NonCopyable
            {
            public:

                ModalBackgroundController(IModalBackgroundView& view, IModalityModel& model);
                ~ModalBackgroundController();

            private:

                void OnModalityChanged();

                IModalBackgroundView& m_view;
                IModalityModel& m_model;

                Eegeo::Helpers::TCallback0<ModalBackgroundController> m_modalityChangedCallback;
            };
        }
    }
}
