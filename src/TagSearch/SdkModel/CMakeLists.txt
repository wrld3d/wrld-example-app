set(headers ${headers} ../src/TagSearch/SdkModel
)
set(currsources
  ../src/TagSearch/SdkModel/TagSearchModule.cpp
  ../src/TagSearch/SdkModel/TagSearchModule.h
  ../src/TagSearch/SdkModel/TagSearchRepositoryObserver.cpp
  ../src/TagSearch/SdkModel/TagSearchRepositoryObserver.h
  ../src/TagSearch/SdkModel/TagSearchSelectedMessageHandler.cpp
  ../src/TagSearch/SdkModel/TagSearchSelectedMessageHandler.h
  ../src/TagSearch/SdkModel/CMakeLists.txt
  ../src/TagSearch/SdkModel/ITagSearchModule.h
  ../src/TagSearch/SdkModel/EegeoTagIconMapper.h
  ../src/TagSearch/SdkModel/EegeoTagIconMapper.cpp
  ../src/TagSearch/SdkModel/EegeoTagIconMapperFactory.h
  ../src/TagSearch/SdkModel/EegeoTagIconMapperFactory.cpp
  ../src/TagSearch/SdkModel/ITagIconMapper.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\TagSearch\\SdkModel FILES ${currsources})
