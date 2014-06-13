// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__iOSRouteMatchingExampleView__
#define __ExampleApp__iOSRouteMatchingExampleView__

#include "Types.h"
#include "IRouteMatchingExampleView.h"
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
class iOSRouteMatchingExampleView : public IRouteMatchingExampleView, private Eegeo::NonCopyable
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
