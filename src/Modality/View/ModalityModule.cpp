// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <vector>
#include "ModalityModule.h"
#include "ModalityModel.h"
#include "ModalityController.h"

namespace ExampleApp
{
    namespace Modality
    {
        namespace View
        {
            ModalityModule::ModalityModule(ExampleAppMessaging::TMessageBus& messageBus,
                                           const std::vector<OpenableControl::View::IOpenableControlViewModel*>& viewModels,
                                           Menu::View::IMenuIgnoredReactionModel& ignoredReactionModel)
            {
                m_pModel = Eegeo_NEW(ModalityModel)();

                m_pController = Eegeo_NEW(ModalityController)(*m_pModel,
                                                              viewModels,
                                                              ignoredReactionModel);

                m_pModalityObserver = Eegeo_NEW(ModalityObserver)(*m_pModel, messageBus);
            }

            ModalityModule::~ModalityModule()
            {
                Eegeo_DELETE m_pModalityObserver;
                Eegeo_DELETE m_pModel;
            }

            IModalityModel& ModalityModule::GetModalityModel() const
            {
                return *m_pModel;
            }

            IModalityController& ModalityModule::GetModalityController() const
            {
                return *m_pController;
            }
        }
    }
}
