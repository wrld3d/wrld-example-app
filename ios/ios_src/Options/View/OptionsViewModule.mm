// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsViewModule.h"
#include "IOptionsViewModel.h"
#include "OptionsView.h"
#include "OptionsController.h"
#include "OptionsViewInterop.h"
#include "IHttpCache.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            OptionsViewModule::OptionsViewModule(IOptionsViewModel& viewModel,
                                                 Eegeo::Helpers::IHttpCache& httpCache,
                                                 ExampleAppMessaging::TMessageBus& messageBus,
                                                 Eegeo::Concurrency::Tasks::IWorkPool& workPool,
                                                 InteriorsExplorer::View::InteriorsExplorerController& interiorsExplorerController,
                                                 InitialExperience::View::InitialExperienceIntroController& initialExperienceIntroController)
            {
                m_pView = [[OptionsView alloc] initView];
                m_pController = Eegeo_NEW(OptionsController)(*[m_pView getInterop], viewModel, messageBus, interiorsExplorerController, initialExperienceIntroController);
                m_pClearCacheMessageHandler = Eegeo_NEW(SdkModel::ClearCacheMessageHandler)(httpCache, messageBus, workPool);
            }

            OptionsViewModule::~OptionsViewModule()
            {
                Eegeo_DELETE m_pClearCacheMessageHandler;
                Eegeo_DELETE m_pController;
                [m_pView release];
            }

            OptionsController& OptionsViewModule::GetOptionsController() const
            {
                return *m_pController;
            }

            OptionsView& OptionsViewModule::GetOptionsView() const
            {
                return *m_pView;
            }
        }
    }
}
