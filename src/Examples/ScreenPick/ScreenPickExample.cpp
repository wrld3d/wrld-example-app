// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ScreenPickExample.h"
#include "CameraHelpers.h"
#include "ICameraProvider.h"
#include "EarthConstants.h"
#include "SphereMesh.h"
#include "TerrainHeightProvider.h"
#include "RenderCamera.h"
#include "TerrainRayPicker.h"

namespace Examples
{
ScreenPickExample::ScreenPickExample(Eegeo::Rendering::RenderContext& renderContext,
                                     Eegeo::Camera::ICameraProvider& cameraProvider,
                                     Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                                     const Eegeo::Resources::Terrain::Collision::ICollisionMeshResourceProvider& collisionMeshResourceProvider,
                                     Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController)
	: m_renderContext(renderContext)
	, m_cameraProvider(cameraProvider)
	, m_globeCameraStateRestorer(cameraController)
{
	const float radius = 20.f;
	const int numSegments = 16;
	const Eegeo::v3 red(1.f, 0.f, 0.f);

	m_pSphere = new Eegeo::DebugRendering::SphereMesh(
	    renderContext,
	    radius,
	    numSegments, numSegments,
	    Eegeo::dv3(),
	    NULL,
	    red
	);
	m_pSphere->Tesselate();

	m_pRayPicker = new Eegeo::Resources::Terrain::Collision::TerrainRayPicker(terrainHeightProvider, collisionMeshResourceProvider);
}

ScreenPickExample::~ScreenPickExample()
{
	delete m_pRayPicker;
	delete m_pSphere;
}

void ScreenPickExample::Start()
{

}

void ScreenPickExample::Suspend()
{

}

void ScreenPickExample::Update(float dt)
{

}

void ScreenPickExample::Draw()
{
	m_pSphere->Draw(m_renderContext);
}

bool ScreenPickExample::Event_TouchTap(const AppInterface::TapData& data)
{
	const Eegeo::Camera::RenderCamera& renderCamera = m_cameraProvider.GetRenderCamera();

	float screenPixelX = data.point.GetX();
	float screenPixelY = data.point.GetY();

	Eegeo::dv3 rayOrigin = renderCamera.GetEcefLocation();
	Eegeo::dv3 rayDirection;
	Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPixelX, screenPixelY, rayDirection);

	Eegeo::dv3 rayIntersectionPoint;
	double intersectionParam;
	bool rayPick = m_pRayPicker->TryGetRayIntersection(rayOrigin, rayDirection, rayIntersectionPoint, intersectionParam);
	if (rayPick)
	{
		m_pSphere->SetPositionECEF(rayIntersectionPoint);
	}

	return true;
}
}