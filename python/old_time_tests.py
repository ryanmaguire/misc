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
#       Silly time tests to see how efficient certain things are in Python.    #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       2017                                                           #
################################################################################
"""
import time

NUMBER_OF_ITERATIONS = 1000000

def func1(x_val):
    """
        Computes y = x.
    """
    start = time.time()

    for _ in range(NUMBER_OF_ITERATIONS):
        _ = x_val

    end = time.time()
    print(end - start)

def func2(x_val):
    """
        Computes y = x, followed by y *= 1.
    """
    start = time.time()

    for _ in range(NUMBER_OF_ITERATIONS):
        _ = x_val
        x_val *= 1

    end = time.time()
    print(end - start)

def func3(x_val):
    """
        Computes y = x*1.
    """
    start = time.time()

    for _ in range(NUMBER_OF_ITERATIONS):
        _ = x_val * 1

    end = time.time()
    print(end - start)

def func4(ind, n_used, window_size, loop):
    """
        Prints a status update.
    """
    mes = "Pt: %d  Tot: %d  Width: %d  Psi Iters: %d  Fast Inversion"
    print(mes % (ind, n_used, window_size, loop), end="\r")

def func5(ind, n_used, window_size, loop):
    """
        A 'do nothing' function.
    """
    pass

def func6(x_val, y_val):
    """
        Function for comparing the efficiencies of func4 and func5.
    """
    start = time.time()

    if x_val:
        for ind in range(y_val):
            func4(ind, y_val, 3, 4)
    else:
        for ind in range(y_val):
            func5(ind, y_val, 3, 4)

    end = time.time()
    print(end - start)
