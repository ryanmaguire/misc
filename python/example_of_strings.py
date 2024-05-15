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
#       Provides an example of using strings in Python.                        #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       2024/05/15                                                     #
################################################################################
"""

# Single quotes are fine.
MY_STRING = 'Hello, World!'
print(MY_STRING)

# Double quotes also work.
MY_STRING = "Hello, World!"
print(MY_STRING)

# If your string has single quotes, use double quotes on the outside.
MY_STRING = "Ain't life grand?"
print(MY_STRING)

# You can do this the other way around, too.
MY_STRING = 'I think "Hello, World!" is an excellent greeting.'
print(MY_STRING)

# If you need both, use character escapes.
MY_STRING = 'Don\'t you think "Hello, World!" is a friendly greeting?'
print(MY_STRING)

# Both of these will cause a syntax error.
#   MY_STRING = 'Don't worry'
#   MY_STRING = "I think "Hello, World!" is a nice greeting."
