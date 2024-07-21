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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       2018                                                          *
 ******************************************************************************/
extern void mandelbrot(int argc, void *argv[]);

void mandelbrot(int argc, void *argv[])
{
    /*  Extract the data from the IDL call.                                   */
    const int xsize = *(int *)argv[0];
    const int ysize = *(int *)argv[1];
    const double xstart = *(double *)argv[2];
    const double ystart = *(double *)argv[3];
    const double xfactor = *(double *)argv[4];
    const double yfactor = *(double *)argv[5];
    const int max_iters = *(int *)argv[6];
    int *result = (int *)argv[7];

    /*  Variables for the looping over the pixels.                            */
    int x, y;

    /*  IDL should have passed 8 arguments. Check for this.                   */
    if (argc != 8)
        return;

    /*  Loop through the y coordinates of the pixels.                         */
    for (y = 0; y < ysize; ++y)
    {
        /*  Convert the y-component of the pixel to the imaginary part of z.  */
        const double imag = ystart + (double)y*yfactor;

        /*  Loop through the x coordinates of the pixels.                     */
        for (x = 0; x < xsize; ++x)
        {
            /*  Convert the y-component of the pixel to the real part of z.   */
            const double real = xstart + (double)x * xfactor;

            /*  The iteration starts at the origin, (z_x, z_y) = (0, 0).      */
            double z_x = 0.0;
            double z_y = 0.0;
            int iters;

            for (iters = 0; iters < max_iters; ++iters)
            {
                /*  Compute z_{n+1} = z_{n}^2 + c. Avoid overwriting the data *
                 *  and store the values in new variables.                    */
                const double z_next_real = z_x*z_x - z_y*z_y + real;
                const double z_next_imag = 2.0*z_x*z_y + imag;

                /*  We can now copy the data over to the main variables.      */
                z_x = z_next_real;
                z_y = z_next_imag;

                /*  Check for divergence.                                     */
                if (z_x*z_x + z_y*z_y > 4.0)
                    break;
            }

            /*  Record the number of iterations needed and move to the next.  */
            *result = iters;
            ++result;
        }
    }
}
