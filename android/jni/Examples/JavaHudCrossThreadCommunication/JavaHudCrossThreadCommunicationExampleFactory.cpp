/*
 * JavaHudCrossThreadCommunicationExampleFactory.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: kimbleoperations
 */

#include "JavaHudCrossThreadCommunicationExampleFactory.h"
#include "JavaHudCrossThreadCommunicationExample.h"
#include "JavaHudCrossThreadCommunicationProxy.h"

using namespace Examples;

JavaHudCrossThreadCommunicationExampleFactory::JavaHudCrossThreadCommunicationExampleFactory(
    Eegeo::EegeoWorld& world,
    AndroidNativeState& nativeState,
    Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue,
    Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_nativeState(nativeState)
	, m_messageQueue(messageQueue)
	, m_globeCameraController(globeCameraController)
{

}

IExample* JavaHudCrossThreadCommunicationExampleFactory::CreateExample() const
{
	JavaHudCrossThreadCommunicationProxy* pProxy = Eegeo_NEW(JavaHudCrossThreadCommunicationProxy)(m_messageQueue);

	return new Examples::JavaHudCrossThreadCommunicationExample(
	           m_nativeState,
	           pProxy,
	           m_world.GetCityThemesService(),
	           m_world.GetCityThemesRepository(),
	           m_world.GetCityThemesUpdater(),
	           m_globeCameraController);
}

std::string JavaHudCrossThreadCommunicationExampleFactory::ExampleName() const
{
	return Examples::JavaHudCrossThreadCommunicationExample::GetName();
}
