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
#       Fixes apt when its broken for many common problems.                    #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       2026/02/15                                                     #
################################################################################
rename_pascal_with_date_to_snake_case() {

    input="$1"

    if [[ ! -e "$input" ]]; then
        echo "Error: File '$input' does not exist."
        return 1
    fi

    dir=$(dirname "$input")
    base=$(basename "$input")

    # Extract date part (first 8 chars) and the rest
    date="${base:0:8}"
    obj="${base:8}"

    # Format date: YYYYMMDD -> yyyy_mm_dd
    formatted_date=$(echo "$date" | sed -E 's/(....)(..)(..)/\1_\2_\3/')

    # Convert object part to snake_case.
    formatted_object=$(echo "$obj" | sed -E 's/([A-Z])/_\L\1/g' | sed 's/^_//')

    output="${formatted_date}_${formatted_object}"

    read -r -p "Before: $input After: $output Rename file? (y/n) " ans

    if [[ "$ans" == "y" || "$ans" == "Y" ]]; then
        mv -- "$input" "$output"
    fi
}
