cmake_minimum_required(VERSION 3.10)
project(Report)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the cmark-gfm library from the local path
add_subdirectory(libs/cmark-gfm EXCLUDE_FROM_ALL)

# Include directories for project headers
include_directories(includes)

# Include directories for cmark-gfm headers
include_directories(
    libs/cmark-gfm/src
    ${CMAKE_BINARY_DIR}/libs/cmark-gfm/src
    libs/cmark-gfm/extensions
    ${CMAKE_BINARY_DIR}/libs/cmark-gfm/extensions
)

# Automatically collect all .cpp files in the src directory
file(GLOB SOURCES "src/*.cpp")

# Add the executable and source files
add_executable(Report ${SOURCES})

# Link against the cmark-gfm library target
if(CMARK_SHARED)
    target_link_libraries(Report libcmark-gfm)
    target_link_libraries(Report libcmark-gfm-extensions)
elseif(CMARK_STATIC)
    target_link_libraries(Report libcmark-gfm_static)
    target_link_libraries(Report libcmark-gfm-extensions_static)
endif()

# Copy the templates directory to the build directory
add_custom_command(
    TARGET Report POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/templates    # Source directory
    ${CMAKE_BINARY_DIR}/templates    # Destination directory
)