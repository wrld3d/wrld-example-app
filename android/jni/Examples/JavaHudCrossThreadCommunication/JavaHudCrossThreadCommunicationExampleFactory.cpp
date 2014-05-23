/*
 * JavaHudCrossThreadCommunicationExampleFactory.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: kimbleoperations
 */

#include "JavaHudCrossThreadCommunicationExampleFactory.h"
#include "JavaHudCrossThreadCommunicationExample.h"

using namespace Examples;

JavaHudCrossThreadCommunicationExampleFactory::JavaHudCrossThreadCommunicationExampleFactory(
		Eegeo::EegeoWorld& world,
		AndroidNativeState& nativeState,
    	Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue)
: m_world(world)
, m_nativeState(nativeState)
, m_messageQueue(messageQueue)
{

}

IExample* JavaHudCrossThreadCommunicationExampleFactory::CreateExample() const
{
    return new Examples::JavaHudCrossThreadCommunicationExample(
    		m_nativeState,
    		m_messageQueue,
    		m_world.GetCityThemesService(),
    		m_world.GetCityThemesRepository(),
    		m_world.GetCityThemesUpdater());
}
