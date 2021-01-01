# Source files
set(sources
    angle_test.cpp
    circle_test.cpp
    dubins_test.cpp
    line_test.cpp
    vector_test.cpp
    main.cpp
)

# Test Executable
add_executable(${PROJECT_NAME}_test ${sources})

target_link_libraries(${PROJECT_NAME}_test 
    PRIVATE
        gtest
        ${PROJECT_NAME}_static
)

set_target_properties(${PROJECT_NAME}_test
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

# Let CMake know we have a test
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test )

