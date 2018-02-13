set(headers ${headers} ../src/DeepLink/SdkModel
)
set(currsources
../src/DeepLink/SdkModel/DeepLinkController.cpp
../src/DeepLink/SdkModel/DeepLinkController.h
../src/DeepLink/SdkModel/DeepLinkModel.cpp
../src/DeepLink/SdkModel/DeepLinkModel.h
../src/DeepLink/SdkModel/DeepLinkModule.cpp
../src/DeepLink/SdkModel/DeepLinkModule.h
../src/DeepLink/SdkModel/DeepLinkLocationHandler.h
../src/DeepLink/SdkModel/DeepLinkLocationHandler.cpp
../src/DeepLink/SdkModel/DeepLinkQueryStringParser.h
../src/DeepLink/SdkModel/DeepLinkQueryStringParser.cpp
../src/DeepLink/SdkModel/DeepLinkSearchHandler.h
../src/DeepLink/SdkModel/DeepLinkSearchHandler.cpp
../src/DeepLink/SdkModel/DeepLinkConfigHandler.cpp
../src/DeepLink/SdkModel/DeepLinkConfigHandler.h
../src/DeepLink/SdkModel/IDeepLinkHandler.h
../src/DeepLink/SdkModel/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\DeepLink\\SdkModel FILES ${currsources})
