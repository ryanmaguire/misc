#!/bin/sh
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
#      	Old script for generating animations I made in asymptote.              #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       2024/02/04                                                     #
################################################################################
export ASYMPTOTE_DIR=$(pwd)
for x in $(find asymptote/ -name *.asy -path "asymptote/animations/*"); do
    filename=$(basename $x .asy)
    echo "Processing: $x"
    asy $x;
    mv $filename.gif ./images/
done
