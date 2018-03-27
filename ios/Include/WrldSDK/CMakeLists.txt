set(headers ${headers} Include/WrldSDK
)
set(currsources
Include/WrldSDK/CMakeLists.txt
Include/WrldSDK/WrldJourneys.frameworkInclude/WrldSDK/WrldJourneysSearch.frameworkInclude/WrldSDK/WrldJourneysWidget.frameworkInclude/WrldSDK/WrldUtils.framework
)
set(sources ${sources} ${currsources})
source_group(\\WrldSDK FILES ${currsources})
