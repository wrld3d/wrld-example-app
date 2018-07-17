#import <Foundation/Foundation.h>

#import "NavWidgetSearchView.h"
#import "NavSearchContainerView.h"
#import <WrldSearchWidget/WrldSearchWidget.h>
#import "WidgetSearchProvider.h"
#import "WidgetSearchResultModel.h"
#import "UIButton+DefaultStates.h"
#import "UIColors.h"
#import "ImageHelpers.h"
#import "WidgetSearchResultTableViewCell.h"

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
                                
                m_autocompleteCompletedEvent = ^(WRLDSearchQuery* startedQuery){
                    HideSearchHint();
                };
                
                [m_pSearchModel.suggestionObserver addQueryCompletedEvent: m_autocompleteCompletedEvent];
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
                
                m_pSearchProviderHandle = [m_pSearchModel addSearchProvider: navLocationFinder];
                [m_pSearchWidgetView displaySearchProvider:m_pSearchProviderHandle];
                
                NSBundle* pResourceBundle = [NSBundle bundleForClass:[WidgetSearchResultTableViewCell class]];
                UINib* pNib = [UINib nibWithNibName: @"WidgetSearchResultTableViewCell" bundle:pResourceBundle];
                
                [m_pSearchWidgetView registerNib:pNib forUseWithResultsTableCellIdentifier:@"WidgetSearchResultTableViewCell"];
                
                m_willPopulateResultCell = ^(WRLDSearchResultTableViewCell *pCell)
                {
                    if([pCell isKindOfClass:[WidgetSearchResultTableViewCell class]])
                    {
                        WidgetSearchResultTableViewCell* pCastCell = (WidgetSearchResultTableViewCell*) pCell;
                        [pCastCell setNavigationHidden: YES];
                    }
                };
                [m_pSearchWidgetView.searchResultContentObserver addWillPopulateEvent:m_willPopulateResultCell];
                
                m_pSearchHintContainer = [[[UIView alloc] init] autorelease];
                m_pSearchHintContainer.backgroundColor = [UIColor whiteColor];
                m_pSearchHintContainer.layer.cornerRadius = 4;
                m_pSearchHintContainer.layer.borderWidth = 1;
                m_pSearchHintContainer.layer.borderColor = [ExampleApp::Helpers::ColorPalette::UiBorderColor CGColor];
                
                m_pSearchHintIcon = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"searchbox_Destination")] autorelease];
                CGFloat hintPadding = 4;
                CGFloat iconSize = 32;
                m_pSearchHintIcon.frame = CGRectMake(hintPadding, hintPadding*1.5, iconSize, iconSize);
                m_pSearchHintLabel = [[[UILabel alloc] init] autorelease];
                m_pSearchHintLabel.text = @"Tap to drop pin at your\ndesired location.";
                m_pSearchHintLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
                m_pSearchHintLabel.font = [UIFont systemFontOfSize:14.0];
                m_pSearchHintLabel.numberOfLines = 2;
                
                m_pSearchHintLabel.lineBreakMode = NSLineBreakByWordWrapping;
                m_pSearchHintLabel.frame = CGRectMake(hintPadding*3 + iconSize, hintPadding, 175, iconSize+hintPadding);
                
                [m_pSearchHintContainer addSubview:m_pSearchHintIcon];
                [m_pSearchHintContainer addSubview:m_pSearchHintLabel];
                
                m_pSearchHintContainer.frame = CGRectMake(0, 70, m_pSearchHintLabel.frame.origin.x + m_pSearchHintLabel.frame.size.width + hintPadding, iconSize+3*hintPadding);
                
                m_hasShownHint = NO;
                [m_pSearchHintContainer setHidden:YES];
                m_pSearchHintContainer.alpha = 0.0;
                
                m_pResultsView = [[[UIView alloc] init] autorelease];
                m_pSearchWidgetView.suggestionsContainer = m_pResultsView;
                m_pSearchWidgetView.resultsContainer = m_pResultsView;
                
                m_pContainer = [[NavSearchContainerView alloc] initWithSubviews: m_pSearchWidgetView :m_pResultsView :m_pBackButton :m_pSearchHintContainer];
            }
            
            NavWidgetSearchView::~NavWidgetSearchView()
            {
                [m_pSearchWidgetView.searchResultContentObserver removeWillPopulateEvent:m_willPopulateResultCell];
                
                [m_pSearchModel.suggestionObserver removeQueryCancelledEvent: m_autocompleteCancelledEvent];
                [m_pSearchModel.suggestionObserver removeQueryCompletedEvent: m_autocompleteCompletedEvent];
                
                [m_pSearchWidgetView stopDisplayingSuggestionProvider: m_pSuggestionProviderHandle];
                [m_pSearchWidgetView stopDisplayingSearchProvider:
                    m_pSearchProviderHandle];
            }
            
            UIView* NavWidgetSearchView::GetUIView()
            {
                return m_pContainer;
            }
            
            void NavWidgetSearchView::Show()
            {
                CGFloat onScreenPosition = 0;
                if (@available(iOS 11.0, *))
                {
                    onScreenPosition = m_pContainer.superview.safeAreaInsets.top;
                }
                else
                {
                    onScreenPosition = [UIApplication sharedApplication].statusBarFrame.size.height;
                }
                
                [m_pSearchWidgetView clearSearch];
                [m_pSearchWidgetView gainFocus];
                CGRect newFrame = m_pContainer.frame;
                newFrame.origin.y = onScreenPosition;
                [m_pContainer setHidden:NO];
                [UIView animateWithDuration:m_animationTimeInSeconds animations:^{
                    m_pContainer.frame = newFrame;
                } completion:^(BOOL finished) {
                    if(!m_hasShownHint)
                    {
                        m_hasShownHint = YES;
                        ShowSearchHint();
                    }
                }];
            }
            
            void NavWidgetSearchView::Hide()
            {
                [m_pSearchWidgetView hideResultsView];
                CGRect newFrame = m_pContainer.frame;
                newFrame.origin.y = -m_pBackButton.bounds.size.height;
                [UIView animateWithDuration:m_animationTimeInSeconds animations:^{
                    m_pContainer.frame = newFrame;
                    m_pSearchHintContainer.alpha = 0.0;
                } completion:^(BOOL finished) {
                    if(finished)
                    {
                        [m_pContainer setHidden:YES];
                        [m_pSearchHintContainer setHidden:YES];
                    }
                }];
                
                HideSearchHint();
            }
            
            void NavWidgetSearchView::ShowSearchHint()
            {
                [m_pSearchHintContainer setHidden:NO];
                m_pSearchHintContainer.alpha = 0.0;
                
                [UIView animateWithDuration:m_animationTimeInSeconds delay:m_animationTimeInSeconds options:UIViewAnimationOptionBeginFromCurrentState animations:^{
                    m_pSearchHintContainer.alpha = 1.0;
                } completion:^(BOOL finished) {
                    if(finished)
                    {
                        [UIView animateWithDuration:m_animationTimeInSeconds delay:5.0 options:UIViewAnimationOptionBeginFromCurrentState animations:^{
                            m_pSearchHintContainer.alpha = 0.0;
                        } completion:^(BOOL finished) {
                            if(finished)
                            {
                                [m_pSearchHintContainer setHidden:YES];
                            }
                        }];
                    }
                }];
            }
            
            void NavWidgetSearchView::HideSearchHint()
            {
                [m_pSearchHintContainer.layer removeAllAnimations];
                [m_pSearchHintContainer setHidden:YES];
            }
            
            void NavWidgetSearchView::AddCloseButtonTarget(id target, SEL selector)
            {
                [m_pBackButton addTarget:target action:selector forControlEvents:UIControlEventPrimaryActionTriggered];
            }
            
            void NavWidgetSearchView::RemoveCloseButtonTarget(id target, SEL selector)
            {
                [m_pBackButton removeTarget:target action:selector forControlEvents:UIControlEventPrimaryActionTriggered];
            }
            
            void NavWidgetSearchView::AddSelectedResultCallback(ResultSelectedEvent resultSelectedEvent)
            {
                [m_pSearchWidgetView.searchSelectionObserver addResultSelectedEvent: resultSelectedEvent];
            }
            
            void NavWidgetSearchView::RemoveSelectedResultCallback(ResultSelectedEvent resultSelectedEvent)
            {
                [m_pSearchWidgetView.searchSelectionObserver removeResultSelectedEvent: resultSelectedEvent];
            }
        }
    }
}
