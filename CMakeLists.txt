cmake_minimum_required(VERSION 3.10)
project(Glass VERSION 4.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Recursively find all source files in the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp" "src/*.h")

# Create the shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-window sfml-system)

# Include directories
target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Add compile flags
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
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
