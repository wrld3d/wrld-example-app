#include "ScreenUnprojectExample.h"
#include "EarthConstants.h"

namespace
{
    //represents a ray originating from an ecef position
    struct Ray
    {
        Eegeo::dv3 origin;
        Eegeo::v3 dir;
    };
    
    bool TryGetRayIntersectionWithEarthSizedSphereCenteredAtOrigin(const Ray &ray, Eegeo::dv3 &intersectionPoint)
    {
        Eegeo::dv3 origin = ray.origin;
        Eegeo::v3 dirInv = -ray.dir;
        
        double a =
        dirInv.GetX() * dirInv.GetX()
        + dirInv.GetY() * dirInv.GetY()
        + dirInv.GetZ() * dirInv.GetZ();
        
        double b =
        dirInv.GetX() * (2.0 * origin.GetX())
        + dirInv.GetY() * (2.0 * origin.GetY())
        + dirInv.GetZ() * (2.0 * origin.GetZ());
        
        double c = 0.0;
        
        c += origin.GetX() * origin.GetX()
        + origin.GetY() * origin.GetY()
        + origin.GetZ() * origin.GetZ();
        
        c -= Eegeo::Space::EarthConstants::RadiusSquared;
        
        double d = b * b + (-4.0) * a * c;
        
        if (d < 0) return false;
        
        d = sqrt(d);
        
        double t = (-0.5) * (b - d) / a;
        
        if (t >= 0.0) return false;
        
        intersectionPoint.SetX(origin.GetX() + (dirInv.GetX() * t));
        intersectionPoint.SetY(origin.GetY() + (dirInv.GetY() * t));
        intersectionPoint.SetZ(origin.GetZ() + (dirInv.GetZ() * t));
        
        return true;
    }    
}

namespace Examples
{
    ScreenUnprojectExample::ScreenUnprojectExample(Eegeo::Rendering::RenderContext& renderContext,
                                                   Eegeo::Camera::CameraModel& cameraModel,
                                                   Eegeo::RenderCamera& renderCamera,
                                                   Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider)
    :renderContext(renderContext)
    ,cameraModel(cameraModel)
    ,renderCamera(renderCamera)
    ,terrainHeightProvider(terrainHeightProvider)
    {
        
    }
    
    void ScreenUnprojectExample::Start()
    {
        //create and tessellate a sphere mesh as in the DebugSphereExample program
        sphere = new Eegeo::DebugRendering::SphereMesh(
                                                       renderContext,
                                                       &cameraModel,
                                                       20.0f,
                                                       16, 16,
                                                       Eegeo::dv3(),
                                                       NULL,
                                                       Eegeo::v3(1.0f, 0.0f, 0.0f)
                                                       );
        sphere->Tesselate();
        
    }
    
    void ScreenUnprojectExample::Suspend()
    {
        //destroy the sphere
        delete sphere;
    }
    
    void ScreenUnprojectExample::Update()
    {
        //select the middle of the client screen as the position of the sphere
        double screenPointOfInterestX = (renderContext.GetScreenWidth()/2.0f);
        double screenPointOfInterestY = (renderContext.GetScreenHeight()/2.0f);
        
        //normalize this 
        double nx = 2.0 * screenPointOfInterestX / renderContext.GetScreenWidth() - 1;
        double ny = - 2.0 * screenPointOfInterestY / renderContext.GetScreenHeight() + 1;
        
        //prepare near and far points
        Eegeo::v4 near(nx, ny, 0.0f, 1.0);
        Eegeo::v4 far(nx, ny, 1.0f, 1.0);
        
        Eegeo::m44 invVP;
        Eegeo::m44::Inverse(invVP, renderContext.GetViewProjectionMatrix());
       
        //unproject the points
        Eegeo::v4 unprojectedNear = Eegeo::v4::Mul(near, invVP);
        Eegeo::v4 unprojectedFar = Eegeo::v4::Mul(far, invVP);
        
        //convert to 3d
        Eegeo::v3 unprojectedNearWorld = unprojectedNear / unprojectedNear.GetW();
        Eegeo::v3 unprojectedFarWorld = unprojectedFar / unprojectedFar.GetW();
        
        //check intersection with a world space ray from camera position
        Ray ray;
        ray.origin = cameraModel.GetWorldPosition();
        ray.dir = (unprojectedFarWorld - unprojectedNearWorld).Norm();
        
        Eegeo::dv3 intersectionPoint;
        if(TryGetRayIntersectionWithEarthSizedSphereCenteredAtOrigin(ray, intersectionPoint))
        {
            //we are intersecting the idealised sphere, so get height at the intersection location
            //and set sphere height to result
            float height = terrainHeightProvider.getHeight(intersectionPoint, 0);
            Eegeo::Space::LatLongAltitude intersectionLocation = Eegeo::Space::LatLongAltitude::FromECEF(intersectionPoint);
            intersectionLocation.SetAltitude(height);
            sphere->SetPositionECEF(intersectionLocation.ToECEF());
        }
    }
    
    void ScreenUnprojectExample::Draw()
    {
        //draw the sphere at the current location
        sphere->Draw(renderCamera);
    }
}
