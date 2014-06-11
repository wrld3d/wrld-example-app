#ifndef __ExampleApp__DebugPrimitiveRenderingExample__
#define __ExampleApp__DebugPrimitiveRenderingExample__

#include "IExample.h"

namespace Eegeo
{
namespace DebugRendering
{
class DebugPrimitiveRenderer;
}
}

namespace Examples
{
class DebugPrimitiveRenderingExample : public Examples::IExample
{
private:
	Eegeo::DebugRendering::DebugPrimitiveRenderer& m_debugPrimitiveRenderer;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

public:
	DebugPrimitiveRenderingExample(Eegeo::DebugRendering::DebugPrimitiveRenderer &debugPrimitiveRenderer,
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
