// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "Modality.h"
#include "IModalityController.h"
#include "IMenuViewModel.h"
#include "IOpenableControlViewModel.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace Modality
    {
        namespace View
        {
            class ModalityController : public IModalityController, private Eegeo::NonCopyable
            {
                IModalityModel& m_modalityModel;
                std::vector<OpenableControl::View::IOpenableControlViewModel*> m_viewModels;
                Eegeo::Helpers::ICallback2<OpenableControl::View::IOpenableControlViewModel&, float>* m_pMenuOpenStateChangedCallback;

                std::vector<Eegeo::Helpers::TIdentity> m_ignoredMenuIdentities;

            public:
                ModalityController(IModalityModel& modalityModel,
                                   const std::vector<OpenableControl::View::IOpenableControlViewModel*>& viewModels);

                ~ModalityController();

                void AddIgnoredMenuIdentity(Eegeo::Helpers::TIdentity identity);
                void RemoveIgnoredMenuIdentity(Eegeo::Helpers::TIdentity identity);

            private:

                float GetModality() const;

                void MenuOpenStateChangeHandler(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState);
            };
        }
    }
}
