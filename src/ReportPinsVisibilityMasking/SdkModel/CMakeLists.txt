set(headers ${headers} ../src/ReportPinsVisibilityMasking/SdkModel
)
set(currsources
  ../src/ReportPinsVisibilityMasking/SdkModel/MenuSectionExpandedChangedObserver.cpp
  ../src/ReportPinsVisibilityMasking/SdkModel/MenuSectionExpandedChangedObserver.h
  ../src/ReportPinsVisibilityMasking/SdkModel/ReportPinsVisibilityMaskingController.cpp
  ../src/ReportPinsVisibilityMasking/SdkModel/ReportPinsVisibilityMaskingController.h
  ../src/ReportPinsVisibilityMasking/SdkModel/ReportPinsVisibilityMaskingModule.cpp
  ../src/ReportPinsVisibilityMasking/SdkModel/ReportPinsVisibilityMaskingModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\ReportPinsVisibilityMasking\\SdkModel FILES ${currsources})
