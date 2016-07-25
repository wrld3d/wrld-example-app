set(headers ${headers} ../src/RenderingTransformMesh
)
set(currsources
  ../src/RenderingTransformMesh/RenderingTransformMesh.h
  ../src/RenderingTransformMesh/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\RenderingTransformMesh FILES ${currsources})
include(../src/RenderingTransformMesh/SdkModel/CMakeLists.txt)