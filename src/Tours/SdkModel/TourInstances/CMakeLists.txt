set(headers ${headers} src/Tours/SdkModel/TourInstances
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\Tours\\SdkModel\\TourInstances FILES ${currsources})
include(src/Tours/SdkModel/TourInstances/Example/CMakeLists.txt)
include(src/Tours/SdkModel/TourInstances/TwitterFeed/CMakeLists.txt)
