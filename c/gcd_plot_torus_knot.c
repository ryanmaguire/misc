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
 *      Colors points (m, n) in the plane black or white depending on the     *
 *      value of GCD(m, n). This is modified from the previous version to     *
 *      show which pairs of integers represent torus knots.                   *
 ******************************************************************************/

/*  Needed for creating the PPM file.                                         */
#include <stdio.h>

/*  Maximum degree of the Jones polynomial we'll consider for torus knots.    */
static const unsigned int max_degree = 77U;

/*  Simple routine for computing the GCD of non-negative numbers. This is the *
 *  "by-hand" method and is dreadfully slow, much slower than the binary GCD  *
 *  method. The benefit is that it is fairly straight-forward to implement.   */
static unsigned int GCD(unsigned int n0, unsigned int n1)
{
    /*  Special case. The while loop can be infinite if one of the entries is *
     *  zero. GCD(n, 0) = n, so use this.                                     */
    if (n0 == 0U)
        return n1;
    else if (n1 == 0U)
        return n0;

    /*  Otherwise, run through the reduction step iteratively.                */
    while(n0 != n1)
    {
        if(n0 > n1)
            n0 -= n1;
        else
            n1 -= n0;
    }

    return n0;
}
/*  End of GCD.                                                               */

/*  Function for computing the "area" of the blocks with GCD(x, y) = 1. This  *
 *  simply sums over the square [0, N] x [0, N] for which entries have GCD 1, *
 *  and then divides by N^2.                                                  *
 *                                                                            *
 *  It occurred to me after writing this that the limit is the reciprocal of  *
 *  the solution to the famous Basel problem, 6 / pi^2. This is the           *
 *  "probability" that two non-negative integers are co-prime.                */
static double test(unsigned int N)
{
    /*  Declare necessary variables.                                          */
    unsigned int x, y;
    unsigned long counter = 0UL;

    /*  Loop over all points in the grid [0, N] x [0, N].                     */
    for (x = 0U; x < N; ++x)
        for (y = 0U; y < N; ++y)

            /*  We're counting coprime pairs, which means GCD(x, y) = 1.      */
            if (GCD(x, y) == 1U)
                ++counter;

    /*  The probability is the number of coprime pairs divided by the total,  *
     *  which is N^2. Return this.                                            */
    return (double)counter / (double)(N*N);
}
/*  End of "test" function.                                                   */

/*  Computes the degree of the jones polynomial of the T_{p, q} torus knot.   */
static unsigned int deg(unsigned int m, unsigned int n)
{
	const unsigned int a = (m - 1) * (n - 1) / 2;
	const unsigned int b = n + 1;
	const unsigned int c = m + 1;
	const unsigned int d = m + n;
	return a + b + c + d;
}

/*  Checks if an ordered pair of integers represents a torus knot.            */
static unsigned int torus_condition(unsigned int x, unsigned int y)
{
    /*  The pair must be coprime to represent a torus knot.                   */
    if (GCD(x, y) != 1)
        return 0U;

    /*  T_{p, q} and T_{q, p} are equivalent knots. We only plot if the first *
     *  entry has a smaller value than the second.                            */
    if (x > y)
        return 0U;

    /*  For large integers the Jones polynomial will have large degree and we *
     *  can skip these for our plot.                                          */
    if (deg(x, y) > max_degree)
        return 0U;

    /*  T_{1, p} is always a torus knot. Skip this.                           */
    if (x <= 1U)
        return 0U;

    /*  Everything passed, we can plot this point.                            */
    return 1U;
}

/*  Function for plotting GCD grid. White for GCD(x, y) = 1, black otherwise. */
int main(void)
{
    /*  Declare all necessary variables.                                      */
    const unsigned int plot_size = 1024U;
    const unsigned int file_size = 100U;

    /*  I only want to draw the block [0, 78] x [0, 78], but a 78x78 PGM file *
     *  will be really-really small and zooming in makes it blurry. Use this  *
     *  scale factor to draw the [0, 63] x [0, 63] region in a 1024x1024 PGM. */
    const double scale = (double)(max_degree + 1U) / (double)plot_size;

    /*  In a PGM file, black is zero and white is 255. Save these values.     */
    const unsigned char black = 0x00U;
    const unsigned char gray = 0xAFU;

    /*  Variables for indexing and looping over the lattice.                  */
    unsigned int n, x, y, z_x, z_y;

    /*  And variables for writing to files.                                   */
    FILE *fp, *ftxt;

    /*  Open the PGM file using fopen and give write permissions.             */
    fp = fopen("gcd_plot.pgm", "w");

    /*  If fopen fails it returns NULL. Check that this didn't happen.        */
    if (!fp)
    {
        puts("fopen failed and returned NULL for PGM file. Returning.");
        return -1;
    }

    /*  Print the preamble to the PGM file.                                   */
    fprintf(fp, "P5\n%u %u\n255\n", plot_size, plot_size);

    /*  Loop through each pixel.                                              */
    for (y = 0U; y < plot_size; ++y)
    {
        /*  PGMs plot top-to-bottom, whereas mathematicians think in a        *
         *  bottom-to-top style. Plot with the z_y variable to fix this.      */
        z_y = (unsigned int)(scale*(plot_size - y));

        /*  Loop over every x pixel as well.                                  */
        for (x = 0U; x < plot_size; ++x)
        {
            z_x = (unsigned int)(scale*x);

            /*  If we have a torus knot pair, plot it.                        */
            if (torus_condition(z_x, z_y))
                fputc(gray, fp);
            else
                fputc(black, fp);
        }
        /*  End of for-loop for the pixels x-coordinate.                      */
    }
    /*  End of for-loop for the pixels y-coordinate.                          */

    /*  Close the file.                                                       */
    fclose(fp);

    /*  We'll write the output to a text file so we can make neater plots     *
     *  using either GNU plotutils or matplotlib in Python.                   */
    ftxt = fopen("gcd_test.txt", "w");

    /*  Check that fopen didn't fail.                                         */
    if (!ftxt)
    {
        puts("fopen failed and returned NULL for text file. Returning.");
        return -1;
    }

    /*  Compute the values for the table.                                     */
    for (n = 0U; n < file_size; ++n)
        fprintf(ftxt, "%.16f\n", test(n));

    /*  Close the file.                                                       */
    fclose(ftxt);
    return 0;
}
/*  End of main.                                                              */
