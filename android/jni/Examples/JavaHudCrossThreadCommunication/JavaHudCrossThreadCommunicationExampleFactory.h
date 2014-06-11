/*
 * JavaHudCrossThreadCommunicationExampleFactory.h
 *
 *  Created on: Dec 10, 2013
 *      Author: kimbleoperations
 */

#ifndef JAVAHUDCROSSTHREADCOMMUNICATIONEXAMPLEFACTORY_H_
#define JAVAHUDCROSSTHREADCOMMUNICATIONEXAMPLEFACTORY_H_

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"
#include "AndroidNativeState.h"
#include "MessageQueue.h"
#include "IAndroidExampleMessage.h"

namespace Examples
{
class JavaHudCrossThreadCommunicationExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
	AndroidNativeState& m_nativeState;
	Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& m_messageQueue;
	Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;

public:
	JavaHudCrossThreadCommunicationExampleFactory(
	    Eegeo::EegeoWorld& world,
	    AndroidNativeState& nativeState,
	    Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue,
	    Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}


#endif /* JAVAHUDCROSSTHREADCOMMUNICATIONEXAMPLEFACTORY_H_ */
