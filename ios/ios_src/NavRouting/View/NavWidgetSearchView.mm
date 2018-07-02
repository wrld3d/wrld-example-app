#import <Foundation/Foundation.h>

#import "NavWidgetSearchView.h"
#import "NavSearchContainerView.h"
#import <WrldSearchWidget/WrldSearchWidget.h>
#import "WidgetSearchResultModel.h"
#import "UIButton+DefaultStates.h"
#import "UIColors.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            NavWidgetSearchView::NavWidgetSearchView(id<WRLDSuggestionProvider> navLocationFinder)
            {
                m_pSearchModel = [[WRLDSearchModel alloc] init];
                
                m_backButton = [[[UIButton alloc] init] autorelease];
                [m_backButton setAutoresizingMask:UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight];
                [m_backButton setDefaultStatesWithNormalImageName:@"nav_search_back_button"
                                               highlightImageName:@"nav_search_back_button_down"
                                            normalBackgroundColor:ExampleApp::Helpers::ColorPalette::White
                                         highlightBackgroundColor:ExampleApp::Helpers::ColorPalette::ButtonPressColor];
                
                m_pSearchWidgetView = [[[WRLDSearchWidgetView alloc] init] autorelease];
                [m_pSearchWidgetView useSearchModel:m_pSearchModel];
                [m_pSearchWidgetView setAutoresizingMask:UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight];
                
                m_pSuggestionProviderHandle = [m_pSearchModel addSuggestionProvider: navLocationFinder];
                [m_pSearchWidgetView displaySuggestionProvider: m_pSuggestionProviderHandle];
                m_pSearchWidgetView.resultsVisible = NO;
                
                
                m_container = [[NavSearchContainerView alloc] initWithSubviews:m_pSearchWidgetView :m_backButton];
            }
            
            NavWidgetSearchView::~NavWidgetSearchView()
            {
            }
            
            UIView* NavWidgetSearchView::GetUIView()
            {
                return m_container;
            }
            
            void NavWidgetSearchView::Show()
            {
                [m_pSearchWidgetView clearSearch];
                [m_pSearchWidgetView gainFocus];
                CGRect newFrame = m_container.frame;
                newFrame.origin.y = m_onScreenPosition;
                [m_container setHidden:NO];
                [UIView animateWithDuration:m_animationTimeInSeconds animations:^{
                    m_container.frame = newFrame;
                }];
            }
            
            void NavWidgetSearchView::Hide()
            {
                [m_pSearchWidgetView hideResultsView];
                CGRect newFrame = m_container.frame;
                newFrame.origin.y = -m_backButton.bounds.size.height;
                [UIView animateWithDuration:m_animationTimeInSeconds animations:^{
                    m_container.frame = newFrame;
                } completion:^(BOOL finished) {
                    if(finished)
                    {
                        [m_container setHidden:YES];
                    }
                }];
            }
            
            void NavWidgetSearchView::AddCloseButtonTarget(id target, SEL selector)
            {
                [m_backButton addTarget:target action:selector forControlEvents:UIControlEventPrimaryActionTriggered];
            }
            
            void NavWidgetSearchView::RemoveCloseButtonTarget(id target, SEL selector)
            {
                [m_backButton removeTarget:target action:selector forControlEvents:UIControlEventPrimaryActionTriggered];
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
