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

-(void) setExampleNames:(const std::vector<std::string>&)exampleNames;
-(void) setBinding:(Examples::iOSExampleControllerView*)pInstance :(UIView*)pView :(int)exampleSelectorWidth;
-(void) activateNext;
-(void) activatePrevious;
-(void) openExampleSelectionMenu;

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
	UIButton* m_pSelectNewExampleButton;
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

	void PopulateExampleList(const std::vector<std::string>& exampleNames);
};
}

#endif /* defined(__ExampleApp__ExampleControllerView__) */
