# Copyright 2013-2018 by Martin Moene
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# -Dlest_FEATURE_LITERAL_SUFFIX=0
# -Dlest_FEATURE_REGEX_SEARCH=0
# -Dlest_FEATURE_TIME=1

cmake_minimum_required( VERSION 2.8 )

project( test )

set( HAS_CPP11 TRUE )
set( std11 "-std=c++11" )

set( cpp_options
        -Wall -Wextra
        )

if ( LEST_EXTRA_WARNINGS )
    set( cpp98_extra_options
            -fdiagnostics-show-option
            -fstrict-aliasing
            -fvisibility=hidden
            -pedantic # : error: ISO C++11 requires at least one argument for the "..." in a variadic macro
            -pedantic-errors
            -Wundef
            -Wno-missing-braces
            -Waggregate-return
            -Wcast-align
            -Wcast-qual
            -Wconversion
            -Wctor-dtor-privacy
            -Wdisabled-optimization
            -Wdouble-promotion
            -Weffc++
            -Wfloat-equal
            -Wformat=2
            -Winline
            -Winvalid-pch
            -Wlogical-op
            -Wmissing-declarations
            -Wmissing-include-dirs
            -Wnoexcept
            -Wnon-virtual-dtor
            -Wold-style-cast
            -Woverloaded-virtual
            -Wpointer-arith
            -Wredundant-decls
            -Wshadow
            -Wsign-conversion
            -Wstrict-overflow=5
            -Wswitch-default
            -Wswitch-enum
            -Wtrampolines
            -Wuseless-cast
            -Wvector-operation-performance
            -Wwrite-strings
            -Werror
            )

    set( cpp11_extra_options
            ${cpp98_extra_options}
            -Wzero-as-null-pointer-constant
            )

endif() # LEST_EXTRA_WARNINGS

set( cpp11_options ${cpp_options} )

# configure unit tests via CTest:

enable_testing()

add_executable(test_library test_library.cpp)
target_compile_options(test_library  PUBLIC ${std11} ${cpp11_options} ${cpp11_extra_options} )

add_test(NAME test_library    COMMAND test_library )
add_test(NAME list_version    COMMAND test_library --version )
add_test(NAME list_tags       COMMAND test_library --list-tags )
add_test(NAME list_tests      COMMAND test_library --list-tests )
add_test(NAME test_container  COMMAND test_library container)

set_property(TEST test_library  PROPERTY LABELS verso unittest )

# add_test( NAME list_version              COMMAND test_library --version )


# end of file
