cmake_minimum_required(VERSION 3.16)
project("SyntaxTreeGen" CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

# add_subdirectory(thirdparty/imgui)
file(GLOB MY_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB imgui_sources CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}")
set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 20)

# target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES})
target_sources("${CMAKE_PROJECT_NAME}" PRIVATE
  "src/main.cpp"
  "src/Typing.cpp"
  "src/Grid.cpp"
  "src/SentenceTree.cpp"
  "src/SyntaxTree.cpp"
)
target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${imgui_sources})
target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${rlImGui_sources})

include_directories(
  "${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/"
  "${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/TreeStructure/"
  "${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/"
  "${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui/"
  "${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raylib/"
)

if(CMAKE_HOST_APPLE)
  set(CMAKE_C_COMPILER "/usr/local/opt/gcc@12/bin/gcc-12")
  set(CMAKE_CXX_COMPILER "/usr/local/opt/gcc@12/bin/g++-12")
  add_definitions(-Wno-deprecated-declarations)
  add_definitions(-Wall)
  add_definitions(-Wno-sign-compare)
  set(CMAKE_CXX_FLAGS "-std=c++20")

  target_link_libraries("${CMAKE_PROJECT_NAME}"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/apple/libraylib.a"
  )

  target_link_libraries(${PROJECT_NAME} "-framework IOKit")
  target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
  target_link_libraries(${PROJECT_NAME} "-framework OpenGL")

elseif(CMAKE_HOST_UNIX)
  set(CMAKE_CXX_FLAGS "-std=c++20")
  target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/libraylib.a"
  )

elseif(CMAKE_HOST_WIN32)
  set(STATIC_LINK false)
  if(STATIC_LINK)
    target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/libraylib.a")
  else()
    target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/libraylibdll.a")
  endif()
  if (MSVC)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20 /SUBSYSTEM:WINDOWS -static")
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|CLANG")
    set(CMAKE_CXX_FLAGS "-std=c++20 -mwindows -static")
  endif()
endif()
