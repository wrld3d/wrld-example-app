// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "Modality.h"
#include "IModalityController.h"
#include "IMenuViewModel.h"
#include "IOpenableControlViewModel.h"
#include "CallbackCollection.h"
#include "IMenuIgnoredReactionModel.h"

namespace ExampleApp
{
    namespace Modality
    {
        namespace View
        {
            class ModalityController : public IModalityController, private Eegeo::NonCopyable
            {
                const std::shared_ptr<IModalityModel> m_modalityModel;
                const std::shared_ptr<OpenableControl::View::TOpenables> m_viewModels;
                Eegeo::Helpers::ICallback2<OpenableControl::View::IOpenableControlViewModel&, float>* m_pMenuOpenStateChangedCallback;

                const std::shared_ptr<Menu::View::IMenuIgnoredReactionModel> m_ignoredReactionModel;

            public:
                ModalityController(const std::shared_ptr<IModalityModel>& modalityModel,
                                   const std::shared_ptr<OpenableControl::View::TOpenables>& viewModels,
                                   const std::shared_ptr<Menu::View::IModalityIgnoredReactionModel>& ignoredReactionModel);

                ~ModalityController();

            private:

                float GetModality() const;

                void MenuOpenStateChangeHandler(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState);
            };
        }
    }
}
