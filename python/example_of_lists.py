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
#       Provides an example of using lists in Python.                          #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       2024/05/15                                                     #
################################################################################
"""

MY_LIST = []
MY_LIST.append(1)
MY_LIST.append(2)
MY_LIST.append(3)
print(MY_LIST[0]) # prints 1
print(MY_LIST[1]) # prints 2
print(MY_LIST[2]) # prints 3

# prints out 1,2,3
for KEY in MY_LIST:
    print(KEY)

# Out of bounds error.
#       mylist = [1, 2, 3]
#       print(mylist[10])
