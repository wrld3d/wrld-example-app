#pragma once

#import <UIKit/UIKit.h>
#include "WrldNav/WrldNav.h"
#include "WrldSearchWidget/WrldSearchWidget.h"
#include "NavWidgetViewIncludes.h"

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
                
                UIView* m_pContainer;
                UIButton* m_pBackButton;
                
                CGFloat m_onScreenPosition = 20;
                CGFloat m_animationTimeInSeconds = 0.2f;
                
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
