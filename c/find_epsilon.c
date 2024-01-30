/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is free software: you can redistribute it and/or modify         *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  This file is distributed in the hope that it will be useful,              *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with this file.  If not, see <https://www.gnu.org/licenses/>.       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Finds machine epsilon for double precision numbers.                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 19, 2024                                              *
 ******************************************************************************/
#include <stdio.h>

int main(void)
{
    const double x = 1.0;
    double dx = 0.5;
    double y = x + dx;

    /*  Machine epsilon is the smallest positive value dx such that 1 = 1 +dx.*
     *  For an IEEE-754 64-bit double this is 2^-52 ~= 2.22 x 10^-16.         */
    while (x != y)
    {
        dx = 0.5 * dx;
        y = x + dx;
    }

    printf("%e\n", 2.0 * dx);
    return 0;
}
