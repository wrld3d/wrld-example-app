set(headers ${headers} ../src/Tours/SdkModel/TourInstances
)
set(currsources
  ../src/Tours/SdkModel/TourInstances/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\Tours\\SdkModel\\TourInstances FILES ${currsources})
include(../src/Tours/SdkModel/TourInstances/Example/CMakeLists.txt)
include(../src/Tours/SdkModel/TourInstances/TwitterFeed/CMakeLists.txt)
