set(TARGET_NAME gtest_extension)

set(TARGET_SOURCES
    "gtest_extension.cpp"
)

add_library(${TARGET_NAME} STATIC
    ${TARGET_SOURCES}
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${TARGET_NAME} PRIVATE
        /wd5045
    )
endif()

target_include_directories(${TARGET_NAME}
    PUBLIC "include" ${INCLUDE_DIRECTORIES_TO_PROPAGATE}
)

target_link_libraries(${TARGET_NAME}
    GTest::gmock
)

cmake_language(CALL ${PROJECT_NAME}_set_target_cpp_compiler_flags ${TARGET_NAME})
