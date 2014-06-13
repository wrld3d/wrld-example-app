// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef PINSWITHATTACHEDUIEXAMPLEFACTORY_H_
#define PINSWITHATTACHEDUIEXAMPLEFACTORY_H_

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"
#include "AndroidNativeState.h"

namespace Examples
{
class PinsWithAttachedJavaUIExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
	AndroidNativeState& m_nativeState;
	Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;

public:
	PinsWithAttachedJavaUIExampleFactory(
	    Eegeo::EegeoWorld& world,
	    AndroidNativeState& nativeState,
	    Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}


#endif /* PINSWITHATTACHEDUIEXAMPLEFACTORY_H_ */
