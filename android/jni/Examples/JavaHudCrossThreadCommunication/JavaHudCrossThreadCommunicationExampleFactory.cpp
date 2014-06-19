// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "JavaHudCrossThreadCommunicationExampleFactory.h"
#include "JavaHudCrossThreadCommunicationExample.h"
#include "JavaHudCrossThreadCommunicationProxy.h"

using namespace Examples;

JavaHudCrossThreadCommunicationExampleFactory::JavaHudCrossThreadCommunicationExampleFactory(
    Eegeo::EegeoWorld& world,
    AndroidNativeState& nativeState,
    Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_nativeState(nativeState)
	, m_globeCameraController(globeCameraController)
{

}

IExample* JavaHudCrossThreadCommunicationExampleFactory::CreateExample() const
{
	return new Examples::JavaHudCrossThreadCommunicationExample(
	           m_nativeState,
	           m_world.GetCityThemesService(),
	           m_world.GetCityThemesRepository(),
	           m_world.GetCityThemesUpdater(),
	           m_globeCameraController);
}

std::string JavaHudCrossThreadCommunicationExampleFactory::ExampleName() const
{
	return Examples::JavaHudCrossThreadCommunicationExample::GetName();
}
