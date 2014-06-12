//
//  Pick3DObjectExample.cpp
//  ExampleApp
//
//  Created by Scott on 03/10/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#include "Pick3DObjectExample.h"
#include "Plane.h"
#include "ICameraProvider.h"
#include "RenderCamera.h"

#define SPHERE_RADIUS 20.0
#define UNPICKED_COLOUR Eegeo::v3(1.0f, 0.0f, 1.0f)
#define PICKED_COLOUR Eegeo::v3(1.0f, 1.0f, 0.0f)

namespace Examples
{
Pick3DObjectExample::Pick3DObjectExample(Eegeo::Rendering::RenderContext& renderContext,
        Eegeo::Space::LatLongAltitude interestLocation,
        Eegeo::Camera::ICameraProvider& cameraProvider,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController)
	:m_renderContext(renderContext)
	,m_interestLocation(interestLocation)
	,m_cameraProvider(cameraProvider)
	,m_movingObject(false)
	,m_pObject(NULL)
	,m_globeCameraStateRestorer(cameraController)
{

}

void Pick3DObjectExample::Start()
{
	m_movingObject = false;

	Eegeo::Space::LatLongAltitude objectStartLocation = m_interestLocation;
	objectStartLocation.SetAltitude(200.0f);
	m_objectLocationEcef = objectStartLocation.ToECEF();

	CreateSphereAtLocation(m_objectLocationEcef, UNPICKED_COLOUR);
}

void Pick3DObjectExample::Suspend()
{
	delete m_pObject;
	m_pObject = NULL;
}

void Pick3DObjectExample::Update(float dt)
{
	m_pObject->SetPositionECEF(m_objectLocationEcef);
}

void Pick3DObjectExample::Draw()
{
	m_pObject->Draw(m_renderContext);
}

bool Pick3DObjectExample::Event_TouchPan(const AppInterface::PanData& data)
{
	return m_movingObject;
}

bool Pick3DObjectExample::Event_TouchDown(const AppInterface::TouchData& data)
{
	bool insideSphere = IsScreenPointInsideModel(data.point);

	if(insideSphere)
	{
		CreateSphereAtLocation(m_objectLocationEcef, PICKED_COLOUR);
		m_movingObject = true;
	}

	return m_movingObject;
}

bool Pick3DObjectExample::Event_TouchUp(const AppInterface::TouchData& data)
{
	m_movingObject = false;

	CreateSphereAtLocation(m_objectLocationEcef, UNPICKED_COLOUR);

	return m_movingObject;
}

void Pick3DObjectExample::CreateWorldSpaceRayFromScreen(const Eegeo::v2& screenPoint, Ray& ray)
{
	const Eegeo::Camera::RenderCamera& renderCamera = m_cameraProvider.GetRenderCamera();

	//normalize the point
	double nx = 2.0 * screenPoint.GetX() / m_renderContext.GetScreenWidth() - 1;
	double ny = - 2.0 * screenPoint.GetY() / m_renderContext.GetScreenHeight() + 1;

	//prepare near and far points
	Eegeo::v4 near(nx, ny, 0.0f, 1.0);
	Eegeo::v4 far(nx, ny, 1.0f, 1.0);

	Eegeo::m44 invVP;
	Eegeo::m44::Inverse(invVP, renderCamera.GetViewProjectionMatrix());

	//unproject the points
	Eegeo::v4 unprojectedNear = Eegeo::v4::Mul(near, invVP);
	Eegeo::v4 unprojectedFar = Eegeo::v4::Mul(far, invVP);

	//convert to 3d
	Eegeo::v3 unprojectedNearWorld = unprojectedNear / unprojectedNear.GetW();
	Eegeo::v3 unprojectedFarWorld = unprojectedFar / unprojectedFar.GetW();

	//check intersection with a ray cast from camera position
	ray.m_origin = renderCamera.GetEcefLocation();
	ray.m_direction = (unprojectedNearWorld - unprojectedFarWorld).Norm();
}

bool Pick3DObjectExample::IsScreenPointInsideModel(const Eegeo::v2& screenPoint)
{
	Ray ray;
	CreateWorldSpaceRayFromScreen(screenPoint, ray);
	ray.m_origin -= m_objectLocationEcef; //make object space

	//the following is a standard ray sphere intersection - for other shapes, an appropriate intersection method
	//should be used

	float a =
	    ray.m_direction.GetX() * ray.m_direction.GetX()
	    + ray.m_direction.GetY() * ray.m_direction.GetY()
	    + ray.m_direction.GetZ() * ray.m_direction.GetZ();

	float b =
	    ray.m_direction.GetX() * (2.0 * ray.m_origin.GetX())
	    + ray.m_direction.GetY() * (2.0 * ray.m_origin.GetY())
	    + ray.m_direction.GetZ() * (2.0 * ray.m_origin.GetZ());

	float c =
	    (ray.m_origin.GetX() * ray.m_origin.GetX()
	     + ray.m_origin.GetY() * ray.m_origin.GetY()
	     + ray.m_origin.GetZ() * ray.m_origin.GetZ());

	c -= (SPHERE_RADIUS * SPHERE_RADIUS);

	double d = b * b + (-4.0) * a * c;

	//if determinant is negative sphere is in negative ray direction so can't hit
	if (d < 0.0)
	{
		return false;
	}

	d = sqrt(d);

	double t = (-0.5) * (b - d) / a;

	if (t >= 0.0)
	{
		return false;
	}

	return true;
}

void Pick3DObjectExample::CreateSphereAtLocation(const Eegeo::dv3& location, const Eegeo::v3& colour)
{
	//assumes sphere is null if not validly allocated so this delete is always safe
	Eegeo_DELETE m_pObject;

	m_pObject = new Eegeo::DebugRendering::SphereMesh(m_renderContext,
	        SPHERE_RADIUS,
	        16, 16, //tessellation parameters
	        m_objectLocationEcef,
	        NULL, //no texture, just color
	        colour);
	m_pObject->Tesselate();
}
}
