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
		AndroidNativeState& nativeState)
: m_world(world)
, m_nativeState(nativeState)
{

}

IExample* JavaHudCrossThreadCommunicationExampleFactory::CreateExample() const
{
    return new Examples::JavaHudCrossThreadCommunicationExample(
    		m_nativeState,
    		m_world.GetCityThemesService(),
    		m_world.GetCityThemesRepository(),
    		m_world.GetCityThemesUpdater());
}
