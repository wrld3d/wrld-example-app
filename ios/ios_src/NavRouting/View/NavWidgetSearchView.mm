#import <Foundation/Foundation.h>

#import "NavWidgetSearchView.h"
#import <WrldSearchWidget/WrldSearchWidget.h>
#import "WidgetSearchResultModel.h"
#import "UIButton+DefaultStates.h"
#import "UIColors.h"

//Wrld Example App fudges the propagation of touch events so to prevent our touch events getting
//passed down to the Map we need to extend our common widget with a consumesTouch selector.
@interface UIView(WrldExampleApp)
- (BOOL) consumesTouch:(UITouch *)touch;
- (void) setVisible:(BOOL) isVisible;
@end

@implementation UIView(WrldExampleApp)
- (BOOL)consumesTouch:(UITouch *)touch
{
    BOOL consume = [self pointInside:[touch locationInView:self] withEvent:nil];
    return consume;
}

- (void) setVisible:(BOOL) isVisible
{
    [self setHidden: !isVisible];
}
@end

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            NavWidgetSearchView::NavWidgetSearchView(id<WRLDSuggestionProvider> navLocationFinder)
            {
                m_pSearchModel = [[WRLDSearchModel alloc] init];
                
                m_container = [[UIView alloc] initWithFrame:CGRectMake(20, 20, 300, 300)];
                
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
                
                [m_container addSubview: m_pSearchWidgetView];
                [m_container addSubview: m_backButton];
                Hide();
                AddSubviewConstraints();
            }
            
            NavWidgetSearchView::~NavWidgetSearchView()
            {
            }
            
            UIView* NavWidgetSearchView::GetUIView()
            {
                return m_container;
            }
                        
            void NavWidgetSearchView::AddSubviewConstraints()
            {
                m_pSearchWidgetView.translatesAutoresizingMaskIntoConstraints = false;
                m_backButton.translatesAutoresizingMaskIntoConstraints = false;
                
                NSLayoutConstraint* searchTop = Constrain(NSLayoutAttributeTop, m_pSearchWidgetView, m_container, 0);
                NSLayoutConstraint* searchBottom = Constrain(NSLayoutAttributeBottom, m_pSearchWidgetView, m_container, 0);
                NSLayoutConstraint* searchLeading = Constrain(NSLayoutAttributeLeading, m_pSearchWidgetView, m_container, 40);
                NSLayoutConstraint* searchTrailing = Constrain(NSLayoutAttributeTrailing, m_pSearchWidgetView, m_container, 0);
                
                NSLayoutConstraint* backTop = Constrain(NSLayoutAttributeTop, m_backButton, m_pSearchWidgetView, 0);
                NSLayoutConstraint* backHeight = [NSLayoutConstraint constraintWithItem:m_backButton
                                                                              attribute:NSLayoutAttributeBottom
                                                                              relatedBy:NSLayoutRelationEqual
                                                                                 toItem:m_pSearchWidgetView.suggestionsContainer
                                                                              attribute:NSLayoutAttributeTop
                                                                             multiplier:1.0
                                                                               constant:0];
                
                NSLayoutConstraint* backLeading = Constrain(NSLayoutAttributeLeading, m_backButton, m_container, 0);
                NSLayoutConstraint* backTrailing = [NSLayoutConstraint constraintWithItem:m_backButton
                                                                                attribute:NSLayoutAttributeTrailing
                                                                                relatedBy:NSLayoutRelationEqual
                                                                                   toItem:m_pSearchWidgetView
                                                                                attribute:NSLayoutAttributeLeading
                                                                               multiplier:1.0
                                                                                 constant:0];
                
                [m_container addConstraint:searchTop];
                [m_container addConstraint:searchBottom];
                [m_container addConstraint:searchLeading];
                [m_container addConstraint:searchTrailing];
                
                [m_container addConstraint:backTop];
                [m_container addConstraint:backHeight];
                [m_container addConstraint:backLeading];
                [m_container addConstraint:backTrailing];
            }
            
            NSLayoutConstraint* NavWidgetSearchView::Constrain (NSLayoutAttribute attribute, UIView* constrained, UIView* constrainer, CGFloat constant)
            {
                return [NSLayoutConstraint constraintWithItem:constrained
                                                    attribute:attribute
                                                    relatedBy:NSLayoutRelationEqual
                                                       toItem:constrainer
                                                    attribute:attribute
                                                   multiplier:1.0
                                                     constant:constant];
            }
            
            void NavWidgetSearchView::Show()
            {
                [m_pSearchWidgetView clearSearch];
                [m_pSearchWidgetView gainFocus];
                [m_container setVisible: YES];
            }
            
            void NavWidgetSearchView::Hide()
            {
                [m_container setVisible: NO];
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
