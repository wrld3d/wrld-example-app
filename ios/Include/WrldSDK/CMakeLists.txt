set(headers ${headers} Include/WrldSDK
)
set(currsources
Include/WrldSDK/CMakeLists.txt
Include/WrldSDK/iphoneos11.3/WrldNav.framework
Include/WrldSDK/iphoneos11.3/WrldNavWidget.framework
Include/WrldSDK/iphoneos11.3/WrldUtils.framework
Include/WrldSDK/iphoneos12.0/WrldNav.framework
Include/WrldSDK/iphoneos12.0/WrldNavWidget.framework
Include/WrldSDK/iphoneos12.0/WrldUtils.framework
)
set(sources ${sources} ${currsources})
source_group(\\WrldSDK FILES ${currsources})
