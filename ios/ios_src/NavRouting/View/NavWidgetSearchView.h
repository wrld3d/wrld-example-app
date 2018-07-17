#pragma once

#import <UIKit/UIKit.h>
#include "WrldNav/WrldNav.h"
#include "WrldSearchWidget/WrldSearchWidget.h"
#include "NavWidgetViewIncludes.h"
#include "WidgetSearchProvider.h"

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
                UIView* m_pResultsView;
                WRLDSearchModel* m_pSearchModel;
                WRLDSuggestionProviderHandle* m_pSuggestionProviderHandle;
                WRLDSearchProviderHandle* m_pSearchProviderHandle;
                
                QueryEvent m_autocompleteCancelledEvent;
                QueryEvent m_autocompleteCompletedEvent;
                
                UIView* m_pContainer;
                UIButton* m_pBackButton;
                
                UIView* m_pSearchHintContainer;
                UIImageView* m_pSearchHintIcon;
                UILabel* m_pSearchHintLabel;
                BOOL m_hasShownHint;
                
                CGFloat m_animationTimeInSeconds = 0.2f;
                
                void (^m_willPopulateResultCell) (WRLDSearchResultTableViewCell*);
                
                void ShowSearchHint();
                void HideSearchHint();
                
            public:
                NavWidgetSearchView(WidgetSearchProvider* navLocationFinder);
                
                ~NavWidgetSearchView();
                
                UIView* GetUIView();
                
                void Show();
                void Hide();
                
                void AddCloseButtonTarget(id target, SEL selector);
                void RemoveCloseButtonTarget(id target, SEL selector);
                void AddSelectedResultCallback(ResultSelectedEvent resultSelectedEvent);
                void RemoveSelectedResultCallback(ResultSelectedEvent resultSelectedEvent);
            };
        }
    }
}
