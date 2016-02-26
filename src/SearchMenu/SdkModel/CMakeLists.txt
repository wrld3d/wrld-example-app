set(headers ${headers} ../src/SearchMenu/SdkModel
)
set(currsources
  ../src/SearchMenu/SdkModel/CMakeLists.txt
  ../src/SearchMenu/SdkModel/ISearchMenuModule.h
  ../src/SearchMenu/SdkModel/SearchMenuModule.cpp
  ../src/SearchMenu/SdkModel/SearchMenuModule.h
  ../src/SearchMenu/SdkModel/SearchMenuPerformedSearchMessageHandler.cpp
  ../src/SearchMenu/SdkModel/SearchMenuPerformedSearchMessageHandler.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SearchMenu\\SdkModel FILES ${currsources})
