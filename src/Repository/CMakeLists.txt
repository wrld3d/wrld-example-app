set(headers ${headers} ../src/Repository
)
set(currsources
  ../src/Repository/CMakeLists.txt
  ../src/Repository/IRepositoryModel.h
  ../src/Repository/RepositoryModel.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Repository FILES ${currsources})
