// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__AndroidRouteMatchingExampleView__
#define __ExampleApp__AndroidRouteMatchingExampleView__

#include "Types.h"
#include "IRouteMatchingExampleView.h"
#include "AndroidNativeState.h"
#include <vector>

namespace Examples
{
class AndroidRouteMatchingExampleView : public IRouteMatchingExampleView, private Eegeo::NonCopyable
{
	std::vector<IUIActionHandler*> m_matchingToggledHandlers;
	AndroidNativeState& m_nativeState;
	jclass m_routeMatchingExampleHudClass;
	jobject m_routeMatchingExampleHud;

public:
	AndroidRouteMatchingExampleView(AndroidNativeState& androidNativeState);

	~AndroidRouteMatchingExampleView();

	void AddMatchingToggledHandler(IUIActionHandler& handler);

	void RemoveMatchingToggledHandler(IUIActionHandler& handler);

	void ToggleMatching();
};
}

#endif /* defined(__ExampleApp__AndroidRouteMatchingExampleView__) */
