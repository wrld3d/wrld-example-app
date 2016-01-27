if(${IOS})
set(headers ${headers} ios/ios_src/Views
)
set(currsources
  ios/ios_src/Views/UILabelledCheckboxView.h
  ios/ios_src/Views/UILabelledCheckboxView.mm
  ios/ios_src/Views/UIView+TouchExclusivity.h
  ios/ios_src/Views/UIView+TouchExclusivity.m
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Views FILES ${currsources})
endif(${IOS})
