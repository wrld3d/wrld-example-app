set(headers ${headers} ../src/SwallowPoiDb
)
set(currsources
  ../src/SwallowPoiDb/ISwallowPoiDbModule.h
  ../src/SwallowPoiDb/SwallowPoiDb.h
  ../src/SwallowPoiDb/SwallowPoiDbCombinedService.cpp
  ../src/SwallowPoiDb/SwallowPoiDbCombinedService.h
  ../src/SwallowPoiDb/SwallowPoiDbModule.cpp
  ../src/SwallowPoiDb/SwallowPoiDbModule.h
  ../src/SwallowPoiDb/SwallowPoiDbService.cpp
  ../src/SwallowPoiDb/SwallowPoiDbService.h
  ../src/SwallowPoiDb/SwallowPoiDbServiceProvider.cpp
  ../src/SwallowPoiDb/SwallowPoiDbServiceProvider.h
  ../src/SwallowPoiDb/SwallowPoiDbWebLoader.cpp
  ../src/SwallowPoiDb/SwallowPoiDbWebLoader.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SwallowPoiDb FILES ${currsources})
include(../src/SwallowPoiDb/Constants/CMakeLists.txt)
include(../src/SwallowPoiDb/Parsers/CMakeLists.txt)
