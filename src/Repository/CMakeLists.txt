set(headers ${headers} src/Repository
)
set(currsources
  src/Repository/IRepositoryModel.h
  src/Repository/RepositoryModel.h
)
set(sources ${sources} ${currsources})
source_group(\\Repository FILES ${currsources})
