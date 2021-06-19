#include "puzz_api.cpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(puzzpy, m)
{
    py::class_<PuzzTable>(m, "PuzzTable")
        .def(py::init<>())
        .def(py::init<int>())
        .def(py::init<string, int, int, int>())
        .def("get_turn", &PuzzTable::get_turn)
        .def("next_tables", &PuzzTable::next_tables)
        .def("eval_otoshi", &PuzzTable::eval_otoshi)
        .def("eval_ochi", &PuzzTable::eval_ochi)
        .def("get_table", &PuzzTable::get_table)
        .def("get_XY_as_table", &PuzzTable::get_XY_as_table)
        .def("show_table", &PuzzTable::show_table);
    m.doc() = "pybind11 example plugin"; // optional module docstring
}
