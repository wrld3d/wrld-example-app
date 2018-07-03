#import <Foundation/Foundation.h>

#import "NavWidgetSearchView.h"
#import "NavSearchContainerView.h"
#import <WrldSearchWidget/WrldSearchWidget.h>
#import "WidgetSearchProvider.h"
#import "WidgetSearchResultModel.h"
#import "UIButton+DefaultStates.h"
#import "UIColors.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            NavWidgetSearchView::NavWidgetSearchView(WidgetSearchProvider* navLocationFinder)
            {
                m_pSearchModel = [[WRLDSearchModel alloc] init];
                
                m_autocompleteCancelledEvent = ^(WRLDSearchQuery* cancelledQuery){
                    [navLocationFinder cancelAutocompleteRequest];
                };
                
                [m_pSearchModel.suggestionObserver addQueryCancelledEvent: m_autocompleteCancelledEvent];
                
                m_pBackButton = [[[UIButton alloc] init] autorelease];
                [m_pBackButton setAutoresizingMask:UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight];
                [m_pBackButton setDefaultStatesWithNormalImageName:@"nav_search_back_button"
                                               highlightImageName:@"nav_search_back_button_down"
                                            normalBackgroundColor:ExampleApp::Helpers::ColorPalette::White
                                         highlightBackgroundColor:ExampleApp::Helpers::ColorPalette::ButtonPressColor];
                
                m_pSearchWidgetView = [[[WRLDSearchWidgetView alloc] init] autorelease];
                [m_pSearchWidgetView useSearchModel:m_pSearchModel];
                [m_pSearchWidgetView setAutoresizingMask:UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight];
                
                m_pSuggestionProviderHandle = [m_pSearchModel addSuggestionProvider: navLocationFinder];
                [m_pSearchWidgetView displaySuggestionProvider: m_pSuggestionProviderHandle];
                m_pSearchWidgetView.resultsVisible = NO;
                
                
                m_pContainer = [[NavSearchContainerView alloc] initWithSubviews:m_pSearchWidgetView :m_pBackButton];
            }
            
            NavWidgetSearchView::~NavWidgetSearchView()
            {
                [m_pSearchModel.suggestionObserver removeQueryCancelledEvent: m_autocompleteCancelledEvent];
            }
            
            UIView* NavWidgetSearchView::GetUIView()
            {
                return m_pContainer;
            }
            
            void NavWidgetSearchView::Show()
            {
                [m_pSearchWidgetView clearSearch];
                [m_pSearchWidgetView gainFocus];
                CGRect newFrame = m_pContainer.frame;
                newFrame.origin.y = m_onScreenPosition;
                [m_pContainer setHidden:NO];
                [UIView animateWithDuration:m_animationTimeInSeconds animations:^{
                    m_pContainer.frame = newFrame;
                }];
            }
            
            void NavWidgetSearchView::Hide()
            {
                [m_pSearchWidgetView hideResultsView];
                CGRect newFrame = m_pContainer.frame;
                newFrame.origin.y = -m_pBackButton.bounds.size.height;
                [UIView animateWithDuration:m_animationTimeInSeconds animations:^{
                    m_pContainer.frame = newFrame;
                } completion:^(BOOL finished) {
                    if(finished)
                    {
                        [m_pContainer setHidden:YES];
                    }
                }];
            }
            
            void NavWidgetSearchView::AddCloseButtonTarget(id target, SEL selector)
            {
                [m_pBackButton addTarget:target action:selector forControlEvents:UIControlEventPrimaryActionTriggered];
            }
            
            void NavWidgetSearchView::RemoveCloseButtonTarget(id target, SEL selector)
            {
                [m_pBackButton removeTarget:target action:selector forControlEvents:UIControlEventPrimaryActionTriggered];
            }
            
            void NavWidgetSearchView::AddSuggestionSelectedCallback(ResultSelectedEvent resultSelectedEvent)
            {
                [m_pSearchWidgetView.suggestionSelectionObserver addResultSelectedEvent: resultSelectedEvent];
            }
            
            void NavWidgetSearchView::RemoveSuggestionSelectedCallback(ResultSelectedEvent resultSelectedEvent)
            {
                [m_pSearchWidgetView.suggestionSelectionObserver removeResultSelectedEvent: resultSelectedEvent];
            }
            
            void NavWidgetSearchView::AddSearchStartedCallback(QueryEvent queryEvent)
            {
                [m_pSearchModel.searchObserver addQueryStartingEvent: queryEvent];
            }
            
            void NavWidgetSearchView::RemoveSearchStartedCallback(QueryEvent queryEvent)
            {
                [m_pSearchModel.searchObserver removeQueryStartingEvent: queryEvent];
            }
        }
    }
}
