if(${IOS})
set(headers ${headers} ios_src/SenionLab
)
set(currsources
  ios_src/SenionLab/CMakeLists.txt
  ios_src/SenionLab/SenionLabLocationModule.h
  ios_src/SenionLab/SenionLabLocationModule.mm
  ios_src/SenionLab/SenionLabLocationServiceImpl.h
  ios_src/SenionLab/SenionLabLocationServiceImpl.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SenionLab FILES ${currsources})
endif(${IOS})
