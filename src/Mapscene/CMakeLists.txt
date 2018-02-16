set(headers ${headers} ../src/Mapscene
)
set(currsources
../src/Mapscene/CMakeLists.txt
../src/Mapscene/Mapscene.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Mapscene FILES ${currsources})
include(../src/Mapscene/SdkModel/CMakeLists.txt)

