set(headers ${headers} Include/IndoorAtlas
)
set(currsources
Include/IndoorAtlas/CMakeLists.txt
Include/IndoorAtlas/IndoorAtlas.framework
)
set(sources ${sources} ${currsources})
source_group(\\IndoorAtlas FILES ${currsources})
