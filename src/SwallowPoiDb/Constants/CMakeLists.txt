set(headers ${headers} ../src/SwallowPoiDb/Constants
)
set(currsources
  ../src/SwallowPoiDb/Constants/SwallowPoiDbConstants.cpp
  ../src/SwallowPoiDb/Constants/SwallowPoiDbConstants.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SwallowPoiDb\\Constants FILES ${currsources})
