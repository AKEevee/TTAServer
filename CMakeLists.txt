cmake_minimum_required(VERSION 3.15)
project(ProjectWork1)

set(CMAKE_CXX_STANDARD 14)
set(mongoc-1.0_DIR "C:/Program Files (x86)/Project/lib/cmake/mongoc-1.0")

find_package (mongoc-1.0 1.7 REQUIRED)
add_executable(ProjectWork1 main.cpp TTAprocessing.h)
target_link_libraries (ProjectWork1 PRIVATE mongo::mongoc_static)
