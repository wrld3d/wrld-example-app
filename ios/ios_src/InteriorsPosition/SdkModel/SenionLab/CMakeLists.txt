if(${IOS})
set(headers ${headers} ios_src/InteriorsPosition/SdkModel/SenionLab
)
set(currsources
  ios_src/InteriorsPosition/SdkModel/SenionLab/CMakeLists.txt
  ios_src/InteriorsPosition/SdkModel/SenionLab/SenionLabLocationModule.h
  ios_src/InteriorsPosition/SdkModel/SenionLab/SenionLabLocationModule.mm
  ios_src/InteriorsPosition/SdkModel/SenionLab/SenionLabLocationInterop.h
  ios_src/InteriorsPosition/SdkModel/SenionLab/SenionLabLocationInterop.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\InteriorsPosition\\SdkModel\\SenionLab FILES ${currsources})
endif(${IOS})
