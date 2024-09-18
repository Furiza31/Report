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

# Link the cmark-gfm library
if(CMARK_SHARED)
    target_link_libraries(Report libcmark-gfm)
    target_link_libraries(Report libcmark-gfm-extensions)
elseif(CMARK_STATIC)
    target_link_libraries(Report libcmark-gfm_static)
    target_link_libraries(Report libcmark-gfm-extensions_static)
endif()

# Ensure ABI compatibility across all targets
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)

# Special handling for Windows platform
if(WIN32)
    set(BUILD_FOR_WIN TRUE)
    target_compile_definitions(Report PRIVATE _WIN32)

    # Ensure that the DLLs are copied to the output directory after build
    add_custom_command(TARGET Report POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:libcmark-gfm> $<TARGET_FILE_DIR:Report>)

    add_custom_command(TARGET Report POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:libcmark-gfm-extensions> $<TARGET_FILE_DIR:Report>)

    # Manually copy known MinGW DLLs (adjust path if needed)
    add_custom_command(TARGET Report POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        /usr/lib/gcc/x86_64-w64-mingw32/10-posix/libstdc++-6.dll $<TARGET_FILE_DIR:Report>)

    add_custom_command(TARGET Report POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        /usr/lib/gcc/x86_64-w64-mingw32/10-posix/libgcc_s_seh-1.dll $<TARGET_FILE_DIR:Report>)

    add_custom_command(TARGET Report POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        /usr/x86_64-w64-mingw32/lib/libwinpthread-1.dll $<TARGET_FILE_DIR:Report>)
endif()

# Copy the templates directory to the build directory
add_custom_command(
    TARGET Report POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/templates    # Source directory
    ${CMAKE_BINARY_DIR}/templates    # Destination directory
)
