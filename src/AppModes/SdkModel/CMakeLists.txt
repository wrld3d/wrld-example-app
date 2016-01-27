set(headers ${headers} src/AppModes/SdkModel
)
set(currsources
  src/AppModes/SdkModel/AppModeModel.cpp
  src/AppModes/SdkModel/AppModeModel.h
  src/AppModes/SdkModel/IAppModeModel.h
  src/AppModes/SdkModel/IAppModeStatesFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\AppModes\\SdkModel FILES ${currsources})
