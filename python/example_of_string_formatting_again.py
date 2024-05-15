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
#       Provides an example of string formatting in Python.                    #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       2024/05/15                                                     #
################################################################################
"""

# Pylint will complain that we are not using "f-strings." Disable this warning.
#   pylint: disable = C0209

# This prints out "Hello, Bob!"
NAME = "Bob"
print("Hello, %s!" % NAME)

# This prints out "Bob is 25 years old."
NAME = "Bob"
AGE = 25
print("%s is %d years old." % (NAME, AGE))

# This prints out: A list: [1, 2, 3]
MY_LIST = [1, 2, 3]
print("This is my list: %s" % MY_LIST)
