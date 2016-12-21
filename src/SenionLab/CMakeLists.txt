if(${IOS})
set(headers ${headers} ../src/SenionLab
)
set(currsources
  ../src/SenionLab/CMakeLists.txt
  ../src/SenionLab/SenionLabLocationController.h
  ../src/SenionLab/SenionLabLocationController.cpp
  ../src/SenionLab/SenionLabLocationService.h
  ../src/SenionLab/SenionLabLocationService.cpp
  ../src/SenionLab/SenionLabLocationChangedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SenionLab FILES ${currsources})
include(../src/SenionLab/View/CMakeLists.txt)
endif(${IOS})
