cmake_minimum_required(VERSION 2.8.2)
set (CMAKE_CXX_STANDARD 14)

project(myProject)

enable_testing()

add_subdirectory(main)
# add_subdirectory(test)
add_subdirectory(libfoo)
# add_subdirectory(libtls)
add_subdirectory(libcrypto)
add_subdirectory(libtls13)
add_subdirectory(libsocket)
