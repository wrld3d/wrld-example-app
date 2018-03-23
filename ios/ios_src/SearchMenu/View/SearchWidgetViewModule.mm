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
                
                m_pSearchWidgetView = Eegeo_NEW(SearchWidgetView)(m_pWrldSearchProvider,
                                                                  m_pWrldSearchProvider);
                
                m_pSearchServices = Eegeo_NEW(SearchMenu::View::SearchServices)(*m_pSearchProvider,
                                                                                messageBus);
                
                m_pSearchWidgetController = Eegeo_NEW(SearchWidgetController)(*m_pSearchWidgetView,
                                                                              *m_pSearchServices,
                                                                              modalBackgroundView,
                                                                              viewModel,
                                                                              messageBus);
            }
            
            SearchWidgetController& SearchWidgetViewModule::GetSearchWidgetController() const{
                return *m_pSearchWidgetController;
            }
            
            SearchWidgetView& SearchWidgetViewModule::GetSearchWidgetView() const
            {
                return *m_pSearchWidgetView;
            }
            
            SearchWidgetViewModule::~SearchWidgetViewModule()
            {
                Eegeo_DELETE m_pSearchWidgetController;
                
                Eegeo_DELETE m_pSearchServices;
                
                Eegeo_DELETE m_pSearchWidgetView;
                
                Eegeo_DELETE m_pSearchProvider;
            }
        }
        
    }
}

