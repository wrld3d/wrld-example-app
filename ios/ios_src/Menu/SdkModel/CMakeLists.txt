if(${IOS})
set(headers ${headers} ios_src/Menu/SdkModel
)
set(currsources
  ios_src/Menu/SdkModel/IOSMenuReactionModel.h
  ios_src/Menu/SdkModel/IOSMenuReactionModel.cpp
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Menu\\SdkModel FILES ${currsources})
endif(${IOS})
