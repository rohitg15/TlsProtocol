set(libtls13_SRCS
    record.h
    handshake.h
    tlsmessages.h
    types.h
    marshal.h
    utils.h
    record.cpp
)

# Declare the library
add_library(libtls13 STATIC
    ${libtls13_SRCS}
)

target_link_libraries(libtls13
    libsocket
)

# Specify here the include directories exported
# by this library
target_include_directories(libtls13 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
