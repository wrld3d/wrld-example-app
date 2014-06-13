// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__EnvironmentNotifierExample__
#define __ExampleApp__EnvironmentNotifierExample__

#include <map>

#include "IExample.h"
#include "RenderContext.h"
#include "SphereMesh.h"
#include "LatLongAltitude.h"
#include "TerrainStreaming.h"
#include "IStreamingObserver.h"
#include "MortonKey.h"

namespace Examples
{
class EnvironmentNotifierExampleTerrainStreamObserver : public Eegeo::Streaming::IStreamingObserver
{
private:
	Eegeo::Rendering::RenderContext& m_renderContext;
	std::map<Eegeo::Streaming::MortonKey, Eegeo::DebugRendering::SphereMesh*, Eegeo::Streaming::MortonKeyCompare>& m_renderables;

	void AddSphere(const Eegeo::Streaming::MortonKey& key);
public:
	EnvironmentNotifierExampleTerrainStreamObserver(Eegeo::Rendering::RenderContext& renderContext,
	        std::map<Eegeo::Streaming::MortonKey, Eegeo::DebugRendering::SphereMesh*, Eegeo::Streaming::MortonKeyCompare>& renderables)
		:m_renderables(renderables)
		,m_renderContext(renderContext)
	{

	}

	void AddedStreamingResourceToSceneGraph(const Eegeo::Streaming::MortonKey& key);
	void RemovedStreamingResourceFromSceneGraph(const Eegeo::Streaming::MortonKey& key);
};

class EnvironmentNotifierExample : public IExample
{
private:
	Eegeo::Rendering::RenderContext& m_renderContext;
	Eegeo::Resources::Terrain::TerrainStreaming& m_terrainStreaming;
	EnvironmentNotifierExampleTerrainStreamObserver* m_pObserver;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

	std::map<Eegeo::Streaming::MortonKey, Eegeo::DebugRendering::SphereMesh*, Eegeo::Streaming::MortonKeyCompare> m_renderables;


public:
	EnvironmentNotifierExample(Eegeo::Rendering::RenderContext& renderContext,
	                           Eegeo::Resources::Terrain::TerrainStreaming& terrainStreaming,
	                           Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController);

	static std::string GetName()
	{
		return "EnvironmentNotifierExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start();
	void Update(float dt);
	void Draw();
	void Suspend();
};
}


#endif /* defined(__ExampleApp__EnvironmentNotifierExample__) */
