cmake_minimum_required(VERSION 3.13)
project(dsp)

file(GLOB_RECURSE SRC "src/*.cpp" "dsp/*.cpp")

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE "/")

target_compile_options(${PROJECT_NAME} PRIVATE /std:c++20)

if (MSVC)
    # Lib path
    target_link_directories(${PROJECT_NAME} PUBLIC "C:/Program Files/PothosSDR/lib/")

    # Misc headers
    target_include_directories(${PROJECT_NAME} PUBLIC "C:/Program Files/PothosSDR/include/")

    # Volk
    target_link_libraries(${PROJECT_NAME} PUBLIC volk)

else()
    find_package(PkgConfig)

    pkg_check_modules(VOLK REQUIRED volk)

    target_include_directories(${PROJECT_NAME} PUBLIC
        ${VOLK_INCLUDE_DIRS}
    )
    
    target_link_directories(${PROJECT_NAME} PUBLIC
        ${VOLK_LIBRARY_DIRS}
    )

    target_link_libraries(${PROJECT_NAME} PUBLIC
        ${VOLK_LIBRARIES}
    )

    if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        target_link_libraries(${PROJECT_NAME} PUBLIC stdc++fs pthread)
    endif ()

endif ()