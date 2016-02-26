// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerViewModule.h"
#include "ScreenProperties.h"
#include "InteriorsExplorerView.h"
#include "InteriorsExplorerCLI.h"
#include "InteriorsExplorerController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            InteriorsExplorerViewModule::InteriorsExplorerViewModule(InteriorsExplorerViewModel& viewModel,
                                                                     ExampleAppMessaging::TMessageBus& messageBus,
                                                                     MyPinCreation::View::IMyPinCreationInitiationViewModel& initiationViewModel,
                                                                     ExampleApp::Menu::View::IMenuViewModel& searchMenuViewModel,
                                                                     ExampleApp::Menu::View::IMenuViewModel& settingsMenuViewModel,
                                                                     ScreenControl::View::IScreenControlViewModel& flattenViewModel,
                                                                     ScreenControl::View::IScreenControlViewModel& compassViewModel,
                                                                     ScreenControl::View::IScreenControlViewModel& watermarkViewModel,
                                                                     Eegeo::Helpers::IdentityProvider& identityProvider)
            {
                m_pView = Eegeo_NEW(InteriorsExplorerView)();
                
                m_pController = Eegeo_NEW(InteriorsExplorerController)(*m_pView,
                                                                       viewModel,
                                                                       messageBus,
                                                                       initiationViewModel,
                                                                       searchMenuViewModel,
                                                                       settingsMenuViewModel,
                                                                       flattenViewModel,
                                                                       compassViewModel);
            }
            
            InteriorsExplorerViewModule::~InteriorsExplorerViewModule()
            {
                Eegeo_DELETE m_pView;

                Eegeo_DELETE m_pController;
            }
            
            InteriorsExplorerController& InteriorsExplorerViewModule::GetController() const
            {
                return *m_pController;
            }
            
            InteriorsExplorerView& InteriorsExplorerViewModule::GetView() const
            {
                return *m_pView;
            }
        }
    }
}
