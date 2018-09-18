cmake_minimum_required(VERSION 3.1)

project(eegeo-mobile-example-app)
set(executable_name eegeo-mobile-example-app)

add_library(${executable_name} SHARED "")

# the following includes append to headers, sources, resources variables
include(../src/CMakeLists.txt)
include(jni/CMakeLists.txt)
include(libs/CMakeLists.txt)

target_include_directories(${executable_name} PRIVATE
    ${headers}
    )

target_sources(${executable_name} PRIVATE
    ${sources}
    ${resources}
    )

unset(headers)
unset(sources)
unset(resources)

target_link_libraries(${executable_name}
    eegeo-sdk
    android
    log
    breakpad_client
)


# import prebuilt libs

set (LIBS_PREBUILT_DIR ${CMAKE_CURRENT_LIST_DIR}/libs/eegeo/prebuilt/android-${ANDROID_NDK_ABI_NAME})

add_library(crypto STATIC IMPORTED GLOBAL)
set_target_properties(crypto PROPERTIES IMPORTED_LOCATION ${LIBS_PREBUILT_DIR}/libcrypto.a)

add_library(ssl STATIC IMPORTED GLOBAL)
set_target_properties(ssl PROPERTIES IMPORTED_LOCATION ${LIBS_PREBUILT_DIR}/libssl.a)

add_library(uv STATIC IMPORTED GLOBAL)
set_target_properties(uv PROPERTIES IMPORTED_LOCATION ${LIBS_PREBUILT_DIR}/libuv.a)

add_library(curl STATIC IMPORTED GLOBAL)
set_target_properties(curl PROPERTIES IMPORTED_LOCATION ${LIBS_PREBUILT_DIR}/libcurl.a)

add_library(http-parser STATIC IMPORTED GLOBAL)
set_target_properties(http-parser PROPERTIES IMPORTED_LOCATION ${LIBS_PREBUILT_DIR}/libhttp-parser.a)

add_library(jpeg STATIC IMPORTED GLOBAL)
set_target_properties(jpeg PROPERTIES IMPORTED_LOCATION ${LIBS_PREBUILT_DIR}/libjpeg.a)

add_library(turbojpeg STATIC IMPORTED GLOBAL)
set_target_properties(turbojpeg PROPERTIES IMPORTED_LOCATION ${LIBS_PREBUILT_DIR}/libturbojpeg.a)

add_library(png STATIC IMPORTED GLOBAL)
set_target_properties(png PROPERTIES IMPORTED_LOCATION ${LIBS_PREBUILT_DIR}/libpng.a)

add_library(breakpad_client STATIC IMPORTED GLOBAL)
set_target_properties(breakpad_client PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/prebuilt/android-${ANDROID_NDK_ABI_NAME}/libbreakpad_client.a
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/libs/breakpad
    )

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/eegeo/CMakeLists.txt")
  include("${CMAKE_CURRENT_SOURCE_DIR}/libs/eegeo/CMakeLists.txt")
else(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/eegeo/CMakeLists.txt")
  message(FATAL_ERROR "Couldn't detect platform headers. Have you run update.platform.sh?")
endif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/eegeo/CMakeLists.txt")

foreach(header ${headers})
    list(APPEND eegeo_sdk_includes ${CMAKE_CURRENT_LIST_DIR}/${header})
endforeach()




add_library(eegeo-sdk STATIC IMPORTED GLOBAL)
set_target_properties(eegeo-sdk PROPERTIES
    IMPORTED_LOCATION ${LIBS_PREBUILT_DIR}/libeegeo-sdk.a
    INTERFACE_INCLUDE_DIRECTORIES "${eegeo_sdk_includes}"
    )

set_property(TARGET eegeo-sdk
    PROPERTY INTERFACE_LINK_LIBRARIES
        png
        curl
        uv
        ssl
        crypto
        http-parser
        jpeg
        turbojpeg
        z
        EGL
        GLESv2
        )
