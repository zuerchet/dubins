# Source files
set(sources
    Circle.cpp
)

add_library(${PROJECT_NAME}_lib ${sources})

target_include_directories(${PROJECT_NAME}_lib 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>  # <prefix>/include/mylib
)

set_target_properties(${PROJECT_NAME}_lib
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)