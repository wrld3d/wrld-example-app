set(headers ${headers} ../src/DeepLink
)
set(currsources
../src/DeepLink/CMakeLists.txt
../src/DeepLink/DeepLink.h
../src/DeepLink/DeepLinkOpenedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\DeepLink FILES ${currsources})
include(../src/DeepLink/SdkModel/CMakeLists.txt)
