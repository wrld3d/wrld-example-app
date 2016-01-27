set(headers ${headers} src/InteriorsCustomMaterials
)
set(currsources
  src/InteriorsCustomMaterials/InteriorsCustomMaterials.h
)
set(sources ${sources} ${currsources})
source_group(\\InteriorsCustomMaterials FILES ${currsources})
include(src/InteriorsCustomMaterials/SdkModel/CMakeLists.txt)
