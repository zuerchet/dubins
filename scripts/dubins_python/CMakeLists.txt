pybind11_add_module(dubins_python dubins_python.cpp)

set_target_properties(dubins_python
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_link_libraries(dubins_python 
    PRIVATE
        ${PROJECT_NAME}_shared
)