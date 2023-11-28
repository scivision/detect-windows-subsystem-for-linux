cmake_minimum_required(VERSION 3.19)

project(IsWSL LANGUAGES C CXX)

enable_testing()

include(CheckIncludeFile)
include(CheckCXXSymbolExists)
include(CheckCompilerFlag)

option(fortran "use Fortran" on)
if(fortran)
  enable_language(Fortran)
endif()

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.20 AND NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 23)
endif()

# informational for dev users
if(CMAKE_CXX_STANDARD GREATER_EQUAL 23)
  check_cxx_symbol_exists(__cpp_lib_string_contains "version" cpp23_string_contains)
endif()

# set compilers warnings
check_compiler_flag(C -Wall C_WALL)
check_compiler_flag(CXX -Wall CXX_WALL)
if(fortran)
check_compiler_flag(Fortran -Wall Fortran_WALL)
endif()

add_compile_options(
"$<$<AND:$<COMPILE_LANGUAGE:C>,${C_WALL}>:-Wall>"
"$<$<AND:$<COMPILE_LANGUAGE:CXX>,${CXX_WALL}>:-Wall>"
"$<$<AND:$<COMPILE_LANGUAGE:Fortran>,${Fortran_WALL}>:-Wall>"
)

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
