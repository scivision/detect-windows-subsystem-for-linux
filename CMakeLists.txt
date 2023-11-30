cmake_minimum_required(VERSION 3.15...3.28)
# 3.15: COMPILE_LANGUAGE:C,CXX

project(IsWSL LANGUAGES C CXX)

enable_testing()

include(CheckIncludeFile)
include(CheckCXXSymbolExists)
include(CheckCCompilerFlag)
include(CheckFortranCompilerFlag)

option(fortran "use Fortran" on)
if(fortran)
  enable_language(Fortran)
endif()

option(debug "print debug info" on)

if(NOT CMAKE_CXX_STANDARD AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.20)
  set(CMAKE_CXX_STANDARD 23)
endif()

message(STATUS "CMake ${CMAKE_VERSION}  CMAKE_CXX_STANDARD ${CMAKE_CXX_STANDARD}")

# informational for dev users
if(CMAKE_CXX_STANDARD GREATER_EQUAL 23)
  check_cxx_symbol_exists(__cpp_lib_string_contains "version" cpp23_string_contains)
endif()

# set compilers warnings
if(NOT MSVC)
check_c_compiler_flag(-Wall C_WALL)
if(fortran)
check_fortran_compiler_flag(-Wall Fortran_WALL)
endif()
endif()

add_compile_options(
"$<$<AND:$<COMPILE_LANGUAGE:C,CXX>,$<BOOL:${C_WALL}>>:-Wall>"
"$<$<AND:$<COMPILE_LANGUAGE:Fortran>,$<BOOL:${Fortran_WALL}>>:-Wall>"
)

if(debug)
  add_compile_definitions(DEBUG)
endif()

# --- C example
check_include_file("sys/utsname.h" HAVE_UTSNAME_H)

add_library(is_wsl_c OBJECT c/lib.c)
target_include_directories(is_wsl_c PUBLIC include)
target_compile_definitions(is_wsl_c PRIVATE $<$<BOOL:${HAVE_UTSNAME_H}>:HAVE_UTSNAME_H>)

add_executable(main_c c/main.c)
target_link_libraries(main_c PRIVATE is_wsl_c)
add_test(NAME IsWSL_C COMMAND main_c)

# --- C++ example
add_library(is_wsl_cpp OBJECT cpp/lib.cpp)
target_include_directories(is_wsl_cpp PUBLIC include)

add_executable(main_cpp cpp/main.cpp)
target_link_libraries(main_cpp PRIVATE is_wsl_cpp)
add_test(NAME IsWSL_Cpp COMMAND main_cpp)

# --- Fortran example
if(fortran)
  add_executable(main_f fortran/main.f90)
  target_link_libraries(main_f PRIVATE is_wsl_cpp)
  set_property(TARGET main_f PROPERTY LINKER_LANGUAGE Fortran)
  add_test(NAME IsWSL_Fortran COMMAND main_f)
endif()

# --- Python example
find_package(Python COMPONENTS Interpreter)
if(Python_FOUND)
  add_test(NAME IsWSL_Python COMMAND Python::Interpreter ${CMAKE_CURRENT_SOURCE_DIR}/is_wsl.py)
endif()

file(GENERATE OUTPUT .gitignore CONTENT "*")
