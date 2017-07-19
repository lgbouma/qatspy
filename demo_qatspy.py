'''
Run the Carter & Agol (2012) QATS algorithm on Kepler 36.
See README.txt for more info.
Refer to `qats.h' for detailed function descriptions.
'''

import qatspy
import numpy as np

flux = np.genfromtxt('kep36.dat')

Δ_min = 794
Δ_max = 797
q = 14

d = qatspy.shConvol_wrapper(flux, q)
result = qatspy.qats_wrapper(d, Δ_min, Δ_max, int(len(flux)), q)

S_best, M_best = result[0], result[1]

print('S_best: {:.4f}, M_best: {:d}'.format(S_best, M_best))

#del d
d = qatspy.shConvol_wrapper(flux, q)
inds = qatspy.qats_indices_wrapper(d, M_best, Δ_min, Δ_max,
        int(len(flux)), q)

print(inds)
