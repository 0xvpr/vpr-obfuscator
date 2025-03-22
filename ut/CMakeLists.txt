include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/ut
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/doctest
)

# Build test executable
add_executable(
    unit-tests
    ut.cpp
)

# Define your include directory
# Recommended compiler flags
if(MSVC)
add_compile_options(/O2 /MTd)
add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror -Wconversion -Winteger-overflow -Winteger-underflow -Wsign-conversion)
add_compile_options(-O3)
endif()

# Optionally enable sanitizers for debug
#if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    #target_compile_options(obfuscator_tests PRIVATE -fsanitize=address,undefined)
    #target_link_options(obfuscator_tests PRIVATE -fsanitize=address,undefined)
#endif()
