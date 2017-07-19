#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <qats.h>

namespace py=pybind11;

py::array_t<double> shConvol_wrapper(py::array_t<double> y, int q) {
  //
  // shConvol: convolves the data, y, comprised of N datum, with a box of unit
  // depth (or height -- see PARITY in qats.cpp) and returns the result of size
  // N-q+1 in d.
  //
  // inputs:	y - data
  //		N - size of y
  //		q - size of box
  // outputs:	d - convolved data of size N-q+1
  // pre:		d - is allocated with appropriate size
  //

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
  //
  // qats: determines the maximum metric Sbest over the set of transits instants
  // for minimum interval DeltaMin and maximum interval DeltaMax for transits of
  // duration (box-width) q by searching the box-convolved data d (of size N).
  // d may be computed with shConvol prior to this call (or by another
  // appropriate filter).
  //
  // inputs:	d - convolved data
  //		DeltaMin - minimum interval (in cadences)
  //		DeltaMax - maximum interval (in cadences)
  //		N - size of convolved data
  //		q - duration (width) of box signal
  // outputs:	Sbest - maximum of obj. function for optimal transit instants
  //		Mbest - number of transits in d corresponding to Sbest
  //

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
  //
  // qats_indices: determines the maximum metric Sbest over the set of transit
  // instants for minimum interval DeltaMin and maximum interval DeltaMax
  // for M transits of duration (box-width) q by searching the box-convolved
  // data d (of size N). d may be computed with shConvol prior to this call
  // (or by another appropriate filter). The indices of the best transit instants
  // are also returned.
  //
  // inputs:	d - convolved data
  //		M - number of transits
  //		DeltaMin - minimum interval (in cadences)
  //		DeltaMax - maximum interval (in cadences)
  //		N - size of convolved data
  //		q - duration (width) of box signal
  // outputs:	Sbest - maximum of obj. function for optimal transit instants
  //		indices - array of M optimal transit instants (cadence #)
  //

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
