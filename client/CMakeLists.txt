cmake_minimum_required(VERSION 3.8)
project(northernlights)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
endif()

if(WIN32)
    set(SCREEN_CAPTURE_PLATFORM_SRC     
    )
    set(SCREEN_CAPTURE_PLATFORM_INC     
       include/win32 
    )
elseif(UNIX)
  set(SCREEN_CAPTURE_PLATFORM_SRC 
       src/unix/udpcontroller.cpp
    )
	find_package(X11 REQUIRED)
	if(!X11_XTest_FOUND)
 		message(FATAL_ERROR "X11 extensions are required, but not found!")
	endif()
	if(!X11_Xfixes_LIB)
 		message(FATAL_ERROR "X11 fixes extension is required, but not found!")
	endif()
	set(SCREEN_CAPTURE_PLATFORM_INC include/unix ${X11_INCLUDE_DIR})
endif()

include_directories(
    include 
    ${SCREEN_CAPTURE_PLATFORM_INC} 
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/color.cpp
    src/image.cpp
    src/screensource.cpp
	${SCREEN_CAPTURE_PLATFORM_SRC}
 )

 find_package(X11 REQUIRED)
 if(!X11_XTest_FOUND)
      message(FATAL_ERROR "X11 extensions are required, but not found!")
 endif()
 if(!X11_Xfixes_LIB)
      message(FATAL_ERROR "X11 fixes extension is required, but not found!")
 endif()
 find_package(Threads REQUIRED)
 set(${PROJECT_NAME}_PLATFORM_LIBS
     ${X11_LIBRARIES}
     ${X11_Xfixes_LIB}
     ${X11_XTest_LIB}
     ${X11_Xinerama_LIB}
     ${CMAKE_THREAD_LIBS_INIT}
 )
 
target_link_libraries(${PROJECT_NAME} screen_capture_lite ${${PROJECT_NAME}_PLATFORM_LIBS}) 