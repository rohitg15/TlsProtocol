set(libcrypto_SRCS
    random.h
    random.cpp
)


find_library(sodium REQUIRED)

# Declare the library
add_library(libcrypto STATIC
    ${libcrypto_SRCS}
)

target_link_libraries(libcrypto
    sodium
)

# Specify here the include directories exported
# by this library
target_include_directories(libcrypto PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
