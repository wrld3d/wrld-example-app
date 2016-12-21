if(${IOS})
set(headers ${headers} ../src/SenionLab/View
)
set(currsources
  ../src/SenionLab/View/CMakeLists.txt
  ../src/SenionLab/View/ISenionLabLocationManager.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SenionLab\\View FILES ${currsources})
endif(${IOS})
