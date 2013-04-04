#ifndef __ExampleApp__LoadModelExample__
#define __ExampleApp__LoadModelExample__

#include "IExample.h"
#include "RenderContext.h"
#include "NewGlobeCamera.h"
#include "LatLongAltitude.h"
#include "CameraModel.h"
#include "Model.h"

namespace Examples
{
    class LoadModelExample : public IExample
    {
    private:
        struct MeshInstance
        {
            float scale;
            Eegeo::dv3 positionEcef;
            Eegeo::v3 forward;
            Eegeo::v3 up;
            Eegeo::Node* node;
        };
        
        Eegeo::Rendering::RenderContext& renderContext;
        Eegeo::Camera::CameraModel& cameraModel;
        Eegeo::RenderCamera& renderCamera;
        Eegeo::Helpers::IFileIO& fileIO;
        Eegeo::Helpers::ITextureFileLoader& textureLoader;
        Eegeo::Space::LatLongAltitude interestLocation;
   
        Eegeo::Model* pModel;
        MeshInstance mesh;
        
    public:
        LoadModelExample(Eegeo::Rendering::RenderContext& renderContext,
                         Eegeo::Space::LatLongAltitude interestLocation,
                         Eegeo::Camera::CameraModel& cameraModel,
                         Eegeo::RenderCamera& renderCamera,
                         Eegeo::Helpers::IFileIO& fileIO,
                         Eegeo::Helpers::ITextureFileLoader& textureLoader);
        
        void Start();
        void Update();
        void Draw();
        void Suspend();
    };
}


#endif /* defined(__ExampleApp__LoadModelExample__) */
