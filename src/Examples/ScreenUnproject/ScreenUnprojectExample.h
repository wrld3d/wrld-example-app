#ifndef __ExampleApp__ScreenUnprojectExample__
#define __ExampleApp__ScreenUnprojectExample__

#include "IExample.h"
#include "Rendering.h"
#include "Terrain.h"
#include "Camera.h"
#include "DebugRendering.h"

namespace Examples
{
class ScreenUnprojectExample : public IExample
{
private:
	Eegeo::DebugRendering::SphereMesh* sphere;
	Eegeo::Rendering::RenderContext& renderContext;
	Eegeo::Camera::ICameraProvider& cameraProvider;
	Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

public:
	ScreenUnprojectExample(Eegeo::Rendering::RenderContext& renderContext,
	                       Eegeo::Camera::ICameraProvider& cameraProvider,
	                       Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
	                       Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController);

	static std::string GetName()
	{
		return "ScreenUnprojectExample";
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


#endif /* defined(__ExampleApp__DebugSphereExample__) */
