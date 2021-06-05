#include <pybind11/cast.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stack>
#include <vector>
#include <iostream>

#include "MathParser/include/parser.hpp"

namespace py = pybind11;

class py_Parser : public MathParser{
public:
  void _appendVariable(std::string name, double value){
    var_store.push(value);
    appendVariable(name, var_store.top());
  }

  std::stack<double> var_store;
};

PYBIND11_MODULE(InfixParser, m){

  // Select specific member function

  double (py_Parser::*e)(mp_RPN) = &py_Parser::eval;
  e = nullptr;
  e = &py_Parser::eval;


  // Construct Python Classes & Functions

  py::class_<mp_RPN>(m, "mp_RPN")
    .def_readwrite("RPN", &mp_RPN::RPN)
    .def_readwrite("RPN_values", &mp_RPN::RPNValues);

  m.def("evaluate", &evaluate);

  py::class_<py_Parser>(m, "Parser")
    .def(py::init())
    .def("append_variable", &py_Parser::_appendVariable)
    .def("delete_variable", &py_Parser::deleteVariable)
    .def("reverse_polish_notation", &py_Parser::reversePolishNotation, py::arg("infix"), py::arg("_do_cache") = false)
    .def("eval", e);
}
