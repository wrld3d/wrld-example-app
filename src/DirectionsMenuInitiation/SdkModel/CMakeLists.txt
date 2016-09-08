set(headers ${headers} ../src/DirectionsMenuInitiation/SdkModel
)
set(currsources
  ../src/DirectionsMenuInitiation/SdkModel/CMakeLists.txt
  ../src/DirectionsMenuInitiation/SdkModel/IDirectionsMenuInitiationModule.h  ../src/DirectionsMenuInitiation/SdkModel/DirectionsMenuInitiationModule.cpp  ../src/DirectionsMenuInitiation/SdkModel/DirectionsMenuInitiationModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\DirectionsMenuInitiation\\SdkModel FILES ${currsources})
