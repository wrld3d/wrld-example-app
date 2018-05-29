// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerViewModule.h"
#include "InteriorsExplorerView.h"
#include "InteriorsExplorerController.h"
#include "INavWidgetView.h"

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
                                                                     Eegeo::Location::NavigationService& navigationService,
                                                                     Eegeo::Helpers::CallbackCollection1<NavRouting::View::INavWidgetView::THeight>& navWidgetViewTopHeightChangedCallbacks)
            {
            	m_pView = Eegeo_NEW(InteriorsExplorerView)(nativeState, navWidgetViewTopHeightChangedCallbacks);

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
