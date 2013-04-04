#include "LoadModelExample.h"
#include <sys/time.h>

namespace Examples
{
    LoadModelExample::LoadModelExample(Eegeo::Rendering::RenderContext& renderContext,
                                       Eegeo::Space::LatLongAltitude interestLocation,
                                       Eegeo::Camera::CameraModel& cameraModel,
                                       Eegeo::RenderCamera& renderCamera,
                                       Eegeo::Helpers::IFileIO& fileIO,
                                       Eegeo::Helpers::ITextureFileLoader& textureLoader)
    :renderContext(renderContext)
    ,interestLocation(interestLocation)
    ,cameraModel(cameraModel)
    ,renderCamera(renderCamera)
    ,fileIO(fileIO)
    ,textureLoader(textureLoader)
    ,pModel(NULL)
    {
        
    }
    
    void LoadModelExample::Start()
    {
        pModel = new Eegeo::Model(renderContext.GetGLState(), textureLoader, fileIO);
        
        //this is a .pod resource file included in the build
        pModel->Load("SanFrancisco_Vehicles.pod");
        
        //the layout of this resource is assumed - a "Vehicles" node should exist
        Eegeo::Node* parentNode = pModel->FindNode("Vehicles");
        Eegeo_ASSERT(parentNode);
        
        //it should have some children, which are the vehicle meshes...
        Eegeo_ASSERT(parentNode->GetNumChildNodes() > 0);

        //select a random vehicle
        srand(time(NULL));
        mesh.node = parentNode->GetChildNode(rand() % parentNode->GetNumChildNodes());
    }
    
    void LoadModelExample::Suspend()
    {
        //destroy the example...
        mesh.node = NULL;
        delete pModel;
        pModel = NULL;
    }
    
    void LoadModelExample::Update()
    {
        //let's put the vehicle in the air
        interestLocation.SetAltitude(150.0f);
        
        //put the vehicle at interest point
        mesh.positionEcef = interestLocation.ToECEF();
        
        //up is relative to earth location, normal to tangent plane formed at surface below model
        mesh.up = mesh.positionEcef.Norm().ToSingle();
        
        //cross with north pole (0,1,0) for a forward vector
        mesh.forward = Eegeo::v3::Cross(mesh.up, Eegeo::v3(0.0f, 1.0f, 0.0f));
        
        //set some big scale value so we can see the vehicle - vary between x20 and x70
        struct timeval time;
        gettimeofday(&time, NULL);
        mesh.scale = 20.0f + ((sin(time.tv_sec)/ 2.0f + 0.5) * 50.0f);
    }
    
    void LoadModelExample::Draw()
    {
        //form basis
        Eegeo::v3 up(mesh.up);
        Eegeo::v3 forward = -mesh.forward; //model is facing reverse (-ve z)
        Eegeo::v3 right(Eegeo::v3::Cross(up, forward).Norm());
        up = Eegeo::v3::Cross(forward, right);
        
        //compute a camera local position
        Eegeo::v3 cameraRelativePos = (mesh.positionEcef - cameraModel.GetWorldPosition()).ToSingle();
        
        //generate a transform from this basis and position...
        Eegeo::m44 cameraRelativeTransform;
        cameraRelativeTransform.SetFromBasis(right, up, forward, cameraRelativePos);
        
        Eegeo::m44 scaleMatrix;
        scaleMatrix.Scale(mesh.scale);
        
        //...and scale
        Eegeo::m44 transform;
        Eegeo::m44::Mul(transform, cameraRelativeTransform, scaleMatrix);
        transform.SetRow(3, Eegeo::v4(cameraRelativePos, 1.0f));
        
        //update the mesh instance with the transform
        mesh.node->SetLocalMatrix(transform);
        mesh.node->UpdateRecursive();
        mesh.node->UpdateSphereRecursive();
        
        //draw the mesh
        mesh.node->Draw(renderContext);

    }
}
