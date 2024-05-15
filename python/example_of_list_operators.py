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
#       Provides an example of using list operators in Python.                 #
################################################################################
"""

# Create two lists.
EVEN_NUMS = [2, 4, 6, 8]
ODD_NUMS = [1, 3, 5, 7]

# This concatenates lists, it does not add their elements.
ALL_NUMS = ODD_NUMS + EVEN_NUMS
print(ALL_NUMS)

# This concatenates the list with itself three times.
TRIPLE_LIST = [1, 2, 3] * 3
print(TRIPLE_LIST)
