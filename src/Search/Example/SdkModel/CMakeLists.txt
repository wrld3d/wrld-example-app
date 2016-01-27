set(headers ${headers} src/Search/Example/SdkModel
)
set(currsources
  src/Search/Example/SdkModel/ExampleSearchJsonParser.cpp
  src/Search/Example/SdkModel/ExampleSearchJsonParser.h
  src/Search/Example/SdkModel/ExampleSearchResultModel.cpp
  src/Search/Example/SdkModel/ExampleSearchResultModel.h
)
set(sources ${sources} ${currsources})
source_group(\\Search\\Example\\SdkModel FILES ${currsources})
