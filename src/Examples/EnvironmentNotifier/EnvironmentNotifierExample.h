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
        Eegeo::Rendering::RenderContext& renderContext;
        std::map<Eegeo::Streaming::MortonKey, Eegeo::DebugRendering::SphereMesh*, Eegeo::Streaming::MortonKeyCompare>& renderables;
        
        void AddSphere(const Eegeo::Streaming::MortonKey& key);
    public:
        EnvironmentNotifierExampleTerrainStreamObserver(Eegeo::Rendering::RenderContext& renderContext,
                                                        std::map<Eegeo::Streaming::MortonKey, Eegeo::DebugRendering::SphereMesh*, Eegeo::Streaming::MortonKeyCompare>& renderables)
        :renderables(renderables)
        ,renderContext(renderContext)
        {
            
        }
        
        void AddedStreamingResourceToSceneGraph(const Eegeo::Streaming::MortonKey& key);
        void RemovedStreamingResourceFromSceneGraph(const Eegeo::Streaming::MortonKey& key);
    };
    
    class EnvironmentNotifierExample : public IExample
    {
    private:
        Eegeo::Rendering::RenderContext& renderContext;
        Eegeo::Resources::Terrain::TerrainStreaming& terrainStreaming;
        EnvironmentNotifierExampleTerrainStreamObserver* observer;
        
        std::map<Eegeo::Streaming::MortonKey, Eegeo::DebugRendering::SphereMesh*, Eegeo::Streaming::MortonKeyCompare> renderables;
        
        
    public:
        EnvironmentNotifierExample(Eegeo::Rendering::RenderContext& renderContext,
                                   Eegeo::Resources::Terrain::TerrainStreaming& terrainStreaming);
        
        void Start();
        void Update(float dt);
        void Draw();
        void Suspend();
    };
}


#endif /* defined(__ExampleApp__EnvironmentNotifierExample__) */
