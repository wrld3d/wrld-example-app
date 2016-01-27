cmake_minimum_required(VERSION 3.1)

project(ExampleApp)
set(executable_name ExampleApp)

include("src/CMakeLists.txt")

macro (include_platform_headers platform_header_list)
    file(GLOB_RECURSE new_list ios/Include/eegeo/*.h)
    set(dir_list "")
    foreach(file_path ${new_list})
        get_filename_component(dir_path ${file_path} PATH)
        set(dir_list ${dir_list} ${dir_path})
    endforeach()
    list(REMOVE_DUPLICATES dir_list)
    set(${platform_header_list} ${dir_list})
endmacro()

###############################################
##### IOS SPECIFIC COMPILE/LINK SETTINGS ######
###############################################

if(${IOS})
    SET (MACOSX_BUNDLE_GUI_IDENTIFIER "com.eegeo.ExampleApp")

    # plist vars
    SET(EEGEO_PLIST_BUNDLE_EXECUTABLE "\${EXECUTABLE_NAME}")
    SET(EEGEO_PLIST_BUNDLE_IDENTIFIER "eegeo.\${PRODUCT_NAME:rfc1034identifier}")
    SET(EEGEO_PLIST_BUNDLE_SHORT_VERSION_STRING "\${PRODUCT_VERSION}")
    SET(EEGEO_PLIST_BUNDLE_DISPLAY_NAME "Eegeo Example")

    SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/templates/ios)

    include("ios/CMakeLists.txt")

    include_platform_headers(platform_header_list)
    set(headers ${headers} ${platform_header_list})

    set(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")
    set(CMAKE_OSX_ARCHITECTURES "armv7;arm64;i386")
    set(IOS_WARNING_FLAGS "-Wmost -Werror -Wno-four-char-constants -Wno-unknown-pragmas -Wno-reorder")

    if(${COMPILE_CPP_03})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -x objective-c++ ${IOS_WARNING_FLAGS}")
        set(eegeo_sdk_lib "-lapps-on-maps")
    else(${COMPILE_CPP_03})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -x objective-c++ -DCOMPILE_CPP_11 ${IOS_WARNING_FLAGS}")
        set(eegeo_sdk_lib "-lapps-on-maps-cpp11")
    endif(${COMPILE_CPP_03})

    SET(ios_frameworks 
      "-framework CoreLocation
      -framework MobileCoreServices 
      -framework SystemConfiguration 
      -framework CFNetwork 
      -framework GLKit 
      -framework OpenGLES 
      -framework UIKit 
      -framework Foundation 
      -framework QuartzCore 
      -framework AVFoundation 
      -framework CoreGraphics 
      -framework CoreData
      -framework CoreLocation")

    SET(linker_search_paths "-Lios/Include/eegeo -Lios/Include")
    SET(libs "${eegeo_sdk_lib} -lturbojpeg -lz -lcurl -luv -lFlurry_6.0.0")
    SET(CMAKE_EXE_LINKER_FLAGS "${ios_frameworks} ${linker_search_paths} ${libs}")

    include_directories(${headers})

    add_executable(${executable_name} MACOSX_BUNDLE ${sources} ${resources} ${storyboards})

    set(
    allresources
    ${resources}
    ${storyboards}
    )

    set_target_properties(
    ${executable_name} 
    PROPERTIES 
    RESOURCE "${allresources}"
    )


endif(${IOS})



#########################################
##### XCODE (IOS) PROJECT SETTINGS ######
#########################################

if(${IOS})
  set_xcode_property (${executable_name} GCC_TREAT_WARNINGS_AS_ERRORS "YES")
  set_xcode_property (${executable_name} CODE_SIGN_IDENTITY "iPhone Developer")
  set_xcode_property (${executable_name} IPHONEOS_DEPLOYMENT_TARGET "5.0")
  set_xcode_property (${executable_name} TARGETED_DEVICE_FAMILY "1,2")
  set_xcode_property (${executable_name} ENABLE_BITCODE "No")

  set_xcode_property (${executable_name} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
  set_xcode_property (${executable_name} ASSETCATALOG_COMPILER_LAUNCHIMAGE_NAME "LaunchImage")
  set_xcode_property (${executable_name} COMBINE_HIDPI_IMAGES "No")

  set_xcode_property(${executable_name} GCC_PRECOMPILE_PREFIX_HEADER "YES")
  set_xcode_property(${executable_name} GCC_PREFIX_HEADER "ios/ExampleApp/ExampleApp-Prefix.pch")


  if(${COMPILE_CPP_03})
      set_xcode_property(${executable_name} CLANG_CXX_LANGUAGE_STANDARD "c++98")
      set_xcode_property(${executable_name} CLANG_CXX_LIBRARY "libstdc++")
  else(${COMPILE_CPP_03})
      add_definitions(-DCOMPILE_CPP_11)
      set_xcode_property(${executable_name} CLANG_CXX_LANGUAGE_STANDARD "c++11")
      set_xcode_property(${executable_name} CLANG_CXX_LIBRARY "libc++")
  endif(${COMPILE_CPP_03})

  set_target_properties(${PROJECT_NAME}
                    PROPERTIES
                    XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "NO"
   )
endif(${IOS})
