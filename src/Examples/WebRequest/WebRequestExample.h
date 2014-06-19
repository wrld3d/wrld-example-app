// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__WebRequestExample__
#define __ExampleApp__WebRequestExample__

#include "IExample.h"

#include "IWebLoadRequestFactory.h"
#include "WebLoadRequestCompletionCallback.h"
#include "IWebLoadRequest.h"

namespace Examples
{
class WebRequestExample : public IExample
{
private:
	Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

public:
	WebRequestExample(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
	                  Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController);

	static std::string GetName()
	{
		return "WebRequestExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start();
	void Update(float dt) {}
	void Draw() {}
	void Suspend() {}
};
}


#endif /* defined(__ExampleApp__WebRequestExample__) */
