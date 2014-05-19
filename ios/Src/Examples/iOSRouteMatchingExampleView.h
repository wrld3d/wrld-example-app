//
//  iOSRouteMatchingExampleView.h
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__iOSRouteMatchingExampleView__
#define __ExampleApp__iOSRouteMatchingExampleView__

#include "Types.h"
#include "IRouteMatchingView.h"
#import <UIKit/UIKit.h>
#include <vector>

namespace Examples
{
    class iOSRouteMatchingExampleView;
}

@interface IRouteMatchingExampleBinding : NSObject

-(void) setExampleInstance:(Examples::iOSRouteMatchingExampleView*)pExample :(UIButton*)pToggleMatching;
-(void) toggleMatching;

@end

namespace Examples
{
    class iOSRouteMatchingExampleView : public IRouteMatchingView, private Eegeo::NonCopyable
    {
        std::vector<IUIActionHandler*> m_matchingToggledHandlers;
        UIView* m_pView;
        UIButton * m_pToggleMatchingButton;
        IRouteMatchingExampleBinding* m_pBinding;
        
    public:
        iOSRouteMatchingExampleView(UIView* pView);
        
        ~iOSRouteMatchingExampleView();
        
        void AddMatchingToggledHandler(IUIActionHandler& handler);
        
        void RemoveMatchingToggledHandler(IUIActionHandler& handler);
        
        void ToggleMatching();
    };
}

#endif /* defined(__ExampleApp__iOSRouteMatchingExampleView__) */
