if(${IOS})
set(headers ${headers} ../src/SenionLab
)
set(currsources
  ../src/SenionLab/CMakeLists.txt
  ../src/SenionLab/SenionLabLocationController.h
  ../src/SenionLab/SenionLabLocationController.cpp
  ../src/SenionLab/SenionLabLocationService.h
  ../src/SenionLab/SenionLabLocationService.cpp
)
set(sources ${sources} ${currsources})
source_group(\\src\\SenionLab FILES ${currsources})
endif(${IOS})
