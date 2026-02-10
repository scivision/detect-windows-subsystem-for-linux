cmake_minimum_required(VERSION 3.15...4.2)
# 3.15: COMPILE_LANGUAGE:C,CXX

project(IsWSL LANGUAGES C CXX)

enable_testing()

include(CheckIncludeFile)
include(CheckCXXSymbolExists)

include(CheckLanguage)
check_language(Fortran)
if(CMAKE_Fortran_COMPILER)
  set(fortran true)
  enable_language(Fortran)
endif()

option(debug "print debug info" on)

set(CMAKE_CXX_STANDARD 20)

message(STATUS "CMake ${CMAKE_VERSION}  kernel: ${CMAKE_HOST_SYSTEM_VERSION}")

check_cxx_symbol_exists(__cpp_lib_starts_ends_with "version" cpp20_starts_ends_with)

# set compilers warnings
if(NOT MSVC)
add_compile_options(
"$<$<COMPILE_LANGUAGE:C,CXX>:-Wall>"
"$<$<COMPILE_LANG_AND_ID:C,GNU>:-Wno-unused-function>"
)
endif()

if(debug)
  add_compile_definitions(DEBUG)
endif()

# CMake detect WSL
if(CMAKE_HOST_SYSTEM_VERSION MATCHES "microsoft-standard-WSL2$")
  set(wsl 2)
elseif(CMAKE_HOST_SYSTEM_VERSION MATCHES "-Microsoft$")
  set(wsl 1)
else()
  set(wsl 0)
endif()

# --- C example
add_library(is_wsl_c OBJECT c/lib.c)
target_include_directories(is_wsl_c PUBLIC include)

add_executable(main_c c/main.c)
target_link_libraries(main_c PRIVATE is_wsl_c)

add_test(NAME IsWSL_C COMMAND main_c)

# --- C++ example
add_library(is_wsl_cpp OBJECT cpp/lib.cpp)
target_include_directories(is_wsl_cpp PUBLIC include)
target_compile_definitions(is_wsl_cpp PRIVATE $<$<BOOL:${debug}>:DEBUG>)

add_executable(main_cpp cpp/main.cpp)
target_link_libraries(main_cpp PRIVATE is_wsl_cpp)

add_test(NAME IsWSL_Cpp COMMAND main_cpp)


set_property(TEST IsWSL_C IsWSL_Cpp PROPERTY PASS_REGULAR_EXPRESSION "WSL:[ ]+${wsl}")

# --- Fortran example
if(fortran)
  add_executable(main_f fortran/main.f90)
  target_link_libraries(main_f PRIVATE is_wsl_cpp)
  set_property(TARGET main_f PROPERTY LINKER_LANGUAGE Fortran)

  add_test(NAME IsWSL_Fortran COMMAND main_f)
  set_property(TEST IsWSL_Fortran PROPERTY PASS_REGULAR_EXPRESSION "WSL:[ ]+${wsl}")
endif()

# --- Python example
find_package(Python COMPONENTS Interpreter)
if(Python_FOUND)
  add_test(NAME IsWSL_Python COMMAND Python::Interpreter ${CMAKE_CURRENT_SOURCE_DIR}/is_wsl.py)
  set_property(TEST IsWSL_Python PROPERTY PASS_REGULAR_EXPRESSION "WSL:[ ]+${wsl}")
endif()

file(GENERATE OUTPUT .gitignore CONTENT "*")
