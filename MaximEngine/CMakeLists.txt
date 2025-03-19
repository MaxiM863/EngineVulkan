add_executable(EngineMaxim main.cpp)


target_sources(EngineMaxim PRIVATE Graphics.cpp Graphics.h
"../Samples/Common_Files/OS.cpp"
"../Samples/Common_Files/Camera.cpp"
"../Samples/Common_Files/CookbookSampleFramework.cpp"
"../Samples/Common_Files/OrbitingCamera.cpp")

if(WIN32)
    
    add_definitions(-DVK_USE_PLATFORM_WIN32_KHR)
    target_link_libraries(EngineMaxim PRIVATE Cookbook)

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

target_include_directories(EngineMaxim PRIVATE "../Cookbook" "../Samples/Common_Files" "../Library/Common_Files" "../Library/Source_Files" "../External")