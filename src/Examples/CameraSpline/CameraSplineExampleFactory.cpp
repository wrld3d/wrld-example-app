// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CameraSplineExampleFactory.h"
#include "CameraSplineExample.h"
#include "EegeoWorld.h"
#include "GlobeCameraController.h"
#include "ResourceCeilingProvider.h"

using namespace Examples;

CameraSplineExampleFactory::CameraSplineExampleFactory(Eegeo::EegeoWorld& world,
                                                       Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
: m_world(world)
, m_globeCameraController(globeCameraController)
{
    
}

IExample* CameraSplineExampleFactory::CreateExample() const
{
	return new Examples::CameraSplineExample(m_world,
                                             m_globeCameraController,
                                             m_world.GetResourceCeilingProvider());
}

std::string CameraSplineExampleFactory::ExampleName() const
{
	return Examples::CameraSplineExample::GetName();
}
