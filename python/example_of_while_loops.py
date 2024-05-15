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
#       Provides an example of using for and while loops.                      #
################################################################################
"""

COUNT = 0

# "while True" creates an infinite loop.
while True:

    print(COUNT)
    COUNT += 1

    # This while loop will not end unless we have a break condition.
    if COUNT >= 5:
        break

# For loops use a different syntax.
for value in range(10):

    # Check if the value is even
    if value % 2 == 0:
        continue # Odd numbers only

    print(value)
