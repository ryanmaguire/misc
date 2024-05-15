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
#   Author:     Ryan Maguire                                                   #
#   Date:       2024/05/15                                                     #
################################################################################
"""

# A dictionary is like a simplified class. It has "attributes" in the form of
# keys. Here is the basic syntax.
phonebook = {}
phonebook["John"] = 7566
phonebook["Jack"] = 7264
phonebook["Jill"] = 2781

# This prints out the contents of the dictionary.
print(phonebook)

# You can create a dictionary all at once as follows.
phonebook1 = {
    "John" : 7566,
    "Jack" : 7264,
    "Jill" : 2781
}

# This will print the same thing.
print(phonebook1)
