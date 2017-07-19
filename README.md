This is a wrapper for Carter & Agol's QATS algorithm (2012).

If you use the code, cite Carter & Agol (2012) **and** Kel'manov and Jeon
(2004).

[Pim Schellart](https://github.com/pschella) showed me how to implement the
wrapper in pybind11.

## Contents:

  * `demo_qatspy.py`: run a demo on Kepler 36 data.

  * `README.txt`: Joshua Carter's readme to his C++ implementation of the
    algorithm, available at
  [Eric Agol's website](http://faculty.washington.edu/agol/QATS/).

  * `qats.h`: detailed function descriptions.

## Install:

after cloning the repo,
```
python setup.py build_ext --inplace
```

Then you should be able to run `demo_qatspy.py`.

## TODO:
`qats_indices_wrapper`
