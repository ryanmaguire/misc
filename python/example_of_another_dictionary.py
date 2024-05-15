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
#       Provides an example of the syntax for a dictionary in Python.          #
################################################################################
"""

# Create a dictionary, just like before.
phonebook = {
    "John": 1234,
    "Jack": 2345,
    "Jill": 3456
}

# You can easily iterate over the keys of a dictionary.
for name, number in phonebook.items():
    print("Phone number of " + name + " is " + str(number))
