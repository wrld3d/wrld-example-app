set(headers ${headers} ../src/Net/SdkModel
)
set(currsources
  ../src/Net/SdkModel/CMakeLists.txt
  ../src/Net/SdkModel/ConnectivityChangedObserver.cpp
  ../src/Net/SdkModel/ConnectivityChangedObserver.h
  ../src/Net/SdkModel/ExampleAppCustomWebLoadRequestFactory.cpp
  ../src/Net/SdkModel/ExampleAppCustomWebLoadRequestFactory.h
  ../src/Net/SdkModel/INetworkCapabilities.h
  ../src/Net/SdkModel/NetIncludes.h
  ../src/Net/SdkModel/NetworkCapabilities.cpp
  ../src/Net/SdkModel/NetworkCapabilities.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Net\\SdkModel FILES ${currsources})
