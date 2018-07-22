set(libtls_SRCS
    record.h
    record.cpp
)

# Declare the library
add_library(libtls STATIC
    ${libtls_SRCS}
)

target_link_libraries(libtls
    libsocket
)

# Specify here the include directories exported
# by this library
target_include_directories(libtls PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
