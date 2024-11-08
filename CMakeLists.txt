cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_FLAGS "-std=c++20")
if(APPLE)
  add_definitions(-Wno-deprecated-declarations)
  add_definitions(-Wall)
  add_definitions(-Wno-sign-compare)
endif()

set(CMAKE_C_COMPILER "/usr/local/opt/gcc@12/bin/gcc-12")
set(CMAKE_CXX_COMPILER "/usr/local/opt/gcc@12/bin/g++-12")

project(SyntaxTreeGen)

if(NOT APPLE)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  set(RAYLIB_VERSION 5.0)
  find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
  if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
      raylib
      DOWNLOAD_EXTRACT_TIMESTAMP OFF
      URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
      set(FETCHCONTENT_QUIET NO)
      FetchContent_Populate(raylib)
      set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
      add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
  endif()
endif()

# Albert
# include(FetchContent)
# set(RAYLIB_VERSION 5.0)
# FetchContent_Declare(
#     raylib
#     URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
#     FIND_PACKAGE_ARGS ${RAYLIB_VERSION}
# )
# set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
# FetchContent_MakeAvailable(raylib)

add_subdirectory(thirdparty/raylib)
add_subdirectory(thirdparty/imgui)
file(GLOB_RECURSE imgui_sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui/*.cpp")
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}")
set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 20)

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES} )
target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${imgui_sources} )
target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${rlImGui_sources} )

if(MSVC) # If using the VS compiler...
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
	set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") #no console
endif()

include_directories(
  "${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/"
  "${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/TreeStructure/"
  "${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui/"
)

if (APPLE)
  include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raylib/")
else()
  include_directories("${CMAKE_PROJECT_NAME}" PUBLIC ${PROJECT_NAME} raylib)
endif()


target_link_libraries("${CMAKE_PROJECT_NAME}" "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raylib/lib/libraylib.a")
# target_link_libraries(${PROJECT_NAME} raylib)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
