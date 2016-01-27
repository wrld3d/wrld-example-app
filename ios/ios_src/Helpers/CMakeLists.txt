if(${IOS})
set(headers ${headers} ios/ios_src/Helpers
)
set(currsources
  ios/ios_src/Helpers/IconResources.h
  ios/ios_src/Helpers/IconResources.mm
  ios/ios_src/Helpers/ImageHelpers.h
  ios/ios_src/Helpers/ImageHelpers.mm
  ios/ios_src/Helpers/UIColors.h
  ios/ios_src/Helpers/UIColors.mm
  ios/ios_src/Helpers/UIHelpers.h
  ios/ios_src/Helpers/UIHelpers.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Helpers FILES ${currsources})
endif(${IOS})
