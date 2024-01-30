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
 *      Computes the square root of a number using Heron's method.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 19, 2024                                              *
 ******************************************************************************/
#include <stdio.h>

static double do_sqrt(double x)
{
    unsigned int n;
    double y = 1.0;

    /*  Repeatedly apply Heron's method. The convergence is quadratic.        */
    for (n = 0U; n < 10U; ++n)
        y = 0.5 * (y + x / y);

    return y;
}

/*  Function for testing Heron's method. Compute sqrt(2) and compare.         */
int main(void)
{
    const double ans = 1.414213562373095048801688724209698078570;
    const double sqrt2 = do_sqrt(2.0);
    const double err = (sqrt2 - ans) / ans;
    printf("%e\n", err);
    return 0;
}
