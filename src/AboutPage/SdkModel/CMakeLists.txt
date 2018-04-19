set(headers ${headers} ../src/AboutPage/SdkModel
)
set(currsources
  ../src/AboutPage/SdkModel/AboutPageMenuModule.cpp
  ../src/AboutPage/SdkModel/AboutPageMenuModule.h
  ../src/AboutPage/SdkModel/IAboutPageMenuModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\AboutPage\\SdkModel FILES ${currsources})
