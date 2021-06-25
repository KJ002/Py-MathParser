#include <pybind11/cast.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "MathParser/include/parser.hpp"

namespace py = pybind11;

class py_Evaluator : public MathEvaluator{
public:

  void _appendVariable(const std::string name, const double value){
    double* heap_var = new double(value);
    appendVariable(name, *heap_var);
  }

  void _deleteVariable(const std::string name){
    delete getExternalVariables()[name];
    deleteVariable(name);
  }
};

PYBIND11_MODULE(InfixParser, m){

  // Construct Python Classes & Functions

  py::class_<mp_RPN>(m, "mp_RPN")
    .def_readwrite("RPN", &mp_RPN::RPN)
    .def_readwrite("RPN_values", &mp_RPN::RPNValues);

  m.def("evaluate", &evaluate);

  py::class_<py_Evaluator>(m, "Evaluator")
    .def(py::init())
    .def("append_variable", &py_Parser::_appendVariable)
    .def("delete_variable", &py_Parser::_deleteVariable)
    .def("variables", &py_Parser::getExternalVariables)
    .def("eval", &py_Parser::eval);
}
