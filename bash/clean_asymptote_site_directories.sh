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
#       Old script for cleaning out the asymptote directories.                 #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       2023/10/09                                                     #
################################################################################
cd asymptote/

for folder in */ ; do

    # Check that the folder exists.
    if [ -d "$folder" ]; then

        # If the folder exists, clean it out.
        echo "Cleaning $folder"

        # Check that the folder is not empty.
        if [ "$(ls -A $folder)" ]; then
            mv $folder* ./

            # Clear out older files while keeping the .asy one.
            rm -f Makefile
            rm -f README.md
            rm -f *.png
            rm -f *.svg
            rm -f *.pdf
            rm -f .DS_Store
            rm -f $folder/.DS_Store

            # Check that the above line worked and the folder is emtpty.
            if [ "$(ls -A $folder)" ]; then

                # Folder is not empty, aborting.
                echo "$folder is not empty, stopping!"
                exit 1
            else
                # Folder is empty, so kill it.
                rm -rf "$folder"
            fi
        else
            # Folder is empty, remove it.
            rm -rf "$folder"
        fi
    else
        # Folder does not exist, move on to the next one.
        continue
    fi
done

echo -e "\nDone cleaning\n"
