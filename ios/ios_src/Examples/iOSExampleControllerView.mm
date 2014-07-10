// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "iOSExampleControllerView.h"
#include "UIHelpers.h"
#include "iOSUIHelpers.h"

using namespace Examples;

@interface AvailableExamplesView : UIScrollView

@end

@implementation IExampleControllerViewBinding

iOSExampleControllerView* m_pInstance;
UIView* m_pView;
std::vector<std::string> m_exampleNames;
UIControl* m_pSelectionScreen;
int m_exampleSelectorWidth;

-(void) setExampleNames:(const std::vector<std::string>&)exampleNames
{
	m_exampleNames = exampleNames;
}

-(void) setBinding:(iOSExampleControllerView*)pInstance :(UIView*)pView :(int)exampleSelectorWidth
{
	m_pInstance = pInstance;
	m_pView = pView;
	m_pSelectionScreen = nil;
	m_exampleSelectorWidth = exampleSelectorWidth;
}

-(void) activateNext
{
	m_pInstance->ActivateNext();
}

-(void) activatePrevious
{
	m_pInstance->ActivatePrevious();
}

-(void)selectionHandler:(UIButton*)sender
{
	std::string name = sender.titleLabel.text.UTF8String;
	m_pInstance->SetCurrentExampleName(name);

	[m_pSelectionScreen removeFromSuperview];
	[m_pSelectionScreen release];
	m_pSelectionScreen = nil;
}

-(void) handleDismissSelectionScreen
{
	if(m_pSelectionScreen != nil)
	{
		[m_pSelectionScreen removeFromSuperview];
		[m_pSelectionScreen release];
		m_pSelectionScreen = nil;
	}
}

-(void) openExampleSelectionMenu
{
	CGRect screenRect = CGRectMake(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	m_pSelectionScreen = [[UIControl alloc] initWithFrame:screenRect];
	m_pSelectionScreen.backgroundColor = [[UIColor blackColor] colorWithAlphaComponent:0.8];

	UIScrollView* scroller = [[UIScrollView alloc] initWithFrame:CGRectMake((SCREEN_WIDTH/2) - m_exampleSelectorWidth/2, 50, m_exampleSelectorWidth, SCREEN_HEIGHT - 100)];

	const int buttonHeight = 30;

	for (int i = 0; i < m_exampleNames.size(); ++ i)
	{
		NSString* label = [NSString stringWithUTF8String:m_exampleNames[i].c_str()];
		UIButton* b = [UIButton buttonWithType:BUTTON_TYPE];
		b.frame = CGRectMake(0, (i * buttonHeight), m_exampleSelectorWidth, buttonHeight);

		[b setTitle:label forState:UIControlStateNormal];
        [b addTarget:self action:@selector(selectionHandler:) forControlEvents:UIControlEventTouchDown];
		[scroller addSubview:b];
	}

	scroller.contentSize = CGSizeMake(m_exampleSelectorWidth, buttonHeight * m_exampleNames.size());
	[m_pSelectionScreen addSubview:scroller];
	[scroller release];

	[m_pSelectionScreen addTarget:self action:@selector(handleDismissSelectionScreen) forControlEvents:UIControlEventTouchDragInside];
	[m_pSelectionScreen addTarget:self action:@selector(handleDismissSelectionScreen) forControlEvents:UIControlEventTouchUpInside];

	[m_pView addSubview:m_pSelectionScreen];
}

@end

namespace Examples
{
iOSExampleControllerView::iOSExampleControllerView(UIView* pView)
	: m_pView(pView)
{
	m_pBinding = [[IExampleControllerViewBinding alloc] init];

	float screenWidth = SCREEN_WIDTH;

    if(IS_IPAD)
    {
        m_pPreviousButton = [UIButton buttonWithType:BUTTON_TYPE];
        [m_pPreviousButton retain];
        m_pPreviousButton.frame = CGRectMake(10, 10, 100, 30);
        [m_pPreviousButton setBackgroundColor:[UIColor colorWithRed:0.0/255.0f green:0.0/255.0f blue:128.0/255.0f alpha:0.6]];
        [m_pPreviousButton setTitle:@"Previous" forState:UIControlStateNormal];
        [m_pPreviousButton addTarget:m_pBinding action:@selector(activatePrevious) forControlEvents:UIControlEventTouchDown];
        
        m_pNextButton = [UIButton buttonWithType:BUTTON_TYPE];
        [m_pNextButton retain];
        m_pNextButton.frame = CGRectMake(screenWidth - 110, 10, 100, 30);
        [m_pNextButton setBackgroundColor:[UIColor colorWithRed:0.0/255.0f green:0.0/255.0f blue:128.0/255.0f alpha:0.6]];
        [m_pNextButton setTitle:@"Next" forState:UIControlStateNormal];
        [m_pNextButton addTarget:m_pBinding action:@selector(activateNext) forControlEvents:UIControlEventTouchDown];
    }
    
	m_pSelectNewExampleButton = [UIButton buttonWithType:BUTTON_TYPE];
	[m_pSelectNewExampleButton retain];
	m_pSelectNewExampleButton.frame = CGRectMake(screenWidth/2 - 300, 20, 600, 30);
    [m_pSelectNewExampleButton setBackgroundColor:[UIColor colorWithRed:0.0/255.0f green:0.0/255.0f blue:128.0/255.0f alpha:0.6]];
	[m_pSelectNewExampleButton setTitle:@"" forState:UIControlStateNormal];
	[m_pSelectNewExampleButton addTarget:m_pBinding action:@selector(openExampleSelectionMenu) forControlEvents:UIControlEventTouchDown];

	[m_pBinding setBinding:this :m_pView :600];
}

iOSExampleControllerView::~iOSExampleControllerView()
{
    if(IS_IPAD)
    {
        [m_pNextButton removeFromSuperview];
        m_pNextButton = nil;
        
        [m_pPreviousButton removeFromSuperview];
        m_pPreviousButton = nil;
    }
    
	[m_pSelectNewExampleButton removeFromSuperview];
	m_pSelectNewExampleButton = nil;

	[m_pBinding release];
	m_pBinding = nil;
}

void iOSExampleControllerView::PopulateExampleList(const std::vector<std::string>& exampleNames)
{
	[m_pBinding setExampleNames: exampleNames];
}

void iOSExampleControllerView::Show()
{
    if(IS_IPAD)
    {
        [m_pView addSubview:m_pPreviousButton];
        [m_pView addSubview:m_pNextButton];
    }
	[m_pView addSubview:m_pSelectNewExampleButton];
}

void iOSExampleControllerView::SetCurrentExampleName(const std::string &name)
{
	NSString* s = [NSString stringWithUTF8String:name.c_str()];
	[m_pSelectNewExampleButton setTitle:s forState:UIControlStateNormal];

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
