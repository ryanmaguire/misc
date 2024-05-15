"""
################################################################################
#                                   LICENSE                                    #
################################################################################
#   This file is free software: you can redistribute it and/or modify          #
#   it under the terms of the GNU General Public License as published by       #
#   the Free Software Foundation, either version 3 of the License, or          #
#   (at your option) any later version.                                        #
#                                                                              #
#   This file is distributed in the hope that it will be useful,               #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU General Public License for more details.                               #
#                                                                              #
#   You should have received a copy of the GNU General Public License          #
#   along with this file.  If not, see <https://www.gnu.org/licenses/>.        #
################################################################################
#   Purpose:                                                                   #
#       Provides an example of using ctypes, and showing some of the benefits  #
#       of compiler optimizations.                                             #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       2024/05/15                                                     #
################################################################################
"""
import ctypes
import time

# The number we'll sum up to.
NUMER_TO_SUM = 100000000

# Load the C function using ctypes.
adder = ctypes.cdll.LoadLibrary("./add.so")

# Perform the computation at the C level.
START = time.time()
C_VAL = adder.add(NUMER_TO_SUM)
END = time.time()

# Computation time for the C function.
C_TIME = END - START

# Perform the computation at the Python level.
START = time.time()
PY_VAL = 0

for _ in range(NUMER_TO_SUM):
    PY_VAL += 1

END = time.time()

# Computation time for the Python routine.
PY_TIME = END - START

# Print the results to the screen.
print("C Computation Time:      " + str(C_TIME))
print("Python Computation Time: " + str(PY_TIME))
print("Ratio of Times:          " + str(PY_TIME / C_TIME))
print("Results are the same?    " + str(PY_VAL == C_VAL))

# With optimizations on for add.c, this prints:
#   C Computation Time:      8.58306884765625e-06
#   Python Computation Time: 5.639729022979736
#   Ratio of Times:          657076.0555555555
#   Results are the same?    True

# With optimizations off for add.c, this prints:
#   C Computation Time:      0.15541434288024902
#   Python Computation Time: 5.160496711730957
#   Ratio of Times:          33.204764863351514
#   Results are the same?    True

# The unoptimized times are strikingly similar to PyPy's time. These are:
#   PyPy Computation Time: 0.18768835067749023
