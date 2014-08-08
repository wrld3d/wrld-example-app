// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__DebugPrimitiveRenderingExample__
#define __ExampleApp__DebugPrimitiveRenderingExample__

#include "DebugRendering.h"
#include "IExample.h"

namespace Examples
{
class DebugPrimitiveRenderingExample : public Examples::IExample
{
private:
	Eegeo::DebugRendering::DebugRenderer& m_debugRenderer;
    const Eegeo::Camera::RenderCamera& m_camera;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;
    float m_frustumDrawTimer;

public:
	DebugPrimitiveRenderingExample(Eegeo::DebugRendering::DebugRenderer &debugRenderer,
                                   const Eegeo::Camera::RenderCamera& camera,
	                               Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController);

	static std::string GetName()
	{
		return "DebugPrimitiveRenderingExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start();
	void Update(float dt);
	void Draw();
	void Suspend();
};
}


#endif /* defined(__ExampleApp__DebugPrimitiveRenderingExample__) */
