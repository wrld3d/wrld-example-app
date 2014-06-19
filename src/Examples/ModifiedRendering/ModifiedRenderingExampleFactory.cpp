// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ModifiedRenderingExampleFactory.h"
#include "ModifiedRenderingExample.h"

using namespace Examples;

ModifiedRenderingExampleFactory::ModifiedRenderingExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* ModifiedRenderingExampleFactory::CreateExample() const
{
	return new Examples::ModifiedRenderingExample(m_world.GetRenderContext(),
	        m_world.GetCameraProvider(),
	        m_world.GetInterestPointProvider(),
	        m_world.GetStreamingVolume(),
	        m_world.GetGlobalLighting(),
	        m_world.GetBuildingSceneElementRepository(),
	        m_world.GetBuildingsRenderableFilter(),
	        m_world.GetRenderQueue(),
	        m_world.GetRenderableFilters(),
	        m_world.GetShaderIdGenerator(),
	        m_world.GetMaterialIdGenerator(),
	        m_world.GetEnvironmentPlaceholderTexture(),
	        m_globeCameraController);
}

std::string ModifiedRenderingExampleFactory::ExampleName() const
{
	return Examples::ModifiedRenderingExample::GetName();
}

