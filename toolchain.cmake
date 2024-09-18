# Set the target system to Windows
set(CMAKE_SYSTEM_NAME Windows)

# Specify the cross compiler to use for C++
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

# Specify the cross compiler to use for C
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)

# Specify the linker to use for the cross-compilation
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)