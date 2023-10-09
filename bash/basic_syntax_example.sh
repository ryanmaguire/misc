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
#       Old "Hello, World" example testing some Bash features.                 #
################################################################################
printf "\nHello, World!\nMy name is %s!\n" "$1"

if [ ! -d "$2" ]; then
    echo "Directory $2 Does Not Exist!"
    echo "Do You Want To Make It? [y/n]"
    read var
    if [ "$var" = "y" ]; then
        echo "You got it!"
        mkdir "$2"
    else
        echo "Alrighty then!"
        exit 1
    fi
else
    echo "$2 Exists! Don't Touch!"
    exit 1
fi
