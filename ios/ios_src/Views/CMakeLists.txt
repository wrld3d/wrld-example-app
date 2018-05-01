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
  ios_src/Views/CustomSwitch.h
  ios_src/Views/CustomSwitch.m
  ios_src/Views/HeaderView.h
  ios_src/Views/HeaderView.mm
  ios_src/Views/MessageView.h
  ios_src/Views/MessageView.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Views FILES ${currsources})
endif(${IOS})
