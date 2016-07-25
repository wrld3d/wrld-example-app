set(headers ${headers} ../src/RenderingTransformMesh/SdkModel
)
set(currsources
  ../src/RenderingTransformMesh/SdkModel/GeometryHelpers.cpp
  ../src/RenderingTransformMesh/SdkModel/GeometryHelpers.h
  ../src/RenderingTransformMesh/SdkModel/LocalTexture.cpp
  ../src/RenderingTransformMesh/SdkModel/LocalTexture.h
  ../src/RenderingTransformMesh/SdkModel/LocalTextureFactory.cpp
  ../src/RenderingTransformMesh/SdkModel/LocalTextureFactory.h
  ../src/RenderingTransformMesh/SdkModel/RenderingTransformMeshModule.cpp
  ../src/RenderingTransformMesh/SdkModel/RenderingTransformMeshModule.h
  ../src/RenderingTransformMesh/SdkModel/TexturedVertexMeshFactory.cpp
  ../src/RenderingTransformMesh/SdkModel/TexturedVertexMeshFactory.h
  ../src/RenderingTransformMesh/SdkModel/TransformMeshRenderable.cpp
  ../src/RenderingTransformMesh/SdkModel/TransformMeshRenderable.h
  ../src/RenderingTransformMesh/SdkModel/TransformMeshRenderableFactory.cpp
  ../src/RenderingTransformMesh/SdkModel/TransformMeshRenderableFactory.h
  ../src/RenderingTransformMesh/SdkModel/TransformMeshRenderableFilter.cpp
  ../src/RenderingTransformMesh/SdkModel/TransformMeshRenderableFilter.h
  ../src/RenderingTransformMesh/SdkModel/UnlitTexturedMaterial.cpp
  ../src/RenderingTransformMesh/SdkModel/UnlitTexturedMaterial.h
  ../src/RenderingTransformMesh/SdkModel/UnlitTexturedMaterialFactory.cpp
  ../src/RenderingTransformMesh/SdkModel/UnlitTexturedMaterialFactory.h
  ../src/RenderingTransformMesh/SdkModel/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\RenderingTransformMesh\\SdkModel FILES ${currsources})
