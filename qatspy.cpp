#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <qats.h>

namespace py=pybind11;

py::array_t<double> shConvol_wrapper(py::array_t<double> y, int q) {

  auto buf_y = y.request();
  int N = buf_y.size;

  // qats.cpp's shConvol function takes double *&d as the fourth argument.
  // First we allocate the array, then cast to doubles.
  auto d = py::array_t<double>(N - q + 1);
  auto buf_d = d.request();
  auto d_p = static_cast<double*>(buf_d.ptr);

  shConvol(static_cast<double *>(buf_y.ptr),
      N,
      q,
      d_p);

  return d;
}


std::pair<double,int> qats_wrapper( py::array_t<double> d, int DeltaMin, int
    DeltaMax, int N, int q) {

  auto buf_d = d.request();

  double S_best;
  int M_best;

  qats(static_cast<double *>(buf_d.ptr),
      DeltaMin,
      DeltaMax,
      N,
      q,
      S_best,
      M_best);

  std::pair<double,int> result;
  result.first = S_best;
  result.second = M_best;

  return result;
}


py::array_t<int> qats_indices_wrapper(py::array_t<double> d, int M, int
    DeltaMin, int DeltaMax, int N, int q) {

  double S_best;
  auto buf_d = d.request();

  auto indices = py::array_t<int>(M);
  auto buf_indices = indices.request();
  auto indices_p = static_cast<int*>(buf_indices.ptr);

  qats_indices(static_cast<double *>(buf_d.ptr),
        M,
        DeltaMin,
        DeltaMax,
        N,
        q,
        S_best,
        indices_p);

  return indices;
}


PYBIND11_PLUGIN(qatspy) {

  py::module m("qatspy");

  m.def("shConvol_wrapper", shConvol_wrapper);
  m.def("qats_wrapper", qats_wrapper);
  m.def("qats_indices_wrapper", qats_indices_wrapper);

  return m.ptr();
}
