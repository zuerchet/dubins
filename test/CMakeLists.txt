# Source files
set(sources
    circle_test.cpp
    vector_test.cpp
    main.cpp
)

# Test Executable
add_executable(${PROJECT_NAME}_test ${sources})

target_link_libraries(${PROJECT_NAME}_test 
    PRIVATE
        gtest
        ${PROJECT_NAME}_lib
)

# Let CMake know we have a test
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test )

