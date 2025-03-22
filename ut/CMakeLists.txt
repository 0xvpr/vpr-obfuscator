include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../ut
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../external/doctest
)

add_executable(
    unit-tests
    ut.cpp
)
add_test(NAME UnitTests COMMAND unit-tests)

if(MSVC)
    add_compile_options( /O2 /MTd )
    add_compile_options( /W4 /WX )
else()
    add_compile_options( -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror -Wconversion )
    add_compile_options( -O3 )
endif()

# Optionally enable sanitizers for debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(unit-tests PRIVATE -fsanitize=address,undefined)
    target_link_options(unit-tests PRIVATE -fsanitize=address,undefined)
endif()
