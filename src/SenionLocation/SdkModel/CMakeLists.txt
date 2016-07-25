set(headers ${headers} ../src/SenionLocation/SdkModel
)
set(currsources
  ../src/SenionLocation/SdkModel/ISenionLocationService.h
  ../src/SenionLocation/SdkModel/LocationServiceFacade.cpp
  ../src/SenionLocation/SdkModel/LocationServiceFacade.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SenionLocation\\SdkModel FILES ${currsources})
