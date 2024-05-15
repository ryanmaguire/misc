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
#       Provides an example of using lists and conditionals in Python.         #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       2024/05/15                                                     #
################################################################################
"""

NAME, NUMBER = 'Bob Guy', 42
print(NAME + str(NUMBER))

X_OBJECT, Y_OBJECT = object(), object()
X_LIST = [X_OBJECT] * 10
Y_LIST = [Y_OBJECT] * 10
BIG_LIST = X_LIST + Y_LIST
X_LEN, Y_LEN = len(X_LIST), len(Y_LIST)
BIG_LEN = len(BIG_LIST)

print("X_LIST: " + str(X_LEN) + " objects")
print("Y_LIST: " + str(Y_LEN) + " objects")
print("BIG_LIST: " + str(BIG_LEN) + " objects")

if X_LIST.count(X_OBJECT) == 10:
    print("Almost there...")

if Y_LIST.count(Y_OBJECT) == 10:
    print("Almost there...")

if BIG_LIST.count(X_OBJECT) == 10:
    print("Nearly done...")

if BIG_LIST.count(Y_OBJECT) == 10:
    print("Great!")
