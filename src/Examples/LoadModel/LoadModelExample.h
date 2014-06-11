#ifndef __ExampleApp__LoadModelExample__
#define __ExampleApp__LoadModelExample__

#include "IExample.h"
#include "RenderContext.h"
#include "LatLongAltitude.h"
#include "IAsyncTextureRequestor.h"
#include "Model.h"

namespace Examples
{
class BoundsVisualiser
{
	struct Shader
	{
		int m_positionSlot;
		int m_mvpUniform;
		u32 m_programHandle;
	};

	struct Vertex
	{
		float m_x, m_y, m_z;
	};

	static const size_t NumVerts;
	static const size_t NumIndices;
	Shader* m_pShader;
	u32 m_glVertexBuffer;
	u32 m_glIndexBuffer;
	Eegeo::Rendering::RenderContext& m_renderContext;

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
		float m_scale;
		Eegeo::dv3 m_positionEcef;
		Eegeo::v3 m_forward;
		Eegeo::v3 m_up;
		Eegeo::Node* m_pNode;
	};

	Eegeo::Rendering::RenderContext& m_renderContext;
	Eegeo::Helpers::IFileIO& m_fileIO;
	Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& m_textureRequestor;
	Eegeo::Space::LatLongAltitude m_interestLocation;
	Eegeo::Lighting::GlobalFogging& m_globalFogging;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

	Eegeo::Model* m_pModel;
	BoundsVisualiser m_boundsVisualiser;
	MeshInstance m_mesh;
	Eegeo::ModelMaterial* m_pDiscMaterial;
	float m_elapsedTime;

public:
	LoadModelExample(Eegeo::Rendering::RenderContext& renderContext,
	                 Eegeo::Space::LatLongAltitude interestLocation,
	                 Eegeo::Helpers::IFileIO& fileIO,
	                 Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor,
	                 Eegeo::Lighting::GlobalFogging& fogging,
	                 Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController);

	static std::string GetName()
	{
		return "LoadModelExample";
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


#endif /* defined(__ExampleApp__LoadModelExample__) */
