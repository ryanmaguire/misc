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
#       Provides an example of the syntax for a class in Python.               #
################################################################################
"""

class MyClass:
    """
        This is the 'doc-string' for a class.
        It tells the reader its purpose, and may include information about
        the attributes (variables) and methods (functions) associated to the
        class.
    """

    def __init__(self, var = "blah"):
        """
            This function initializes all of the variables in a class.
            It is optional. If your class doesn't needed any user-specified
            arguments, you do not need an __init__ function. This function
            is called when you write my_object = MyClass().
        """

        # One of the later functions treats "variable" as a string. Ensure the
        # user provided us with a string.
        if not isinstance(var, str):
            raise TypeError("Your variable must be a string.")

        # We have a string, set the class variable, or "attribute", to var.
        self.variable = var

    def function(self):
        """
            This is a 'method', a function inside the class.
            If you have an instance my_class of MyClass, you can access this
            method via my_class.function().
        """
        print("Message inside a class.")

    def what_is_my_variable(self):
        """
            Methods can also access the variables of the class.
        """
        print("Your variable is " + self.variable)

my_object_x = MyClass()
my_object_y = MyClass("blargh")

# Test use for the method inside the class.
my_object_x.function()

# Then print out both values
my_object_x.what_is_my_variable()
my_object_y.what_is_my_variable()

# You can change values as well.
my_object_y.variable = "yippy!"
my_object_y.what_is_my_variable()
