set(headers ${headers} ../src/Search/SelectFirstResult/SdkModel
)
set(currsources
  ../src/Search/SelectFirstResult/SdkModel/CMakeLists.txt
  ../src/Search/SelectFirstResult/SdkModel/SelectFirstResultSearchService.cpp
  ../src/Search/SelectFirstResult/SdkModel/SelectFirstResultSearchService.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\SelectFirstResult\\SdkModel FILES ${currsources})
