set(headers ${headers} src/SecondaryMenu/SdkModel
)
set(currsources
  src/SecondaryMenu/SdkModel/ISecondaryMenuModule.h
  src/SecondaryMenu/SdkModel/PerformedSearchMessageHandler.cpp
  src/SecondaryMenu/SdkModel/PerformedSearchMessageHandler.h
  src/SecondaryMenu/SdkModel/SecondaryMenuModule.cpp
  src/SecondaryMenu/SdkModel/SecondaryMenuModule.h
)
set(sources ${sources} ${currsources})
source_group(\\SecondaryMenu\\SdkModel FILES ${currsources})
