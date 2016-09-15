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
                const std::shared_ptr<OpenableControl::View::TOpenables> m_openables;
                Eegeo::Helpers::TCallback2<ModalityController, OpenableControl::View::IOpenableControlViewModel&, float> m_menuOpenStateChangedCallback;
                Eegeo::Helpers::TCallback1<ModalityController, OpenableControl::View::IOpenableControlViewModel*> m_openableAdded;
                Eegeo::Helpers::TCallback1<ModalityController, OpenableControl::View::IOpenableControlViewModel*> m_openableRemoved;
                const std::shared_ptr<Menu::View::IMenuIgnoredReactionModel> m_ignoredReactionModel;

            public:
                ModalityController(const std::shared_ptr<IModalityModel>& modalityModel,
                                   const std::shared_ptr<OpenableControl::View::TOpenables>& openables,
                                   const std::shared_ptr<Menu::View::IModalityIgnoredReactionModel>& ignoredReactionModel);

                ~ModalityController();

            private:

                float GetModality() const;
                void OnOpenableAdded(OpenableControl::View::IOpenableControlViewModel*& openable);
                void OnOpenableRemoved(OpenableControl::View::IOpenableControlViewModel*& openable);
                void MenuOpenStateChangeHandler(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState);
            };
        }
    }
}
