#include "DebugSphereExample.h"

namespace Examples
{
    DebugSphereExample::DebugSphereExample(Eegeo::Rendering::RenderContext& renderContext,
                       Eegeo::Space::LatLongAltitude interestLocation,
                       Eegeo::Camera::CameraModel& cameraModel,
                       Eegeo::RenderCamera& renderCamera)
    :renderContext(renderContext)
    ,interestLocation(interestLocation)
    ,cameraModel(cameraModel)
    ,renderCamera(renderCamera)
    {
        
    }
    
    void DebugSphereExample::Start()
    {
        //add a set of spheres to the world with different heights and colors
        Eegeo::Space::LatLongAltitude sphereLocation = interestLocation;
        
        sphereLocation.SetAltitude(100.0f);
        AddSphere(sphereLocation, Eegeo::v3(1.0f, 0.0f, 0.0f));
        
        sphereLocation.SetAltitude(150.0f);
        AddSphere(sphereLocation, Eegeo::v3(0.0f, 1.0f, 1.0f));
        
        sphereLocation.SetAltitude(200.0f);
        AddSphere(sphereLocation, Eegeo::v3(0.0f, 1.0f, 0.0f));
        
        sphereLocation.SetAltitude(250.0f);
        AddSphere(sphereLocation, Eegeo::v3(0.0f, 0.0f, 1.0f));
        
        sphereLocation.SetAltitude(300.0f);
        AddSphere(sphereLocation, Eegeo::v3(1.0f, 1.0f, 0.0f));
    }
    
    void DebugSphereExample::Suspend()
    {
        //destroy all the spheres
        for(std::vector<Eegeo::DebugRendering::SphereMesh*>::iterator
            it = renderables.begin(); it != renderables.end(); ++ it)
        {
            delete *it;
        }
        
        renderables.clear();
    }
    
    void DebugSphereExample::Update()
    {
        //no work to do in update
    }
    
    void DebugSphereExample::Draw()
    {
        //draw all the spheres
        for(std::vector<Eegeo::DebugRendering::SphereMesh*>::iterator
            it = renderables.begin(); it != renderables.end(); ++ it)
        {
            (*it)->Draw(renderCamera);
        }
    }
    
    void DebugSphereExample::AddSphere(Eegeo::Space::LatLongAltitude sphereLocation,
                                       Eegeo::v3 color)
    {
        //add a sphere of radius 20 meters at sphereLocation 
        Eegeo::DebugRendering::SphereMesh* sphere = new Eegeo::DebugRendering::SphereMesh(
                                                                                       renderContext,
                                                                                       &cameraModel,
                                                                                       20.0f,
                                                                                       16, 16, //tessellation parameters
                                                                                       sphereLocation.ToECEF(),
                                                                                       NULL, //no texture, just colored spheres
                                                                                       color
                                                                                       );
        sphere->Tesselate(); //tessellate the sphere
        
        renderables.push_back(sphere);
    }
}
