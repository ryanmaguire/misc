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
#       Script for checking all compile options with libtmpl.                  #
################################################################################
COMPILER_LIST="gcc"

if command -v clang &> /dev/null; then
    COMPILER_LIST="$COMPILER_LIST clang"
fi

if command -v tcc &> /dev/null; then
    COMPILER_LIST="$COMPILER_LIST tcc"
fi

if command -v pcc &> /dev/null; then
    COMPILER_LIST="$COMPILER_LIST pcc"
fi

# Loop through compilers.
for comp in $COMPILER_LIST; do

    # Loop through STD versions.
    for ver in "c89" "c99" "c11" "c18"; do

        # Loop through IEEE vs non-IEEE modes of libtmpl.
        for ieee in "" "-noieee"; do

            # Loop through inline vs non-inline modes of libtmpl.
            for inl in "" "-inline"; do

                # C89 does not have inline. Skip this combination.
                if [[ $ver == c89 && $inl == -inline ]]; then
                    continue
                fi

                # libtmpl math algorithms vs. using libm directly.
                for math in "" "-nomath"; do

                    # C89 does not have the C99 math functions. Skip this.
                    if [[ $ver == c89 && $math == -nomath ]]; then
                        continue
                    fi

                    # Fixed-width integers vs. no-fixed-width integers.
                    for int in "" "-noint"; do

                        # Whether or not to compile with long-long support.
                        for ll in "" "-longlong"; do

                            # C89 does not have long long. Skip this.
                            if [[ $ver == c89 && $ll == -longlong ]]; then
                                continue
                            fi

                            # Build the "monster" libtmpl or not. Monster mode
                            # #include's every source file into one c file and
                            # compiles that.
                            for mon in "" "-monster"; do
                                rstring=${comp}_${ver}_${ieee}_${inl}_${math}
                                rstring=${rstring}_${int}_${ll}_${mon}
                                results=results_${rstring}.txt
                                touch $results
                                CC="-cc=$comp"
                                STD="-std=$ver"
                                ARGS="$CC $STD $inl $math $ll $mon $ieee"
                                bash make.sh $ARGS >> $results
                            done
                        done
                    done
                done
            done
        done
    done
done
