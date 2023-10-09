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
 *  along with thie file.  If not, see <https://www.gnu.org/licenses/>.       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Time test C vs Fortran with something simple. Computes sin(x) for a   *
 *      large set of real numbers at double precision.                        *
 ******************************************************************************/

/*  Trigonometric functions found here.                                       */
#include <math.h>

/*  Input/Output functions found here. printf in particular.                  */
#include <stdio.h>

/*  size_t typedef is provided here.                                          */
#include <stddef.h>

/*  Computes sin(x) for a large set of numbers.                               */
int main(void)
{
    /*  Number of elements looped over. Use a large number to get a good      *
     *  average for the performance.                                          */
    const size_t array_size = (size_t)(1E8);

    /*  Index for looping over the points in the data set.                    */
    size_t n;

    /*  Step size between sample points.                                      */
    const double dx = 1.0E-6;

    /*  Variable for looping between the sample points.                       */
    double x = 0.0;

    /*  Variable for storing sin(x) as x varies.                              */
    double y;

    /*  Variable for computing the max of |sin(x)| as x varies. This is used  *
     *  to prevent the compiler from optimizing out the entire for-loop.      */
    double max = 0.0;

    /*  Loop over the points and run the computation.                         */
    for (n = 0; n < array_size; ++n)
    {
        y = fabs(sin(x));

        /*  Update the max of |sin(x)|, if needed.                            */
        if (max < y)
            max = y;

        /*  Update the point to the next sample.                              */
        x += dx;
    }

    /*  Avoid the compiler optimizing out everything, print the max.          */
    printf("%.18f\n", max);
}
/*  End of main.                                                              */
