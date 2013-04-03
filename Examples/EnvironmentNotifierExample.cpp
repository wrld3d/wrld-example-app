#include "EnvironmentNotifierExample.h"
#include "CubeMapCellInfo.h"

#define SPHERE_HEIGHT_ABOVE_SEA 10.0

namespace Examples
{
    //EnvironmentNotifierExample//
    EnvironmentNotifierExample::EnvironmentNotifierExample(Eegeo::Rendering::RenderContext& renderContext,
                                                           Eegeo::Camera::CameraModel& cameraModel,
                                                           Eegeo::RenderCamera& renderCamera,
                                                           Eegeo::Resources::Terrain::TerrainStreaming& terrainStreaming)
    :renderContext(renderContext)
    ,cameraModel(cameraModel)
    ,renderCamera(renderCamera)
    ,terrainStreaming(terrainStreaming)
    ,observer(NULL)
    {
    }
    
    void EnvironmentNotifierExample::Start()
    {
        observer = new EnvironmentNotifierExampleTerrainStreamObserver(renderContext, cameraModel, renderCamera, renderables);
        terrainStreaming.AddStreamingObserver(observer);
    }
    
    void EnvironmentNotifierExample::Suspend()
    {
        terrainStreaming.RemoveStreamingObserver(observer);
        delete observer;
        observer = NULL;
    }
    
    void EnvironmentNotifierExample::Update()
    {
    }
    
    
    void EnvironmentNotifierExample::Draw()
    {
        //draw all the spheres
        for(std::map<Eegeo::Streaming::MortonKeyLong, Eegeo::DebugRendering::SphereMesh*>::iterator
            it = renderables.begin(); it != renderables.end(); ++ it)
        {
            Eegeo::DebugRendering::SphereMesh& mesh = *(*it).second;
            mesh.Draw(renderCamera);
        }
    }
    
    
    //EnvironmentNotifierExampleTerrainStreamObserver///
    void EnvironmentNotifierExampleTerrainStreamObserver::AddSphere(const Eegeo::Streaming::MortonKeyLong& key)
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
                                                                                          renderContext,
                                                                                          &cameraModel,
                                                                                          20.0f,
                                                                                          16, 16,
                                                                                          spherePosition,
                                                                                          NULL,
                                                                                          color
                                                                                          );
        sphere->Tesselate();
        
        renderables.insert(std::make_pair(key,sphere));
    }
    
    void EnvironmentNotifierExampleTerrainStreamObserver::AddedStreamingResourceToSceneGraph(const Eegeo::Streaming::MortonKeyLong& key)
    {
        Eegeo_TTY("Adding Terrain Resource :: %s\n", key.ToString().c_str());
        AddSphere(key);
    }
    
    void EnvironmentNotifierExampleTerrainStreamObserver::RemovedStreamingResourceFromSceneGraph(const Eegeo::Streaming::MortonKeyLong& key)
    {
        Eegeo_TTY("Removing Terrain Resource :: %s\n", key.ToString().c_str());
        renderables.erase(key);
    }
}
