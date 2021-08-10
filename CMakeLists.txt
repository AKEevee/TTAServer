cmake_minimum_required(VERSION 3.15)
project(ProjectWork1)

set(CMAKE_CXX_STANDARD 14)

#include_directories(${LIBMONGOCXX_INCLUDE_DIR})
#include_directories(${LIBBSONCXX_INCLUDE_DIR})
#include_directories("/usr/local/include/mongocxx/v_noabi")
#include_directories("/usr/local/include/bsoncxx/v_noabi")
#include_directories("/usr/local/include/libmongoc-1.0")
#include_directories("/usr/local/include/libbson-1.0")
#include_directories("/usr/local/lib")
set(mongoc-1.0_DIR "C:/Program Files (x86)/Project/lib/cmake/mongoc-1.0")

#set(CMAKE_MODULE_PATH Findlibmongoc.cmake)
find_package (mongoc-1.0 1.7 REQUIRED)
add_executable(ProjectWork1 main.cpp)
target_link_libraries (ProjectWork1 PRIVATE mongo::mongoc_static)
#find_package (mongoc-1.0 REQUIRED)
#find_package(libmongoc REQUIRED)
#find_package(libbsoncxx REQUIRED)

#target_link_libraries(ProjectWork1 ${LIBMONGOCXX_LIBRARIES})
#target_link_libraries(ProjectWork1 ${LIBBSONCXX_LIBRARIES})