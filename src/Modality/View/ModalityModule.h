// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "Modality.h"
#include "IModalityModule.h"
#include "IMenuViewModel.h"
#include "IOpenableControlViewModel.h"
#include "BidirectionalBus.h"
#include "ModalityObserver.h"
#include "ModalityController.h"
#include "IMenuIgnoredReactionModel.h"

namespace ExampleApp
{
    namespace Modality
    {
        namespace View
        {
            class ModalityModule: public IModalityModule, private Eegeo::NonCopyable
            {
            private:
                IModalityController* m_pController;
                IModalityModel* m_pModel;
                ModalityObserver* m_pModalityObserver;

            public:
                ModalityModule(ExampleAppMessaging::TMessageBus& messageBus,
                               const std::vector<OpenableControl::View::IOpenableControlViewModel*>& viewModels,
                               Menu::View::IMenuIgnoredReactionModel& ignoredReactionModel);

                ~ModalityModule();

                IModalityModel& GetModalityModel() const;

                IModalityController& GetModalityController() const;
            };
        }
    }
}
