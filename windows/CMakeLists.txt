cmake_minimum_required(VERSION 3.1)

set(CMAKE_TOOLCHAIN_FILE "../cmake/toolchain/windows/windows.cmake")

set(windows_abi_name "x64")   # Pass this in?
if(NOT ${WINDOWS}) 
	message(FATAL_ERROR "Incorrect toolchain set: ${CMAKE_TOOLCHAIN_FILE}")
endif(NOT ${WINDOWS})

project(ExampleApp)
set(executable_name ExampleApp)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/eegeo/CMakeLists.txt")
  include("${CMAKE_CURRENT_SOURCE_DIR}/libs/eegeo/CMakeLists.txt")
else(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/eegeo/CMakeLists.txt")
  message(FATAL_ERROR "Couldn't detect platform headers. Have you run update.platform.sh?")
endif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/eegeo/CMakeLists.txt")

set(precompiled_header ExampleAppPch.h)
set(precompiled_header_result WindowsPch_$(Configuration)_$(Platform).pch)


include(../src/CMakeLists.txt)
include(src/CMakeLists.txt)


add_definitions(-D__BYTE_ORDER__ -D__ORDER_LITTLE_ENDIAN__ -D_HAS_EXCEPTIONS=0 -DHAVE_STRUCT_TIMESPEC=1 -DNOMINMAX=1 -DPTW32_STATIC_LIB -DCURL_STATICLIB)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi /EHsc /Oi /GS /Gy /wd4068 /Gd /MP /WX /Zm300 /Yu${precompiled_header} /FI${precompiled_header} /Fp${precompiled_header_result}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /LTCG /INCREMENTAL:NO /OPT:REF")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS} /NODEFAULTLIB:LIBCMT.lib")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /DDEBUG /GF")
set(CMAKE_SYSTEM_VERSION 8.1)

remove_visual_studio_compiler_flag_debug("/RTC1")

set(linker_search_paths
	libs/eegeo/prebuilt/${windows_abi_name}
	libs/eegeo/ANGLE/${windows_abi_name}
	libs/eegeo/pthread/${windows_abi_name}
)

include_directories(${headers})
link_directories(${linker_search_paths})

set(libs
	eegeo-sdk
	libEGL
	libGLESv2
	png
	curl
	turbojpeg
	http-parser
	xml2
	pthreadVC2
	jpeg
	locationapi
	libuv
	IPHlpApi
	UserEnv
	psapi
	version
	wininet
	)

add_library(${executable_name} SHARED ${sources} ${resources})
add_dotnet_reference(${executable_name} "WindowsBase")
target_link_libraries(${executable_name} ${libs})

#############################################
## Add C++ project reference to C# project ##
#############################################
set(cs_project_file "${CMAKE_SOURCE_DIR}/ExampleApp/ExampleAppWPF/ExampleAppWPF.csproj")
set(cs_project_input_file "${CMAKE_CURRENT_BINARY_DIR}/ExampleAppWPF.csproj.in")

# Get C++ project Windows style path relative to C# project
file(RELATIVE_PATH relative_build_dir "${CMAKE_SOURCE_DIR}/ExampleApp/ExampleAppWPF" ${CMAKE_CURRENT_BINARY_DIR}/ExampleApp.vcxproj)
string(REPLACE "/" "\\" wpf_relative_path_to_this_project ${relative_build_dir})

# Create input file based off existing C# project
execute_process(COMMAND cp "${cs_project_file}" ${cs_project_input_file})
execute_process(COMMAND sed -i "s,<ProjectReference.*>,<ProjectReference Include=\"@CMAKE_EXAMPLEAPP_PROJECT_INCLUDE_PATH@\">,g" ${cs_project_input_file})

# Substitute this C++ project's path into input file and replace C# project
set(CMAKE_EXAMPLEAPP_PROJECT_INCLUDE_PATH ${wpf_relative_path_to_this_project})
configure_file(${cs_project_input_file} ${cs_project_file})

include_external_msproject(ExampleAppWPF ${cs_project_file})