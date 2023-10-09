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
 *      value of GCD(m, n). Yields a surprising image. Uses libtmpl.          *
 ******************************************************************************/

/*  Needed for creating the PPM file.                                         */
#include <stdio.h>

/*  Binary GCD routine provided here.                                         */
#include <libtmpl/include/tmpl_integer.h>

/*  Function for plotting GCD grid. White for GCD(x, y) = 1, black otherwise. */
int main(void)
{
    /*  Declare all necessary variables.                                      */
    const unsigned int plot_size = 1024U;

    /*  I only want to draw the block [0, 63] x [0, 63], but a 64x64 PGM file *
     *  will be really-really small and zooming in makes it blurry. Use this  *
     *  scale factor to draw the [0, 63] x [0, 63] region in a 1024x1024 PGM. */
    const double scale = 64.0 / (double)plot_size;

    /*  In a PGM file, black is zero and white is 255. Save these values.     */
    const unsigned char black = 0x00U;
    const unsigned char white = 0xFFU;

    /*  Variables for indexing and looping over the lattice.                  */
    unsigned int x, y, z_x, z_y;

    /*  And a variable for writing to the PGM file.                           */
    FILE *fp;

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

            /*  If z_x and z_y are coprime, plot the pixel white.             */
            if (tmpl_UInt_GCD(z_x, z_y) == 1U)
                fputc(white, fp);
            else
                fputc(black, fp);
        }
        /*  End of for-loop for the pixels x-coordinate.                      */
    }
    /*  End of for-loop for the pixels y-coordinate.                          */

    /*  Close the file.                                                       */
    fclose(fp);
    return 0;
}
/*  End of main.                                                              */
