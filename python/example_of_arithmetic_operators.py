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
#       Provides an example of using arithmetic operators in Python.           #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       2024/05/15                                                     #
################################################################################
"""

# We can use basic addition, multiplication, and division.
NUMBER = 1 + 2 * 3 / 4.0
print(NUMBER)

# This will turn an integer into a float.
NOT_INTEGER = 4 / 2
print(NOT_INTEGER)

# Use "true divide" to make the output an integer.
INTEGER = 4 // 2
print(INTEGER)

# We can also compute remainders, or "modulos". 11 = 3*3 + 2, so 11 mod 3 = 2.
REMAINDER = 11 % 3
print(REMAINDER)

# Exponentiation is allowed. It is not given by x ^ y, but instead x ** y.
SQUARED = 7 ** 2
print(SQUARED)

# We can use arbitrary numbers.
CUBED = 2 ** 3
print(CUBED)

# Fractional numbers as well.
ROOT = 2 ** 0.5
print(ROOT)
