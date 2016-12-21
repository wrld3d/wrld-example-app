if(${IOS})
set(headers ${headers} ios_src/SenionLab/View
)
set(currsources
  ios_src/SenionLab/View/CMakeLists.txt
  ios_src/SenionLab/View/SenionLabLocationManager.h
  ios_src/SenionLab/View/SenionLabLocationManager.mm
  ios_src/SenionLab/View/SenionLabLocationIncludes.h  ios_src/SenionLab/View/SenionLabLocationManagerInterop.h  ios_src/SenionLab/View/SenionLabLocationManagerInterop.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SenionLab\\View FILES ${currsources})
endif(${IOS})
