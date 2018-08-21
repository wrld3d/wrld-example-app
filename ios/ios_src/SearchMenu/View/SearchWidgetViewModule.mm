#include "SearchWidgetViewModule.h"
#include "SearchResultsRepository.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchWidgetViewModule::SearchWidgetViewModule(
                                                           Modality::View::IModalBackgroundView& modalBackgroundView,
                                                           Menu::View::IMenuViewModel& viewModel,
                                                           bool isNavigationEnabled,
                                                           ExampleAppMessaging::TMessageBus& messageBus
                                                           )
            {
                m_pSearchProvider = Eegeo_NEW(SearchProviders::SearchProvider)();
                
                m_pSearchModel = [[[WRLDSearchModel alloc] init] autorelease];
                
                m_pWrldSearchProvider = [[WidgetSearchProvider alloc] initWithSearchProvider: m_pSearchProvider];
                
                m_autocompleteCancelledEvent = ^(WRLDSearchQuery* cancelledQuery){
                    [m_pWrldSearchProvider cancelAutocompleteRequest];
                };
                
                [m_pSearchModel.suggestionObserver addQueryCancelledEvent: m_autocompleteCancelledEvent];
                
                m_pView = [[SearchWidgetContainerView alloc] initWithSearchModel: m_pSearchModel
                                                                  searchProvider: m_pWrldSearchProvider
                                                               navigationEnabled: isNavigationEnabled
                                                                      messageBus: messageBus];
                
                m_pSearchResults = Eegeo_NEW(SearchResultsRepository)();
                m_pSuggestions = Eegeo_NEW(SearchResultsRepository)();
                
                m_pSearchServices = Eegeo_NEW(SearchMenu::View::SearchServices)(*m_pSearchProvider,
                                                                                *m_pSearchResults,
                                                                                *m_pSuggestions,
                                                                                *[m_pView getInterop],
                                                                                messageBus);
                
                m_pSearchWidgetController = Eegeo_NEW(SearchWidgetController)(*[m_pView getInterop],
                                                                              *m_pSearchResults,
                                                                              modalBackgroundView,
                                                                              viewModel,
                                                                              messageBus,
                                                                              *m_pSearchProvider);
            }
            
            SearchWidgetController& SearchWidgetViewModule::GetSearchWidgetController() const
            {
                return *m_pSearchWidgetController;
            }
            
            SearchWidgetContainerView& SearchWidgetViewModule::GetSearchWidgetView() const
            {
                return *m_pView;
            }
            
            WidgetSearchProvider* SearchWidgetViewModule::GetSuggestionProvider() const
            {
                return m_pWrldSearchProvider;
            }
            
            ISearchResultsRepository& SearchWidgetViewModule::GetSuggestionsRepository() const
            {
                return *m_pSuggestions;
            }
                        
            ISearchResultsRepository& SearchWidgetViewModule::GetSearchResultsRepository() const
            {
                return *m_pSearchResults;
            }
            
            SearchWidgetViewModule::~SearchWidgetViewModule()
            {
                Eegeo_DELETE m_pSearchWidgetController;
                
                Eegeo_DELETE m_pSearchServices;
                
                Eegeo_DELETE m_pSuggestions;
                Eegeo_DELETE m_pSearchResults;
                
                [m_pView release];
                
                [m_pSearchModel.suggestionObserver removeQueryCancelledEvent: m_autocompleteCancelledEvent];
                
                Eegeo_DELETE m_pSearchProvider;
            }
        }
        
    }
}

