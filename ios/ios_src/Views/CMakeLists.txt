if(${IOS})
set(headers ${headers} ios_src/Views
)
set(currsources
  ios_src/Views/CMakeLists.txt
  ios_src/Views/UIButton+DefaultStates.h
  ios_src/Views/UIButton+DefaultStates.mm
  ios_src/Views/UILabelledCheckboxView.h
  ios_src/Views/UILabelledCheckboxView.mm
  ios_src/Views/UIView+TouchExclusivity.h
  ios_src/Views/UIView+TouchExclusivity.m
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Views FILES ${currsources})
endif(${IOS})
