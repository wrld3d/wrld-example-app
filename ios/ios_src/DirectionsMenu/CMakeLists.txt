set(headers ${headers} ios_src/DirectionsMenu
)
set(currsources
  ios_src/DirectionsMenu/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\DirectionsMenu FILES ${currsources})
include(ios_src/DirectionsMenu/View/CMakeLists.txt)
include(ios_src/DirectionsMenu/SdkModel/CMakeLists.txt)