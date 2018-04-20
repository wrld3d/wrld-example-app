set(headers ${headers} Include/WrldSearchWidget
)
set(currsources
Include/WrldSearchWidget/CMakeLists.txt
Include/WrldSearchWidget/WrldSearchWidget.framework
)
set(sources ${sources} ${currsources})
source_group(\\WrldSearchWidget FILES ${currsources})
