// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__DebugPrimitiveRenderingExampleFactory__
#define __ExampleApp__DebugPrimitiveRenderingExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"

namespace Examples
{
class DebugPrimitiveRenderingExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
	Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;

public:
	DebugPrimitiveRenderingExampleFactory(Eegeo::EegeoWorld& world,
	                                      Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}


#endif /* defined(__ExampleApp__DebugPrimitiveRenderingExampleFactory__) */
