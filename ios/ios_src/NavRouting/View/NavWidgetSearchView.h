#pragma once

#import <UIKit/UIKit.h>
#include "WrldNav/WrldNav.h"
#include "WrldSearchWidget/WrldSearchWidget.h"
#include "NavWidgetViewIncludes.h"

@interface NavWidgetViewVisibilityControl : NSObject<WRLDNavModelEventListener>
- (instancetype) initWithSearchView: (WRLDSearchWidgetView*) searchView navWidgetView : (ExampleApp::NavRouting::View::NavWidgetView*) navWidgetView;
- (void) showNavView;
- (void) showSearchView;
@property (readonly) BOOL isSearchingForStartPoint;
@end

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class NavWidgetSearchView
            {
            private:
                WRLDSearchWidgetView* m_pSearchWidgetView;
                WRLDSearchModel* m_pSearchModel;
                WRLDSuggestionProviderHandle* m_pSuggestionProviderHandle;
                
                UIView *m_container;
                UIButton *m_backButton;
                
                void AddSubviewConstraints();
                NSLayoutConstraint* Constrain (NSLayoutAttribute attribute, UIView* constrained, UIView* constrainer, CGFloat constant);
                
            public:
                NavWidgetSearchView(id<WRLDSuggestionProvider> navLocationFinder);
                
                ~NavWidgetSearchView();
                
                UIView* GetUIView();
                
                void Show();
                void Hide();
                
                void AddCloseButtonTarget(id target, SEL selector);
                void RemoveCloseButtonTarget(id target, SEL selector);
                void AddSuggestionSelectedCallback(ResultSelectedEvent resultSelectedEvent);
                void RemoveSuggestionSelectedCallback(ResultSelectedEvent resultSelectedEvent);
                void AddSearchStartedCallback(QueryEvent queryEvent);
                void RemoveSearchStartedCallback(QueryEvent queryEvent);
            };
        }
    }
}
