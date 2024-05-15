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
#       Provides a benchmark of multiplying vs. adding in Python.              #
################################################################################
"""
import time

# The primary implementation of Python, CPython, at the time of this writing,
# does not have several of the optimizations available to more traditional
# compiled languages that would make things like adding and multiplying by
# constants equal in terms of computational time. In a language like C or C++,
# or even Python with the JIT compiler PyPy, something like y = x + x and
# y = 2*x should be identical in speed. For the CPython interpreter this is
# not the case. This short script showcases this phenomenon.
NUMBER_OF_ITERS = 10000000
X_VALUE = 4.234

def mult(x_val):
    """
        Calculates y = 2*x. This is done many times to get a good benchmark.
    """
    start_time = time.time()

    for _ in range(NUMBER_OF_ITERS):
        _ = 2*x_val

    end_time = time.time()

    return end_time - start_time

def mult_float(x_val):
    """
        Calculates y = 2.0*x. This is done many times to get a good benchmark.
    """
    start_time = time.time()

    for _ in range(NUMBER_OF_ITERS):
        _ = 2.0*x_val

    end_time = time.time()

    return end_time - start_time

def add(x_val):
    """
        Calculates y = x + x. This is done many times to get a good benchmark.
    """
    start_time = time.time()

    for _ in range(NUMBER_OF_ITERS):
        _ = x_val + x_val

    end_time = time.time()

    return end_time - start_time

# We can see that x + x and 2.0*x are identical in speed, however 2*x is much
# slower. This is likely because of the CPython interpreter performing an
# implicit cast of int (2) to float (2.0) before performing the computation.
print(mult(X_VALUE)) # 0.26024651527404785 seconds.
print(mult_float(X_VALUE)) # 0.18248510360717773 seconds.
print(add(X_VALUE)) # 0.18433570861816406 seconds

# Using PyPy we get:
#   print(mult(X_VALUE)) # 0.0050959587097167970 seconds.
#   print(mult_float(X_VALUE)) # 0.0049915313720703125 seconds.
#   print(add(X_VALUE)) # 0.0052456855773925780 seconds
# About 35x faster, but also identical across the board.
