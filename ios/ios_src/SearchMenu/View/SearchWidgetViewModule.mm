#include "SearchWidgetViewModule.h"
//#include "SearchWidgetView.h"


namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchWidgetViewModule::SearchWidgetViewModule(
                                                           Modality::View::IModalBackgroundView& modalBackgroundView,
                                                           Menu::View::IMenuViewModel& viewModel,
                                                           ExampleAppMessaging::TMessageBus& messageBus
                                                           )
            {
                m_pSearchProvider = Eegeo_NEW(SearchProviders::SearchProvider)();
                
                m_pWrldSearchProvider = [[WidgetSearchProvider alloc] initWithSearchProvider: m_pSearchProvider];
                
                
                
                m_pView = [[SearchWidgetContainerView alloc] initWithSearchProvider:m_pWrldSearchProvider
                                                                messageBus:messageBus];
                
                m_pSearchServices = Eegeo_NEW(SearchMenu::View::SearchServices)(*m_pSearchProvider,
                                                                                messageBus);
                
                m_pSearchWidgetController = Eegeo_NEW(SearchWidgetController)(*[m_pView getInterop],
                                                                              *m_pSearchServices,
                                                                              modalBackgroundView,
                                                                              viewModel,
                                                                              messageBus);
            }
            
            SearchWidgetController& SearchWidgetViewModule::GetSearchWidgetController() const{
                return *m_pSearchWidgetController;
            }
            
            SearchWidgetContainerView& SearchWidgetViewModule::GetSearchWidgetView() const
            {
                return *m_pView;
            }
            
            UIViewController& SearchWidgetViewModule::GetSearchWidgetUIViewController() const
            {
                return *[m_pView getInterop]->GetWidgetController();
            }
            
            SearchWidgetViewModule::~SearchWidgetViewModule()
            {
                Eegeo_DELETE m_pSearchWidgetController;
                
                Eegeo_DELETE m_pSearchServices;
                
                [m_pView release];
                
                Eegeo_DELETE m_pSearchProvider;
            }
        }
        
    }
}

