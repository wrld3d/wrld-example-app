set(headers ${headers} ../src/Mapscene/SdkModel
)
set(currsources
../src/Mapscene/SdkModel/MapsceneLoader.cpp
../src/Mapscene/SdkModel/MapsceneLoader.h
../src/Mapscene/SdkModel/MapsceneModule.cpp
../src/Mapscene/SdkModel/MapsceneModule.h
../src/Mapscene/SdkModel/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\Mapscene\\SdkModel FILES ${currsources})

