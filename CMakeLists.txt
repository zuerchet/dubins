cmake_minimum_required(VERSION 3.5)
project(dubins
    VERSION 1.0
    DESCRIPTION "Calculate dubins shortest paths."
    LANGUAGES CXX
)

# Check that this is the the only project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Turn on compile commands
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    # Add testing
    include(CTest)

    # Docs only available if this is the main app
    find_package(Doxygen)
    if(Doxygen_FOUND)
        add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found, not building docs")
    endif()
endif()

# Build externals
add_subdirectory(extern)

# Build library
add_subdirectory(src)

# Build application
add_subdirectory(app)

# Build tests
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) AND BUILD_TESTING)
    add_subdirectory(test)
endif()