cmake_minimum_required(VERSION 3.16)
project("myGame")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/open_spiel/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/open_spiel/open_spiel_core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/open_spiel/games/chess)
file(GLOB_RECURSE OPEN_SPIEL_CORE ${CMAKE_CURRENT_SOURCE_DIR}/src/open_spiel/open_spiel_core/*)
file(GLOB_RECURSE OPEN_SPIEL_CHESS ${CMAKE_CURRENT_SOURCE_DIR}/src/open_spiel/games/chess/* )
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)

message("First foreach")
foreach(file ${OPEN_SPIEL_CORE})
    message(STATUS "  ${file}")
endforeach()
message("Second foreach")
foreach(file ${OPEN_SPIEL_CHESS})
    message(STATUS "  ${file}")
endforeach()
#if (EMSCRIPTEN)
  #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
  #set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so that you can directly open it.
#endif ()

add_executable(${PROJECT_NAME} ${OPEN_SPIEL_CHESS} ${OPEN_SPIEL_CORE} ${SOURCE_FILES})
add_subdirectory("raylib")
add_subdirectory(abseil-cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC 
  raylib 
  absl::algorithm
  absl::flags
  absl::flags_parse
  absl::flat_hash_map
  absl::optional
  absl::random_random
  absl::str_format
  absl::strings
  absl::time)
