// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "SearchMenuDragTab.h"
#import "UIButton+DefaultStates.h"

@interface SearchMenuDragTab()
{
    UIButton* m_pDragTab;
}

@end

@implementation SearchMenuDragTab

- (void)init:(UIButton*)dragTab
{
    m_pDragTab = dragTab;
}

- (void)showCloseView:(bool)shouldShowCloseView
{
    if(shouldShowCloseView)
    {
        [m_pDragTab setDefaultStatesWithImageNames:@"button_close_off" :@"button_close_on"];
    }
    else
    {
        [m_pDragTab setDefaultStatesWithImageNames:@"button_search_off" :@"button_search_on"];
    }
}

@end
