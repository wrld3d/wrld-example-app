// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <InteriorsExplorer/View/InteriorsExplorerViewJni.h>
#include "InteriorsExplorerViewModule.h"
#include "ScreenProperties.h"
#include "InteriorsExplorerView.h"
#include "InteriorsExplorerController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            InteriorsExplorerViewModule::InteriorsExplorerViewModule(SdkModel::InteriorsExplorerModel& model,
            														 InteriorsExplorerViewModel& viewModel,
                                                                     ExampleAppMessaging::TMessageBus& messageBus,
																	 AndroidNativeState& nativeState,
                                                                     Eegeo::Location::NavigationService& navigationService)
            {
            	m_pView = Eegeo_NEW(InteriorsExplorerView)(nativeState);

            	m_pController = Eegeo_NEW(InteriorsExplorerController)(model,
            														   *m_pView,
                                                                       viewModel,
                                                                       messageBus,
                                                                       navigationService);
            }
            
            InteriorsExplorerViewModule::~InteriorsExplorerViewModule()
            {
                Eegeo_DELETE m_pController;
                
                Eegeo_DELETE m_pView;
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
