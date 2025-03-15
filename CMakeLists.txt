cmake_minimum_required (VERSION 3.5)

project(EngineMaxim)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(EngineMaxim 
"./MaximEngine/main.cpp"
"./Samples/Common_Files/OS.cpp"
"./Samples/Common_Files/OS.h"
"./Samples/Common_Files/Camera.cpp"
"./Samples/Common_Files/Camera.h"
"./Samples/Common_Files/CookbookSampleFramework.cpp"
"./Samples/Common_Files/CookbookSampleFramework.h"
"./Samples/Common_Files/OrbitingCamera.cpp"
"./Samples/Common_Files/OrbitingCamera.h"
"./MaximEngine/Graphics.cpp"
"./MaximEngine/Graphics.h"
"./MaximEngine/ModelClass.cpp"
"./MaximEngine/ModelClass.h"
"./MaximEngine/Scene.cpp"
"./MaximEngine/Scene.h"
)

add_subdirectory(Cookbook)


add_custom_command(TARGET EngineMaxim POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/Data/ ${CMAKE_BINARY_DIR}/Data/)

if(WIN32)
    
    add_definitions(-DVK_USE_PLATFORM_WIN32_KHR)
    target_link_libraries(EngineMaxim PUBLIC Cookbook)

endif(WIN32)

if(UNIX)

    add_definitions(-DVK_USE_PLATFORM_XLIB_KHR)
    
    find_package(X11 REQUIRED)

    message(STATUS "X11_FOUND = ${X11_FOUND}")
    message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
    message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

    include_directories(${X11_INCLUDE_DIR})

    link_directories(${X11_LIBRARIES})

    target_link_libraries(EngineMaxim ${X11_LIBRARIES} Cookbook)

endif(UNIX)

target_include_directories(EngineMaxim PUBLIC "./Cookbook" "./Samples/Common_Files" "./Library/Common_Files" "./Library/Source_Files" "./External")