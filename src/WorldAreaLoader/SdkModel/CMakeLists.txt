set(headers ${headers} ../src/WorldAreaLoader/SdkModel
)
set(currsources
  ../src/WorldAreaLoader/SdkModel/CMakeLists.txt
  ../src/WorldAreaLoader/SdkModel/IWorldAreaLoaderModel.h
  ../src/WorldAreaLoader/SdkModel/IWorldAreaLoaderModule.h
  ../src/WorldAreaLoader/SdkModel/WorldAreaLoader.h
  ../src/WorldAreaLoader/SdkModel/WorldAreaLoaderModel.cpp
  ../src/WorldAreaLoader/SdkModel/WorldAreaLoaderModel.h
  ../src/WorldAreaLoader/SdkModel/WorldAreaLoaderModule.cpp
  ../src/WorldAreaLoader/SdkModel/WorldAreaLoaderModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\WorldAreaLoader\\SdkModel FILES ${currsources})
