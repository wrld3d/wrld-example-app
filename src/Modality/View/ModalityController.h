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
                IModalityModel& m_modalityModel;
                std::vector<OpenableControl::View::IOpenableControlViewModel*> m_viewModels;
                Eegeo::Helpers::ICallback2<OpenableControl::View::IOpenableControlViewModel&, float>* m_pMenuOpenStateChangedCallback;

                Menu::View::IMenuIgnoredReactionModel& m_ignoredReactionModel;

            public:
                ModalityController(IModalityModel& modalityModel,
                                   const std::vector<OpenableControl::View::IOpenableControlViewModel*>& viewModels,
                                   Menu::View::IMenuIgnoredReactionModel& ignoredReactionModel);

                ~ModalityController();

            private:

                float GetModality() const;

                void MenuOpenStateChangeHandler(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState);
            };
        }
    }
}
