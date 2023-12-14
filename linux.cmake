set(LINUX_CXX_WARNING_FLAGS "-Wall -Wextra -Wpedantic -Wnon-virtual-dtor -Wold-style-cast -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wduplicated-cond -Wlogical-op -Wuseless-cast")

set(CMAKE_CXX_FLAGS "${LINUX_CXX_WARNING_FLAGS} -march=x86-64 -mtune=skylake -mavx2 -fuse-linker-plugin -fno-rtti -pipe -fno-unwind-tables -fvisibility=hidden -fvisibility-inlines-hidden -fno-strict-aliasing" CACHE INTERNAL "C++ compiler options" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-print-memory-usage -Wl,--sort-section=alignment -Wl,--as-needed" CACHE INTERNAL "Linker options" FORCE)

# Options for DEBUG build
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb -DDEBUG" CACHE INTERNAL "C++ Compiler options for debug build type" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-Wl,-O0" CACHE INTERNAL "Linker options for debug build type" FORCE)

# Options for RELEASE with debug information build
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -ggdb -flto -DNDEBUG" CACHE INTERNAL "C++ Compiler options for release with debug info build type" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "-Wl,-O1 -flto=auto" CACHE INTERNAL "Linker options for release with debug info build type" FORCE)

# Options for RELEASE build
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -flto -DNDEBUG" CACHE INTERNAL "C++ Compiler options for release build type" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-Wl,-O1 -flto=auto" CACHE INTERNAL "Linker options for release build type" FORCE)

