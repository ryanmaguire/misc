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
#       Provides an example of using the Numpy C-API and setup tools.          #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       2024/05/15                                                     #
################################################################################
"""

# pylint will complain about these imports not being valid. They indeed are.
# Disable these to avoid incorrect pylint errors.
#     pylint: disable = E0401
#     pylint: disable = E0611
from numpy.distutils.misc_util import Configuration
from numpy.distutils.core import setup

# Function for generating the extension module.
def configuration(parent_package = '', top_path = None):
    """
        Configures the extension module. This will result in the
        C code being compiled and ready to use at the Python level.
    """

    config = Configuration(
        'mymodule',
        parent_package,
        top_path
    )

    config.add_extension('mymodule', ['example_of_numpy_c_api.c'])
    return config

# Create the extension module.
if __name__ == "__main__":
    setup(configuration = configuration)
