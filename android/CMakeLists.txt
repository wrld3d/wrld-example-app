cmake_minimum_required(VERSION 3.1)

project(eegeo-mobile-example-app)
set(executable_name eegeo-mobile-example-app)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/eegeo/CMakeLists.txt")
  include("${CMAKE_CURRENT_SOURCE_DIR}/libs/eegeo/CMakeLists.txt")
else(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/eegeo/CMakeLists.txt")
  message(FATAL_ERROR "Couldn't detect platform headers. Have you run update.platform.sh?")
endif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/eegeo/CMakeLists.txt")

include(../src/CMakeLists.txt)
include(jni/CMakeLists.txt)
include(libs/CMakeLists.txt)

set (ANDROID_PREBUILT_EEA_LIBS_DIR libs/prebuilt/android-${ANDROID_NDK_ABI_NAME})
set (ANDROID_PREBUILT_LIBS_DIR libs/eegeo/prebuilt/android-${ANDROID_NDK_ABI_NAME})
link_directories(
    ${ANDROID_PREBUILT_EEA_LIBS_DIR}
    ${ANDROID_PREBUILT_LIBS_DIR}
)

# api-host has some name conflicts with example app classes
list(REMOVE_ITEM headers libs/eegeo/eegeo-api-host)
list(REMOVE_ITEM headers libs/eegeo/eegeo-api-host/Android)

set(CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--stub-group-size=2085000")

include_directories(${headers})
link_directories(${linker_search_paths})

set(libs
	eegeo-api-host
	eegeo-api
	eegeo-sdk
	android
	EGL
	GLESv2
	png
	curl
	crypto
	turbojpeg
	http-parser
	jpeg
	log
	ssl
	crypto
	uv
	z
	breakpad_client)

add_library(${executable_name} SHARED ${sources} ${resources})
target_link_libraries(${executable_name} ${libs})

