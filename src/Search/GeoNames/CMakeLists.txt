set(headers ${headers} ../src/Search/GeoNames
)
set(currsources
  ../src/Search/GeoNames/CMakeLists.txt
  ../src/Search/GeoNames/GeoNames.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\GeoNames FILES ${currsources})
include(../src/Search/GeoNames/SdkModel/CMakeLists.txt)
