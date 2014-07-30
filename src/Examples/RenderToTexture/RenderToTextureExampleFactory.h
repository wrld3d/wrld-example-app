// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__RenderToTextureExampleFactory__
#define __ExampleApp__RenderToTextureExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"

namespace Examples
{
class RenderToTextureExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
	Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;
    
public:
	RenderToTextureExampleFactory(Eegeo::EegeoWorld& world,
                                  Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController);
    
	std::string ExampleName() const;
    
	IExample* CreateExample() const;
};
}

#endif /* defined(__ExampleApp__RenderToTextureExampleFactory__) */
