set(headers ${headers} ../src/Avatar/SdkModel
)
set(currsources
  ../src/Avatar/SdkModel/AvatarController.cpp
  ../src/Avatar/SdkModel/AvatarController.h
  ../src/Avatar/SdkModel/CMakeLists.txt
  ../src/Avatar/SdkModel/AvatarModel.cpp
  ../src/Avatar/SdkModel/AvatarModel.h
  ../src/Avatar/SdkModel/AvatarSceneModelFactory.cpp
  ../src/Avatar/SdkModel/AvatarSceneModelFactory.h
  ../src/Avatar/SdkModel/IAnimatedSceneModel.h
  ../src/Avatar/SdkModel/IAvatarController.h
  ../src/Avatar/SdkModel/IAvatarModel.h
  ../src/Avatar/SdkModel/IAvatarModule.h
  ../src/Avatar/SdkModel/IAvatarSceneModelFactory.h
  ../src/Avatar/SdkModel/IAvatarView.h
  ../src/Avatar/SdkModel/XrayAnimatedSceneModel.cpp
  ../src/Avatar/SdkModel/XrayAnimatedSceneModel.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Avatar\\SdkModel FILES ${currsources})
