cmake_minimum_required (VERSION 3.0)

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
add_definitions(-DVK_USE_PLATFORM_WIN32_KHR)
add_subdirectory(Cookbook)
target_link_libraries(EngineMaxim PUBLIC Cookbook)
target_include_directories(EngineMaxim PUBLIC "./Cookbook" "./Samples/Common_Files" "./Library/Common_Files" "./Library/Source_Files" "./External")