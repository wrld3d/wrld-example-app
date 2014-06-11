/*
 * PositionJavaPinButtonExampleFactory.h
 *
 *  Created on: Dec 10, 2013
 *      Author: kimbleoperations
 */

#ifndef POSITIONJAVAPINBUTTONEXAMPLEFACTORY_H_
#define POSITIONJAVAPINBUTTONEXAMPLEFACTORY_H_

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"
#include "AndroidNativeState.h"

namespace Examples
{
class PositionJavaPinButtonExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
	AndroidNativeState& m_nativeState;
	Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;

public:
	PositionJavaPinButtonExampleFactory(
	    Eegeo::EegeoWorld& world,
	    AndroidNativeState& nativeState,
	    Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}


#endif /* POSITIONJAVAPINBUTTONEXAMPLEFACTORY_H_ */
