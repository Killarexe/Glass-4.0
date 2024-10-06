cmake_minimum_required(VERSION 3.10)
project(Glass VERSION 4.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

include(FetchContent)
FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.x
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM)
FetchContent_MakeAvailable(SFML)

# Recursively find all source files in the src directory
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/")

# Create the shared library
if(BUILD_SHARED_LIBS)
  add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
else()
  add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})
endif()

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-window sfml-system)

# Include directories
target_include_directories(${PROJECT_NAME} 
    PUBLIC 
      $<INSTALL_INTERFACE:include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
      ${PROJECT_INCLUDE}
)

# Add compile flags
target_compile_options(${PROJECT_NAME} PRIVATE
  -Wall
  -Wpedantic
  -O2
)

# Optionally, you can add different flags for Debug and Release builds
target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>:-g -O0>
  $<$<CONFIG:Release>:-O3>
)

# Set the output name of the library
set_target_properties(${PROJECT_NAME} PROPERTIES
  OUTPUT_NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Install the library
install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

# Install the headers
install(DIRECTORY include/ DESTINATION include)

# Generate and install export file
install(EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION lib/cmake/${PROJECT_NAME}
)
