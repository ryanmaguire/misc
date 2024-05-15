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
#       Provides an example of using conditionals in Python.                   #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       2024/05/15                                                     #
################################################################################
"""

X_VALUE = 2
print(X_VALUE == 2) # prints out True
print(X_VALUE == 3) # prints out False
print(X_VALUE < 3) # prints out True

NAME = "John"
AGE = 42

if NAME == "John" and AGE == 42:
    print("You're John and you are 42")

if NAME == "John" or AGE == 42:
    print("You're either John or are 42")

if NAME in ["John", "Bob"]:
    print("You're either John or Bob")
