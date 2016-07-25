set(headers ${headers} ../src/Avatar/AvatarModule
)
set(currsources
  ../src/Avatar/AvatarModule/CMakeLists.txt
  ../src/Avatar/AvatarModule/AvatarModule.cpp
  ../src/Avatar/AvatarModule/AvatarModule.h
  ../src/Avatar/AvatarModule/AvatarView.cpp
  ../src/Avatar/AvatarModule/AvatarView.h
  ../src/Avatar/AvatarModule/AvatarLocationChangedObserver.cpp
  ../src/Avatar/AvatarModule/AvatarLocationChangedObserver.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Avatar\\AvatarModule FILES ${currsources})
