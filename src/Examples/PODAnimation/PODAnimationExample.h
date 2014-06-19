// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__PODAnimationExample__
#define __ExampleApp__PODAnimationExample__

#include "IExample.h"
#include "RenderContext.h"
#include "LatLongAltitude.h"

#include "Model.h"

namespace Examples
{
class PODAnimationExample : public IExample
{
private:

	Eegeo::Rendering::RenderContext& m_renderContext;
	Eegeo::Helpers::IFileIO& m_fileIO;
	Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& m_textureRequestor;
	Eegeo::Lighting::GlobalFogging& m_globalFogging;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

	Eegeo::Model* m_pModel;

public:
	PODAnimationExample(Eegeo::Rendering::RenderContext& renderContext,
	                    Eegeo::Helpers::IFileIO& fileIO,
	                    Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor,
	                    Eegeo::Lighting::GlobalFogging& fogging,
	                    Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController);

	static std::string GetName()
	{
		return "PODAnimationExample";
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


#endif /* defined(__ExampleApp__PODAnimationExample__) */
