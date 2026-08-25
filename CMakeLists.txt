cmake_minimum_required(VERSION 3.20)

project(biocomp-uff LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

file(GLOB EXERCISE_DIRS CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/exercicio[0-9]*"
)

foreach(EXERCISE_DIR IN LISTS EXERCISE_DIRS)
    if(IS_DIRECTORY "${EXERCISE_DIR}")
        get_filename_component(EXERCISE_NAME "${EXERCISE_DIR}" NAME)
        set(EXERCISE_SOURCE "${EXERCISE_DIR}/main.cpp")

        if(EXERCISE_NAME MATCHES "^exercicio[0-9]+$" AND EXISTS "${EXERCISE_SOURCE}")
            add_executable("${EXERCISE_NAME}" "${EXERCISE_SOURCE}")

            target_compile_options("${EXERCISE_NAME}" PRIVATE
                -Wall
                -Wextra
            )
        endif()
    endif()
endforeach()
