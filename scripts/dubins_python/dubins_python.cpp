#include "dubins/Dubins.hpp"
#include "dubins/Vector.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <string>

namespace py = pybind11;


PYBIND11_MODULE(dubins_python, m)
{
    m.doc() = "dubins python wrapper";

    using namespace dubins;

    py::class_<Vector2D>(m, "Vector2D")
        .def(py::init<>())
        .def(py::init<double, double>())
        .def_readwrite("x", &Vector2D::x)
        .def_readwrite("y", &Vector2D::y)
        .def("__repr__", [](const Vector2D& val) {
            return "<dubins_python.Vector2D (" + std::to_string(val.x) + ", " + std::to_string(val.y) + ")>";
        });

    py::class_<State>(m, "State")
        .def(py::init<>())
        .def(py::init<Vector2D, double>())
        .def_readwrite("position", &State::position)
        .def_readwrite("heading", &State::heading)
        .def("__repr__", [](const State& val) {
            return "<dubins_python.State {(" + std::to_string(val.position.x) + ", " + std::to_string(val.position.y)
                   + ", " + std::to_string(val.heading) + "}>";
        });

    py::class_<Dubins::Options>(m, "Options")
        .def(py::init<>())
        .def_readwrite("turning_radius", &Dubins::Options::turning_radius)
        .def_readwrite("max_segment_length", &Dubins::Options::max_segment_length)
        .def_readwrite("min_number_of_segments", &Dubins::Options::min_number_of_segments);

    py::class_<Dubins>(m, "Dubins")
        .def(py::init<State, State, Dubins::Options>())
        .def("length", &Dubins::length)
        .def("segmented_path", &Dubins::segmented_path)
        .def("segmented_rsr", &Dubins::segmented_rsr)
        .def("segmented_lsl", &Dubins::segmented_lsl)
        .def("segmented_rsl", &Dubins::segmented_rsl)
        .def("segmented_lsr", &Dubins::segmented_lsr)
        .def("segmented_lrl", &Dubins::segmented_lrl)
        .def("segmented_rlr", &Dubins::segmented_rlr);
}