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
    class BoundsVisualiser
    {
        struct Shader {
            int m_positionSlot;
            int m_mvpUniform;
            u32 m_programHandle;
        };
        
        struct Vertex {
            float x, y, z;
        };
        
        const size_t NumVerts = 8;
        const size_t NumIndices = 36;
        Shader* m_pShader;
        u32 m_glVertexBuffer;
        u32 m_glIndexBuffer;
        Eegeo::Rendering::RenderContext& renderContext;
        
        std::string VertexShader();
        std::string FragmentShader();
        void CompileShaders();
        void InitMeshGLBuffers(Vertex* verts, u16* indices);
        void Build(const Eegeo::v3& minExtents, const Eegeo::v3& maxExtents);
        void DestroyGeometry();
        
    public:
        BoundsVisualiser(Eegeo::Rendering::RenderContext& renderContext);
        ~BoundsVisualiser();
        
        void Draw(const Eegeo::v3& minExtents, const Eegeo::v3& maxExtents);
    };

    
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
        Eegeo::Lighting::GlobalFogging& globalFogging;
   
        Eegeo::Model* pModel;
        BoundsVisualiser boundsVisualiser;
        MeshInstance mesh;
        
    public:
        LoadModelExample(Eegeo::Rendering::RenderContext& renderContext,
                         Eegeo::Space::LatLongAltitude interestLocation,
                         Eegeo::Camera::CameraModel& cameraModel,
                         Eegeo::RenderCamera& renderCamera,
                         Eegeo::Helpers::IFileIO& fileIO,
                         Eegeo::Helpers::ITextureFileLoader& textureLoader,
                         Eegeo::Lighting::GlobalFogging& fogging);
        
        void Start();
        void Update();
        void Draw();
        void Suspend();
    };
}


#endif /* defined(__ExampleApp__LoadModelExample__) */
