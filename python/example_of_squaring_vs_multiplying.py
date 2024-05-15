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
#       Provides a benchmark of multiplying vs. squaring in Python.            #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       2024/05/15                                                     #
################################################################################
"""
import time

# C-Python does not optimize exponentiation by constants very well.
# Something like y = x*x and y = x**2 should, with optimizations, yield
# identical performances. This scripts shows that this is not the case.
NUMBER_OF_RUNS = 10000000
X_LIST = [float(k) for k in range(NUMBER_OF_RUNS)]
Y_LIST = [0.0] * NUMBER_OF_RUNS

def square():
    """
        Computes y = x^2 by using the exponentiation operator.
    """

    # Get the starting time.
    start = time.time()

    # Loop through many times to get a good average for the computation.
    for ind in range(NUMBER_OF_RUNS):
        x_val = X_LIST[ind]
        Y_LIST[ind] = x_val ** 2

    # Get the ending time.
    end = time.time()

    # Return how long the computation took.
    return end - start

def square_float():
    """
        Computes y = x^2 by using the exponentiation operator with a float.
    """

    # Get the starting time.
    start = time.time()

    # Loop through many times to get a good average for the computation.
    for ind in range(NUMBER_OF_RUNS):
        x_val = X_LIST[ind]
        Y_LIST[ind] = x_val ** 2.0

    # Get the ending time.
    end = time.time()

    # Return how long the computation took.
    return end - start

def multiply():
    """
        Computes y = x^2 by using multiplication.
    """

    # Get the starting time.
    start = time.time()

    # Loop through many times to get a good average for the computation.
    for ind in range(NUMBER_OF_RUNS):
        x_val = X_LIST[ind]
        Y_LIST[ind] = x_val * x_val

    # Get the ending time.
    end = time.time()

    # Return how long the computation took.
    return end - start

print(square()) # 0.7492341995239258
print(square_float()) # 0.6064016819000244
print(multiply()) # 0.42986035346984863

# Based on these numbers, my guess is Python converts the exponent to a
# float and then calls the (real-valued) power function. This would explain why
# square is slower than square_float, since square_float doesn't need a cast,
# and why both are significantly slower than multiplying.

# Using PyPy (a JIT compiler for Python), we get identical times.
#   print(square(INPUT_VALUE)) # 0.012137889862060547
#   print(square_float(INPUT_VALUE)) # 0.01208186149597168
#   print(multiply(INPUT_VALUE)) # 0.011777162551879883

# The ratios for the times are:
#   square: 61.72689059123944
#   square_float: 50.191080414405526
#   multiply: 36.49948377431828
