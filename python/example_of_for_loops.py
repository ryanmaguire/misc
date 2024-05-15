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
#       Provides an example of using for loops.                                #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       2024/05/15                                                     #
################################################################################
"""

# Prints out the numbers 0, 1, 2, 3, 4
for INDEX in range(5):
    print(INDEX)

# Prints out 3, 4, 5
for INDEX in range(3, 6):
    print(INDEX)

# Prints out 3, 5, 7
for INDEX in range(3, 8, 2):
    print(INDEX)

# Prints out 0, 1, 2, 3, 4
COUNT = 0

while COUNT < 5:
    print(COUNT)
    COUNT += 1
