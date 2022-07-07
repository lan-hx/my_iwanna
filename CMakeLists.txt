cmake_minimum_required(VERSION 3.13)

# vcpkg init
if(DEFINED VCPKG_DIR AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE ${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")
endif()

# update qt variables
message("QT_PREFIX_DIR: ${QT_PREFIX_DIR}")
list(APPEND CMAKE_PREFIX_PATH ${QT_PREFIX_DIR})

project(my_iwanna VERSION 0.1 LANGUAGES CXX)

# CTest
enable_testing()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SLOW "slow")

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wmisleading-indentation -Wunused -Wshadow -Wcast-qual -Wcast-align -Wunreachable-code -fno-exceptions -fno-rtti -march=native")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto")
    if(DEFINED SLOW)
        string(REGEX REPLACE " -fno-exceptions" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
        # string(REGEX REPLACE " -fno-rtti" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    endif()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -fstack-protector-all -D_GLIBCXX_ASSERTIONS")
    if(NOT WIN32 AND NOT MSYS)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined")
    endif()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -s")
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # warning
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
    # disable exceptions and RTTI
    string(REGEX REPLACE "/EH[a-z]+" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    string(REGEX REPLACE "/GR" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /nologo /fp:fast /GA /Gd /GL /GR- /GS /guard:cf /permissive- /sdl /Zc:__cplusplus /Zc:forScope /Zc:inline /Zc:rvalueCast /arch:AVX2 /std:c++latest /MP /experimental:module /source-charset:utf-8 /execution-charset:GBK /D \"_CRT_SECURE_NO_WARNINGS\"")
    if(DEFINED SLOW)
        # string(REGEX REPLACE "/GR-" "/GR" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
    endif()
    # /fsanitize=address
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /RTC1 /analyze")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /Zi /Zo")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NOLOGO /LTCG:incremental /MANIFEST /OPT:REF /DYNAMICBASE /NXCOMPAT /DEBUG")
endif ()

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL}")
message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message("CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELWITHDEBINFO: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
message("CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")

find_package(Qt5 CONFIG REQUIRED COMPONENTS Widgets Multimedia)

# clang-format
if (NOT DEFINED CLANG_FORMAT_BIN)
    # attempt to find the binary if user did not specify
    find_program(CLANG_FORMAT_BIN
            NAMES clang-format clang-format-12
            HINTS ${CLANG_SEARCH_PATH})
endif()
if ("${CLANG_FORMAT_BIN}" STREQUAL "CLANG_FORMAT_BIN-NOTFOUND")
    message(WARNING "couldn't find clang-format.")
else()
    message(STATUS "found clang-format at ${CLANG_FORMAT_BIN}")
endif()

file(GLOB_RECURSE ALL_SOURCE_FILES src/**/*.cpp src/**/*.h src/*.cpp src/*.h)
if(NOT DEFINED NO_CLANG_FORMAT)
    add_custom_target(clang_format ALL
            COMMAND ${CLANG_FORMAT_BIN} -i
            ${ALL_SOURCE_FILES}
    )
    message(STATUS "run clang-format on: ${ALL_SOURCE_FILES}")
endif()

# clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (NOT DEFINED CLANG_TIDY_BIN)
    # attempt to find the binary if user did not specify
    find_program(CLANG_TIDY_BIN
            NAMES clang-tidy clang-tidy-12
            HINTS ${CLANG_SEARCH_PATH})
endif()
if ("${CLANG_TIDY_BIN}" STREQUAL "CLANG_TIDY_BIN-NOTFOUND")
    message(WARNING "couldn't find clang-tidy.")
else()
    message(STATUS "found clang-tidy at ${CLANG_TIDY_BIN}")
endif()

set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_BIN}")

include_directories(src/include test/include)

ADD_SUBDIRECTORY(src ${CMAKE_BINARY_DIR}/bin)
ADD_SUBDIRECTORY(test ${CMAKE_BINARY_DIR}/test)