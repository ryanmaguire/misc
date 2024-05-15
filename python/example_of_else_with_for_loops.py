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
#       Provides an example of else and for / while loops.                     #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       2024/05/15                                                     #
################################################################################
"""

COUNT = 0

# Prints out 1, 2, 3, 4
while COUNT < 5:
    print(COUNT)
    COUNT += 1

    if COUNT == 6:
        break

# If the while loop ends and the break did not trigger, this code is executed.
else:
    print("value: " + str(COUNT))

for INDEX in range(1, 10):

    if INDEX % 5 == 0:
        break

    print(INDEX)

# The break will happen before the for loop ends. This code is not used.
else:
    print("this is not printed")
