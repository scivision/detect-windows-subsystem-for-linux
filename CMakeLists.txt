cmake_minimum_required(VERSION 3.20)

project(IsWSL LANGUAGES C CXX)

enable_testing()

include(CheckIncludeFile)

option(fortran "use Fortran" on)
if(fortran)
  enable_language(Fortran)
endif()

set(CMAKE_CXX_STANDARD 23)

# --- C example
check_include_file("sys/utsname.h" HAVE_UTSNAME_H)

add_library(is_wsl_c OBJECT lib.c)
target_include_directories(is_wsl_c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(is_wsl_c PRIVATE $<$<BOOL:${HAVE_UTSNAME_H}>:HAVE_UTSNAME_H>)

add_executable(main_c main.c)
target_link_libraries(main_c PRIVATE is_wsl_c)
add_test(NAME IsWSL_C COMMAND main_c)

# --- C++ example
add_library(is_wsl_cpp OBJECT lib.cpp)
target_include_directories(is_wsl_cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main_cpp main.cpp)
target_link_libraries(main_cpp PRIVATE is_wsl_cpp)
add_test(NAME IsWSL_Cpp COMMAND main_cpp)

# --- Fortran example
if(fortran)
  add_executable(main_f main.f90)
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
