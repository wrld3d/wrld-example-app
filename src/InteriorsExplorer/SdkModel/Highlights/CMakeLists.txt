set(headers ${headers} ../src/InteriorsExplorer/SdkModel/Highlights
)
set(currsources
  ../src/InteriorsExplorer/SdkModel/Highlights/InteriorsHighlightPickingController.cpp
  ../src/InteriorsExplorer/SdkModel/Highlights/InteriorsHighlightPickingController.h
  ../src/InteriorsExplorer/SdkModel/Highlights/InteriorsHighlightVisibilityController.cpp
  ../src/InteriorsExplorer/SdkModel/Highlights/InteriorsHighlightVisibilityController.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\InteriorsExplorer\\SdkModel\\Highlights FILES ${currsources})
