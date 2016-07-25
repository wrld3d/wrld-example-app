if(${IOS})
set(headers ${headers} ios_src/SenionLab
)
set(currsources
  ios_src/SenionLab/CMakeLists.txt
  ios_src/SenionLab/ISenionLabModule.h
  ios_src/SenionLab/SenionLabLocationManager.h
  ios_src/SenionLab/SenionLabLocationManager.mm
  ios_src/SenionLab/SenionLabModule.h
  ios_src/SenionLab/SenionLabModule.mm



)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SenionLab FILES ${currsources})
include(ios_src/SenionLab/FrameWork/CMakeLists.txt)
endif(${IOS})
