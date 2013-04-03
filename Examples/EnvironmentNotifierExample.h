#ifndef __ExampleApp__EnvironmentNotifierExample__
#define __ExampleApp__EnvironmentNotifierExample__

#include <map>

#include "IExample.h"
#include "RenderContext.h"
#include "NewGlobeCamera.h"
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
        Eegeo::Camera::CameraModel& cameraModel;
        Eegeo::RenderCamera& renderCamera;
        std::map<Eegeo::Streaming::MortonKeyLong, Eegeo::DebugRendering::SphereMesh*, Eegeo::Streaming::MortonKeyLongCompare>& renderables;
        
        void AddSphere(const Eegeo::Streaming::MortonKeyLong& key);
    public:
        EnvironmentNotifierExampleTerrainStreamObserver(Eegeo::Rendering::RenderContext& renderContext,
                                                        Eegeo::Camera::CameraModel& cameraModel,
                                                        Eegeo::RenderCamera& renderCamera,
                                                        std::map<Eegeo::Streaming::MortonKeyLong, Eegeo::DebugRendering::SphereMesh*, Eegeo::Streaming::MortonKeyLongCompare>& renderables)
        :renderables(renderables)
        ,cameraModel(cameraModel)
        ,renderContext(renderContext)
        ,renderCamera(renderCamera)
        {
            
        }
        
        void AddedStreamingResourceToSceneGraph(const Eegeo::Streaming::MortonKeyLong& key);
        void RemovedStreamingResourceFromSceneGraph(const Eegeo::Streaming::MortonKeyLong& key);
    };
    
    class EnvironmentNotifierExample : public IExample
    {
    private:
        Eegeo::Rendering::RenderContext& renderContext;
        Eegeo::Camera::CameraModel& cameraModel;
        Eegeo::RenderCamera& renderCamera;
        Eegeo::Resources::Terrain::TerrainStreaming& terrainStreaming;
        EnvironmentNotifierExampleTerrainStreamObserver* observer;
        
        std::map<Eegeo::Streaming::MortonKeyLong, Eegeo::DebugRendering::SphereMesh*, Eegeo::Streaming::MortonKeyLongCompare> renderables;
        
        
    public:
        EnvironmentNotifierExample(Eegeo::Rendering::RenderContext& renderContext,
                                   Eegeo::Camera::CameraModel& cameraModel,
                                   Eegeo::RenderCamera& renderCamera,
                                   Eegeo::Resources::Terrain::TerrainStreaming& terrainStreaming);
        
        void Start();
        void Update();
        void Draw();
        void Suspend();
    };
}


#endif /* defined(__ExampleApp__EnvironmentNotifierExample__) */
