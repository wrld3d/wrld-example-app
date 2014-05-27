//
//  ExampleControllerView.cpp
//  ExampleApp
//
//  Created by Scott on 23/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "iOSExampleControllerView.h"
#include "UIHelpers.h"

#define SCREEN_WIDTH ((([UIApplication sharedApplication].statusBarOrientation == UIInterfaceOrientationPortrait) || ([UIApplication sharedApplication].statusBarOrientation == UIInterfaceOrientationPortraitUpsideDown)) ? [[UIScreen mainScreen] bounds].size.width : [[UIScreen mainScreen] bounds].size.height)
#define SCREEN_HEIGHT ((([UIApplication sharedApplication].statusBarOrientation == UIInterfaceOrientationPortrait) || ([UIApplication sharedApplication].statusBarOrientation == UIInterfaceOrientationPortraitUpsideDown)) ? [[UIScreen mainScreen] bounds].size.height : [[UIScreen mainScreen] bounds].size.width)

using namespace Examples;

@implementation IExampleControllerViewBinding

Examples::iOSExampleControllerView* m_pInstance;

-(void) setBoundInstance:(iOSExampleControllerView*)pInstance
{
    m_pInstance = pInstance;
}

-(void) activateNext
{
    m_pInstance->ActivateNext();
}

-(void) activatePrevious
{
    m_pInstance->ActivatePrevious();
}

@end

namespace Examples
{
    iOSExampleControllerView::iOSExampleControllerView(UIView* pView)
    : m_pView(pView)
    {
        m_pBinding = [[IExampleControllerViewBinding alloc] init];
        
        float screenWidth = SCREEN_WIDTH;
        
        m_pPreviousButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        [m_pPreviousButton retain];
        m_pPreviousButton.frame = CGRectMake(10, 10, 100, 30);
        [m_pPreviousButton setTitle:@"Previous" forState:UIControlStateNormal];
        [m_pPreviousButton addTarget:m_pBinding action:@selector(activatePrevious) forControlEvents:UIControlEventTouchDown];
        
        m_pNextButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        [m_pNextButton retain];
        m_pNextButton.frame = CGRectMake(screenWidth - 110, 10, 100, 30);
        [m_pNextButton setTitle:@"Next" forState:UIControlStateNormal];
        [m_pNextButton addTarget:m_pBinding action:@selector(activateNext) forControlEvents:UIControlEventTouchDown];
        
        [m_pBinding setBoundInstance:this];
        
        m_pLabel = [[UILabel alloc]initWithFrame:CGRectMake(screenWidth/2 - 300, 10, 600, 30)];
        m_pLabel.textAlignment = UITextAlignmentCenter;
        [m_pView addSubview:m_pLabel];
    }
    
    iOSExampleControllerView::~iOSExampleControllerView()
    {
        [m_pNextButton removeFromSuperview];
        m_pNextButton = nil;
        
        [m_pPreviousButton removeFromSuperview];
        m_pPreviousButton = nil;
        
        [m_pLabel removeFromSuperview];
        m_pLabel = nil;
        
        [m_pBinding release];
        m_pBinding = nil;
    }
    
    void iOSExampleControllerView::Show()
    {
        [m_pView addSubview:m_pPreviousButton];
        [m_pView addSubview:m_pNextButton];
    }
    
    void iOSExampleControllerView::SetCurrentExampleName(const std::string &name)
    {
        m_pLabel.text = [NSString stringWithUTF8String:name.c_str()];
        m_selectedExample = name;
        UpdateSelectedExample();
    }
    
    void iOSExampleControllerView::AddSelectPreviousExampleHandler(IUIActionHandler& handler)
    {
        m_previousHandlers.push_back(&handler);
    }
    
    void iOSExampleControllerView::RemoveSelectPreviousExampleHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_previousHandlers, &handler);
    }
    
    void iOSExampleControllerView::ActivatePrevious()
    {
        InvokeAllHandlers(m_previousHandlers);
    }
    
    void iOSExampleControllerView::AddSelectNextExampleHandler(IUIActionHandler& handler)
    {
        m_nextHandlers.push_back(&handler);
    }
    
    void iOSExampleControllerView::RemoveSelectNextExampleHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_nextHandlers, &handler);
    }
    
    void iOSExampleControllerView::ActivateNext()
    {
        InvokeAllHandlers(m_nextHandlers);
    }
    
    void iOSExampleControllerView::AddExampleSelectedHandler(IUIActionHandler& handler)
    {
        m_exampleUpdatedHandlers.push_back(&handler);
    }
    
    void iOSExampleControllerView::RemoveExampleSelectedHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_exampleUpdatedHandlers, &handler);
    }
    
    void iOSExampleControllerView::UpdateSelectedExample()
    {
        InvokeAllHandlers(m_exampleUpdatedHandlers);
    }
    
    std::string iOSExampleControllerView::GetSelectedExample()
    {
        return m_selectedExample;
    }
}
