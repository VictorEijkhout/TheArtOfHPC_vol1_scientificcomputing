#include <boost/python.hpp>

#include "hello.h"

BOOST_PYTHON_MODULE(hello_ext)
{
  using namespace boost::python;
  def("greet", greet);
}
