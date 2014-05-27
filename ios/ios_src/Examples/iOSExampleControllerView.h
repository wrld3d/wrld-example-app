//
//  ExampleControllerView.h
//  ExampleApp
//
//  Created by Scott on 23/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__ExampleControllerView__
#define __ExampleApp__ExampleControllerView__

#include "Types.h"
#include "IExampleControllerView.h"
#include "IUIActionHandler.h"
#import <UIKit/UIKit.h>
#include <vector>
#include <string>

namespace Examples
{
    class iOSExampleControllerView;
}

@interface IExampleControllerViewBinding : NSObject

-(void) setBoundInstance:(Examples::iOSExampleControllerView*)pExample;
-(void) activateNext;
-(void) activatePrevious;

@end

namespace Examples
{
    class iOSExampleControllerView : public IExampleControllerView, private Eegeo::NonCopyable
    {
        std::vector<IUIActionHandler*> m_exampleUpdatedHandlers;
        std::vector<IUIActionHandler*> m_nextHandlers;
        std::vector<IUIActionHandler*> m_previousHandlers;
        UIView* m_pView;
        UIButton * m_pNextButton;
        UIButton * m_pPreviousButton;
        UILabel* m_pLabel;
        IExampleControllerViewBinding* m_pBinding;
        std::string m_selectedExample;
        
    public:
        iOSExampleControllerView(UIView* pView);
        
        ~iOSExampleControllerView();
        
        void Show();
        
        void SetCurrentExampleName(const std::string& name);
        
        void AddSelectPreviousExampleHandler(IUIActionHandler& handler);
        
        void RemoveSelectPreviousExampleHandler(IUIActionHandler& handler);
        
        void AddSelectNextExampleHandler(IUIActionHandler& handler);
        
        void RemoveSelectNextExampleHandler(IUIActionHandler& handler);
        
        void AddExampleSelectedHandler(IUIActionHandler& handler);
        
        void RemoveExampleSelectedHandler(IUIActionHandler& handler);
        
        std::string GetSelectedExample();
        
        void UpdateSelectedExample();
        
        void ActivateNext();
        
        void ActivatePrevious();
    };
}

#endif /* defined(__ExampleApp__ExampleControllerView__) */
