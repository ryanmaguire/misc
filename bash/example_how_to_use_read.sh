#!/bin/bash
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
#       Example of using "read" in a shell script.                             #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       2024/04/29                                                     #
################################################################################
echo 'What is 2+2?'
read VAR
if [ "$VAR" = "4" ]; then
        echo 'Correct!'
else
        echo 'Well, you tried!'
fi
