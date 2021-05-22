#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

#include "../include/parser.hpp"

namespace py = pybind11;


PYBIND11_MODULE(Parser, m){

  // Select non-cache accessing function

  double (MathParser::*e)(mp_RPN) = &MathParser::eval;
  e = nullptr;
  e = &MathParser::eval;

  py::class_<mp_RPN>(m, "mp_RPN")
    .def_readwrite("RPN", &mp_RPN::RPN)
    .def_readwrite("RPN_values", &mp_RPN::RPNValues);

  m.def("evaluate", &evaluate);

  py::class_<MathParser>(m, "MathParser")
    .def(py::init())
    .def("append_variable", &MathParser::appendVariable)
    .def("delete_variable", &MathParser::deleteVariable)
    .def("reverse_polish_notation", &MathParser::reversePolishNotation)
    .def("eval", e);
}
