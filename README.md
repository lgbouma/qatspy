This is a wrapper for the Quasiperiodic Automated Transit Search (QATS)
algorithm.

If you use the code, please cite [Carter & Agol (2012)](https://arxiv.org/abs/1210.5136) and 
[Kel'manov and Jeon (2004)](http://ieeexplore.ieee.org/document/1268358/).

[Pim Schellart](https://github.com/pschella) showed me how to implement the
wrapper in pybind11.

## Contents

  * `demo_qatspy.py`: run a demo on Kepler 36 data.

  * `README.txt`: Joshua Carter's readme to his C++ implementation of the
    algorithm, available at
  [Eric Agol's website](http://faculty.washington.edu/agol/QATS/).

  * `qats.h`: detailed function descriptions.

  * `carter_agol_2012_fig7_reproduce.py` reproduce the top panel of Figure 7 of
    Carter & Agol (2012).

  * `carter_agol_2012_river_reproduce.py` reproduce a river plot from the
    bottom panels of Figure 7, Carter & Agol (2012).

## Install

after cloning the repo,
```bash
python setup.py install --user
```
for instance in your favorite venv, which will let you access the library
anywhere.

Then you should be able to run `demo_qatspy.py`. The shell output should be:
```bash
S_best: 127.4420, M_best: 55
[  110   904  1699  2494  3290  4085  4880  5676  6470  7265  8059  8853
  9647 10441 11235 12029 12823 13617 14411 15205 15999 16793 17587 18381
 19175 19969 20763 21557 22351 23146 23941 24736 25532 26327 27122 27917
 28713 29507 30302 31096 31890 32684 33478 34272 35066 35860 36654 37448
 38242 39036 39830 40624 41418 42212 43006]
```

## Warnings

Following the notes from Sec 3.3 of Carter & Agol (2012), this algorithm
assumes uniformly spaced data. Missing points should be filled in with zeros.

## License

The license for the Python files and `qatspy.cpp` is the MIT License.
`qats.cpp` and `qats.h` are written by J. Carter and provided by E. Agol; it
appears to be re-distributable, but please make sure to cite Carter & Agol
(2012) and Kel'manov and Jeon (2004) if you use this implementation.
