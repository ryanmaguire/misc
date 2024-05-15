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
#       Provides an example of using multiple functions in Python.             #
################################################################################
"""

def list_benefits():
    """
        This is the function 'doc-string' telling the use about the function.
    """
    return "Organized code", "Readable code", "Code reuse", "Sharing code"

def build_sentence(benefit):
    """
        This function returns a string that starts with the input.
    """

    if not isinstance(benefit, str):
        raise TypeError("Input must be a string.")

    return benefit + " is a benefit!"

def name_the_benefits_of_functions():
    """
        This function concatenates a list of benefits for functions.
    """
    list_of_benefits = list_benefits()

    for benefit in list_of_benefits:
        print(build_sentence(benefit))

name_the_benefits_of_functions()
