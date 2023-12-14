set(WINDOWS_DEFINITIONS "-DWIN32 -D_WINDOWS -DWINVER=0x0601 -D_WIN32_WINNT=0x0601 -DVC_EXTRALEAN -DWIN32_LEAN_AND_MEAN -D_CRT_SECURE_NO_WARNINGS -D_UNICODE -DUNICODE -DLEOS_WINDOWS -DLOG_DEBUG")
set(CMAKE_CXX_FLAGS "${WINDOWS_DEFINITIONS} /arch:AVX2 /MP /permissive- /analyze- /W4 /wd4068 /Zc:__cplusplus /Zc:wchar_t /Zi /Zc:inline /fp:precise /errorReport:prompt /WX- /Zc:forScope /Gd /Zc:__cplusplus /EHa /nologo /diagnostics:classic" CACHE INTERNAL "C++ compiler options" FORCE)

# Options for DEBUG build
set(CMAKE_CXX_FLAGS_DEBUG "/Od /Oy- /sdl -D_DEBUG" CACHE INTERNAL "C++ Compiler options for debug build type" FORCE)

# Options for RELEASE with debug information build
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/GS /Gs /GL /Gw /O2 /Ob3 -DNDEBUG" CACHE INTERNAL "C++ Compiler options for release with debug info build type" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/MAP /DEBUG /OPT:REF /LTCG /MACHINE:X64 /STACK:8000000 /HEAP:8000000" CACHE INTERNAL "Linker options for release with debug info build type" FORCE)

# Options for RELEASE build
set(CMAKE_CXX_FLAGS_RELEASE "/GS- /GR- /GL /Gw /O2 /Ob3 -DNDEBUG" CACHE INTERNAL "C++ Compiler options for release with debug info build type" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/MAP /OPT:REF /LTCG /MACHINE:X64 /STACK:8000000 /HEAP:8000000" CACHE INTERNAL "Linker options for release with debug info build type" FORCE)
