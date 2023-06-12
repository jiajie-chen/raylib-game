# region CMake
cmake_minimum_required(VERSION 3.15)
project(collapse_rl VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
# endregion

# region Dependencies
include(FetchContent)
# region raylib
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        fec96137e8d10ee6c88914fbe5e5429c13ee1dac # v4.5.0
  GIT_SHALLOW ON
)
FetchContent_GetProperties(raylib)
if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
  set(FETCHCONTENT_QUIET NO)
  FetchContent_Populate(raylib)
  set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
  add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
endif()
# endregion
# region raylib-cpp
FetchContent_Declare(
    raylib_cpp
    GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
    GIT_TAG        71333029c1b916b00ee155b92c3a26bf48da27b8 # v4.5.0
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(raylib_cpp)
# endregion
# region flecs
FetchContent_Declare(
  flecs
  GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
  GIT_TAG        2bcb38a868e54ccac74c075a72944600f18a083f # v3.2.3
  GIT_SHALLOW ON
)
FetchContent_MakeAvailable(flecs)
# endregion
# endregion

# region Project Build
add_executable(${PROJECT_NAME})
add_subdirectory(src)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    raylib
    raylib_cpp
    flecs::flecs_static
)

# region OSX
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
# endregion
# endregion
