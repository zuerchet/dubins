# Add externals for testing
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) AND BUILD_TESTING)
    # Setup gtest
    option(BUILD_GMOCK "" OFF)
    option(INSTALL_GTEST "" OFF)
    add_subdirectory(googletest)
endif()