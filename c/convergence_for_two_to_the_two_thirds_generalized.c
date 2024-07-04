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
 *      Given the point (x, y) in the upper right quadrant, computes the      *
 *      limit of x_{n+2} = sqrt(x_{n} x_{n+1}) with x_{0} = x, x_{1} = y. A   *
 *      PGM plot as made from this as well.                                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 2, 2024                                                  *
 ******************************************************************************/

/*  FILE data type, fprintf, and fputs are all found here.                    */
#include <stdio.h>

/*  The square root function is given here.                                   */
#include <math.h>

/*  Maximum number of iterations allowed for x_{n+2} = sqrt(x_{n} x_{n+1}).   */
static const unsigned int max_iters = 64U;

/*  Error tolerance for convergence of the sequence x_{n}.                    */
static const double eps = 1.0E-14;

/*  Computes x_{n+2} = sqrt(x_{n} x_{n+1}).                                   */
static double func(double x0, double x1)
{
    /*  Variable for indexing.                                                */
    unsigned int n;

    /*  Keep computing until we converge or do too many iterations.           */
    for (n = 0U; n < max_iters; ++n)
    {
        const double tmp = x1;
        x1 = sqrt(x1 * x0);
        x0 = tmp;

        /*  Check for convergence.                                            */
        if (fabs(x1 - x0) < eps)
            break;
    }

    return x1;
}

/*  Gets a gray scale color from a positive real number.                      */
static int get_color(double x)
{
    /*  In the square [0, 16^2] the function is bounded by 16. The maximum    *
     *  value for a gray scale color is 255. Use this to normalize.           */
    const double scale_factor = 255.0 / 16.0;
    const double input = x * scale_factor;

    /*  Avoid overflow. Return the maximum gray scale for large inputs.       */
    if (input > 255.0)
        return 255;

    /*  Change "0" to "1" if you want to see the pre-image of "8" in the      *
     *  plane. It will be displayed as a black curve.                         */
#if 0
    if (7.97 < x && x < 8.03)
        return 0;
#endif

    /*  Otherwise, cast the input to an int for our gray scale value.         */
    return (int)input;
}

/*  Writes a gray scale color to a PGM file.                                  */
void write_color(FILE *fp, double x)
{
    const unsigned int val = get_color(x);
    fputc(val, fp);
}

/*  Plots the limit of x_{n+2} = sqrt(x_{n} x_{n+1}) with x_{0} = x, and      *
 *  x_{1} = y with (x, y) varying over the square [0, 16]^2.                  */
int main(void)
{
    /*  Number of pixels in the x and y axes.                                 */
    const unsigned int x_size = 1024U;
    const unsigned int y_size = 1024U;

    /*  The square we're sampling, [0, 16]^2.                                 */
    const double x_min = 0.0;
    const double x_max = 16.0;
    const double y_min = 0.0;
    const double y_max = 16.0;

    /*  Variable for the output of the function.                              */
    double val;

    /*  Open the PGM file and give it write permissions.                      */
    FILE * const fp = fopen("almost_fibonacci.pgm", "w");

    /*  Variables for looping over the pixels.                                */
    unsigned int x, y;

    /*  Variables for the points in the plane corresponding to pixels.        */
    double x_val, y_val;

    /*  Conversion factors for going from pixels to points.                   */
    const double x_factor = (x_max - x_min) / (double)x_size;
    const double y_factor = (y_max - y_min) / (double)y_size;

    /*  Write the preamble of the PGM file.                                   */
    fputs("P5\n1024 1024\n255\n", fp);

    /*  Loop through the y components of the PGM file.                        */
    for (y = 0U; y < y_size; ++y)
    {
        /*  Convert the y-coordinate of the pixel to the plane coordinate.    */
        y_val = y_max - y_factor * (double)y;

        /*  Loop through the x components of the PGM file.                    */
        for (x = 0U; x < x_size; ++x)
        {
            /*  Get the x-coordinate in the plane for this pixel.             */
            x_val = x_min + x_factor * (double)x;

            /*  Compute the function and plot it to the PGM file.             */
            val = func(x_val, y_val);
            write_color(fp, val);
        }
    }

    /*  All done with the picture, we can close the file.                     */
    fclose(fp);
    return 0;
}
