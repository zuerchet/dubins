# Source files
set(sources
    main.cpp
)

add_executable(${PROJECT_NAME}_app ${sources})

target_link_libraries(${PROJECT_NAME}_app 
    PRIVATE 
        ${PROJECT_NAME}_lib 
)

set_target_properties(${PROJECT_NAME}_app
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)