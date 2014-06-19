// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "EnvironmentNotifierExample.h"
#include "CubeMapCellInfo.h"

#define SPHERE_HEIGHT_ABOVE_SEA 10.0

namespace Examples
{
//EnvironmentNotifierExample//
EnvironmentNotifierExample::EnvironmentNotifierExample(Eegeo::Rendering::RenderContext& renderContext,
        Eegeo::Resources::Terrain::TerrainStreaming& terrainStreaming,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController)
	:m_renderContext(renderContext)
	,m_terrainStreaming(terrainStreaming)
	,m_pObserver(NULL)
	,m_globeCameraStateRestorer(cameraController)
{
}

void EnvironmentNotifierExample::Start()
{
	m_pObserver = new EnvironmentNotifierExampleTerrainStreamObserver(m_renderContext, m_renderables);
	m_terrainStreaming.AddStreamingObserver(m_pObserver);
}

void EnvironmentNotifierExample::Suspend()
{
	m_terrainStreaming.RemoveStreamingObserver(m_pObserver);
	delete m_pObserver;
	m_pObserver = NULL;
}

void EnvironmentNotifierExample::Update(float dt)
{
}


void EnvironmentNotifierExample::Draw()
{
	//draw all the spheres
	for(std::map<Eegeo::Streaming::MortonKey, Eegeo::DebugRendering::SphereMesh*>::iterator
	        it = m_renderables.begin(); it != m_renderables.end(); ++ it)
	{
		Eegeo::DebugRendering::SphereMesh& mesh = *(*it).second;
		mesh.Draw(m_renderContext);
	}
}


//EnvironmentNotifierExampleTerrainStreamObserver///
void EnvironmentNotifierExampleTerrainStreamObserver::AddSphere(const Eegeo::Streaming::MortonKey& key)
{
	Eegeo::Space::CubeMap::CubeMapCellInfo cellInfo(key);
	const Eegeo::dv2& resourceQuadtreeCellCenter = cellInfo.GetFaceCentre();
	Eegeo::dv3 worldSpaceCellCenter = Eegeo::Space::CubeMap::FacePointToWorld(cellInfo.GetFaceIndex(),
	                                  resourceQuadtreeCellCenter,
	                                  Eegeo::Space::EarthConstants::CubeSideLengthHalf);


	Eegeo::dv3 up = worldSpaceCellCenter.Norm();
	Eegeo::dv3 spherePosition = Eegeo::dv3::Scale(up, Eegeo::Space::EarthConstants::Radius + SPHERE_HEIGHT_ABOVE_SEA);

	Eegeo::v3 color(1.f, 0.f, 1.f);

	Eegeo::DebugRendering::SphereMesh* sphere = new Eegeo::DebugRendering::SphereMesh(
	    m_renderContext,
	    20.0f,
	    16, 16,
	    spherePosition,
	    NULL,
	    color
	);
	sphere->Tesselate();

	m_renderables.insert(std::make_pair(key,sphere));
}

void EnvironmentNotifierExampleTerrainStreamObserver::AddedStreamingResourceToSceneGraph(const Eegeo::Streaming::MortonKey& key)
{
	Eegeo_TTY("Adding Terrain Resource :: %s\n", key.ToString().c_str());
	AddSphere(key);
}

void EnvironmentNotifierExampleTerrainStreamObserver::RemovedStreamingResourceFromSceneGraph(const Eegeo::Streaming::MortonKey& key)
{
	Eegeo_TTY("Removing Terrain Resource :: %s\n", key.ToString().c_str());
	m_renderables.erase(key);
}
}
