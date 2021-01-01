# Header files (since clangd cannot seem to pick them up in the include paths)
# function(ADD_HEADERS)
#     foreach(HEADER IN LISTS ARGV)
#         set(headers ${headers} ${${PROJECT_NAME}_SOURCE_DIR}/include/dubins/${HEADER})
#     endforeach()
#     set(headers ${headers} PARENT_SCOPE)
# endfunction()

# add_headers(
#     Circle.hpp
#     Vector.hpp
#     Line.hpp
# )

# Source files
set(sources
    Circle.cpp
    Dubins.cpp
    Line.cpp
)

# Object target (so we only compile once)
add_library(${PROJECT_NAME}_objlib OBJECT ${sources})

target_include_directories(${PROJECT_NAME}_objlib 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>  # <prefix>/include/mylib
)

set_target_properties(${PROJECT_NAME}_objlib
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        POSITION_INDEPENDENT_CODE TRUE  # Needed for shared libraries
)

# Create static and shared libraries
add_library(${PROJECT_NAME}_shared SHARED)
add_library(${PROJECT_NAME}_static STATIC)

target_link_libraries(${PROJECT_NAME}_shared PUBLIC ${PROJECT_NAME}_objlib)
target_link_libraries(${PROJECT_NAME}_static PUBLIC ${PROJECT_NAME}_objlib)

set_target_properties(${PROJECT_NAME}_shared
    PROPERTIES
        OUTPUT_NAME ${PROJECT_NAME}
)
set_target_properties(${PROJECT_NAME}_static
    PROPERTIES
        OUTPUT_NAME ${PROJECT_NAME}
)
