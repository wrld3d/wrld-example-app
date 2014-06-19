// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ControlCityThemeExampleFactory.h"
#include "ControlCityThemeExample.h"

using namespace Examples;

ControlCityThemeExampleFactory::ControlCityThemeExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* ControlCityThemeExampleFactory::CreateExample() const
{
	return new Examples::ControlCityThemeExample(m_world.GetCityThemesService(),
	        m_world.GetCityThemesRepository(),
	        m_world.GetCityThemesUpdater(),
	        m_world,
	        m_globeCameraController);
}

std::string ControlCityThemeExampleFactory::ExampleName() const
{
	return Examples::ControlCityThemeExample::GetName();
}

