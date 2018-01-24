set(headers ${headers} Include/WrldSDK
)
set(currsources
Include/WrldSDK/CMakeLists.txt
Include/WrldSDK/WrldNav.framework
Include/WrldSDK/WrldNavWidget.framework
Include/WrldSDK/WrldUtils.framework
)
set(sources ${sources} ${currsources})
source_group(\\WrldSDK FILES ${currsources})
