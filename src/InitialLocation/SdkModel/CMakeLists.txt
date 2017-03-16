set(headers ${headers} ../src/InitialLocation/SdkModel
)
set(currsources
../src/InitialLocation/SdkModel/CMakeLists.txt
../src/InitialLocation/SdkModel/IInitialLocationModel.h
../src/InitialLocation/SdkModel/InitialLocation.h
../src/InitialLocation/SdkModel/InitialLocationModel.cpp
../src/InitialLocation/SdkModel/InitialLocationModel.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\InitialLocation\\SdkModel FILES ${currsources})
