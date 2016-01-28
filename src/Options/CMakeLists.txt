set(headers ${headers} ../src/Options
)
set(currsources
  ../src/Options/CacheEnabledChangedMessage.cpp
  ../src/Options/CacheEnabledChangedMessage.h
  ../src/Options/ClearCacheMessage.cpp
  ../src/Options/ClearCacheMessage.h
  ../src/Options/CMakeLists.txt
  ../src/Options/CompletedCacheClearMessage.cpp
  ../src/Options/CompletedCacheClearMessage.h
  ../src/Options/IOptionsModule.h
  ../src/Options/OptionsModule.cpp
  ../src/Options/OptionsModule.h
  ../src/Options/StreamOverWifiOnlyChangedMessage.cpp
  ../src/Options/StreamOverWifiOnlyChangedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Options FILES ${currsources})
include(../src/Options/SdkModel/CMakeLists.txt)
include(../src/Options/View/CMakeLists.txt)
