set(headers ${headers} ../src/InteriorsNavigation/SdkModel
)
set(currsources
  ../src/InteriorsNavigation/SdkModel/IInteriorsNavigationService.h
  ../src/InteriorsNavigation/SdkModel/InteriorsNavigationService.cpp
  ../src/InteriorsNavigation/SdkModel/InteriorsNavigationService.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\InteriorsNavigation\\SdkModel FILES ${currsources})
