set(headers ${headers} ../src/InteriorsExplorer/SdkModel/Highlights
)
set(currsources
  ../src/InteriorsExplorer/SdkModel/Highlights/InteriorsHighlightPickingController.cpp
  ../src/InteriorsExplorer/SdkModel/Highlights/InteriorsHighlightPickingController.h
  ../src/InteriorsExplorer/SdkModel/Highlights/InteriorsHighlightVisibilityController.cpp
  ../src/InteriorsExplorer/SdkModel/Highlights/InteriorsHighlightVisibilityController.h
  ../src/InteriorsExplorer/SdkModel/Highlights/InteriorsEntityIdHighlightVisibilityController.cpp
  ../src/InteriorsExplorer/SdkModel/Highlights/InteriorsEntityIdHighlightVisibilityController.h
  ../src/InteriorsExplorer/SdkModel/Highlights/IHighlightColorMapper.h
  ../src/InteriorsExplorer/SdkModel/Highlights/HighlightColorMapper.cpp
  ../src/InteriorsExplorer/SdkModel/Highlights/HighlightColorMapper.h
  ../src/InteriorsExplorer/SdkModel/Highlights/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\InteriorsExplorer\\SdkModel\\Highlights FILES ${currsources})
