if(${IOS})
set(headers ${headers} ios_src/SenionLab
)
set(currsources
  ios_src/SenionLab/CMakeLists.txt
  ios_src/SenionLab/SenionLabLocationManagerInterop.h
  ios_src/SenionLab/SenionLabLocationManagerInterop.mm
  ios_src/SenionLab/SenionLabLocationManager.h
  ios_src/SenionLab/SenionLabLocationManager.mm
  ios_src/SenionLab/SenionLabLocationModule.h
  ios_src/SenionLab/SenionLabLocationModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SenionLab FILES ${currsources})
endif(${IOS})
