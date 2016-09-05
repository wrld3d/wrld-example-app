// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Modality.h"
#include "ICallback.h"
#include <memory>

namespace ExampleApp
{
    namespace Modality
    {
        namespace View
        {
            class ModalBackgroundController : protected Eegeo::NonCopyable
            {
            public:

                ModalBackgroundController(const std::shared_ptr<IModalBackgroundView>& view, const std::shared_ptr<IModalityModel>& model);
                ~ModalBackgroundController();

            private:

                void OnModalityChanged();

                const std::shared_ptr<IModalBackgroundView> m_view;
                const std::shared_ptr<IModalityModel> m_model;

                Eegeo::Helpers::TCallback0<ModalBackgroundController> m_modalityChangedCallback;
            };
        }
    }
}
