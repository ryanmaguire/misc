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
#       Provides an example of creating and using functions.                   #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       2024/05/15                                                     #
################################################################################
"""

# Functions are created using 'def'.
def my_function():
    """
        This is the 'doc-string' of the function. It tells the user what
        it does. In a python shell typing "help(my_function)" will print this
        message out for the user.
    """
    print("Hello From My Function!")

def my_function_with_args(name, greeting):
    """
        Function:
            my_function_with_args
        Purpose:
            Prints a greeting to a person.
        Arguments:
            name (str):
                The name of the person.
            greeting (str):
                The message given to the person.
        Output:
            None.
    """
    print("Hello, " + name + "! I wish you " + greeting)

def sum_two_numbers(left_number, right_number):
    """
        Function:
            sum_two_numbers
        Purpose:
            Sums two integers together.
        Arguments:
            left_number (int):
                An arbitrary integer.
            right_number (int):
                Another arbitrary integer.
        Output:
            sum (int):
                The sum of left_number and right_number.
    """
    return left_number + right_number

# Lets test our functions. Compute the sum of 1 and 2.
SUM_OF_ONE_AND_TWO = sum_two_numbers(1, 2)

# Call the first function which takes no arguments.
my_function()

# Call the second function which needs two arguments.
my_function_with_args("John Doe", "a great year!")

# Print the result of our summation function.
print(SUM_OF_ONE_AND_TWO)
