set(headers ${headers} src/CategorySearch/SdkModel
)
set(currsources
  src/CategorySearch/SdkModel/CategorySearchModule.cpp
  src/CategorySearch/SdkModel/CategorySearchModule.h
  src/CategorySearch/SdkModel/CategorySearchSelectedMessageHandler.cpp
  src/CategorySearch/SdkModel/CategorySearchSelectedMessageHandler.h
  src/CategorySearch/SdkModel/ICategorySearchModule.h
)
set(sources ${sources} ${currsources})
source_group(\\CategorySearch\\SdkModel FILES ${currsources})
