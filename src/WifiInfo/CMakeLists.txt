if(${IOS})
set(headers ${headers} ../src/WifiInfo
)
set(currsources
  ../src/WifiInfo/CMakeLists.txt
  ../src/WifiInfo/IRestrictedBuildingService.h
  ../src/WifiInfo/RestrictedBuildingService.cpp
  ../src/WifiInfo/RestrictedBuildingService.h

)
set(sources ${sources} ${currsources})
source_group(\\src\\WifiInfo FILES ${currsources})

endif(${IOS})
