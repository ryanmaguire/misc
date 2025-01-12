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
#   Author:     Ryan Maguire                                                   #
#   Date:       2025/01/12                                                     #
################################################################################
synctoserver() {

    # Check if we're doing a dry-run. "-n" is the option for this.
    if [[ $# -eq 1 ]]; then

        # This is a simple script, only allow "-n" as an option.
        if [[ "$1" == "-n" ]]; then
            ARGUMENTS="-navhx"

        # Everything else is treated as an invalid argument.
        else

            # Exit with an error message.
            echo "Invalid argument."
            echo "Pass -n for a dry-run, no argument for a standard run."
            return 0
        fi

    # We get here if no argument was given.
    else

        # Default arguments, standard run with rsync.
        ARGUMENTS="-avhx"
    fi

    # Sync the data to the server.
    rsync                                   \
        --exclude '.Trash*'                 \
        --exclude 'lost+found'              \
        -e 'ssh -p 40'                      \
        "$ARGUMENTS" --progress --delete    \
        user@192.168.0.x:/path/to/stuff/ /path/to/stuff/
}
