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
 ******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*  This function colors the current pixel in the format (R, G, B).           */
static void color(int red, int green, int blue, FILE *fp)
{
    fputc(red, fp);
    fputc(green, fp);
    fputc(blue, fp);
}

/*  Function for computing the Euclidean distance from z0 to z1.              */
static double norm(const double * const z0, const double * const z1)
{
    const double x = z1[0] - z0[0];
    const double y = z1[1] - z0[1];
    return sqrt(x*x + y*y);
}

int main(void)
{
    /*  Pixel size of the image to be created.                                */
    const unsigned int size = 1024U;

    /*  Divide by two before hand to save on division computations.           */
    const double size_by_two = size / 2.0;

    /*  Radius of the final image.                                            */
    const double image_radius = 2.0;

    /*  Radius of the circle to be drawn.                                     */
    const double circle_radius = 1.0;

    /*  Scale factor for incrementing through each pixel.                     */
    const double scale_factor = 2*image_radius/size;

    /*  Array for the center of the sphere.                                   */
    double center[2];

    /*  Array for the current point being computed.                           */
    double point[2];

    /*  Variable used for determining how bright a given pixel is.            */
    int brightness;

    /*  Variables used for indexing over the x and y coordinates.             */
    unsigned int x, y;

    /*  Variable used for the distance from point to center.                  */
    double dist;

    /*  File we're printing too.                                              */
    FILE *fp = fopen("sphere_raster.ppm", "w");

    // Check if fopen failed.
    if (!fp)
    {
        puts("fopen failed and return NULL. Aborting.");
        return -1;
    }

    /*  Print the preamble for the PPM file to the screen.                    */
    fprintf(fp, "P6\n%d %d\n255\n", size, size);

    /*  Set the the center to the origin (0, 0).                              */
    center[0] = 0;
    center[1] = 0;

    /*  Loop through each pixel.                                              */
    for(y = 0U; y < size; y++)
    {
        for(x = 0U; x < size; x++)
        {

            /*  Calculate the location of the current point.                  */
            point[0] = (x - size_by_two) * scale_factor;
            point[1] = (y - size_by_two) * scale_factor;

            /*  Compute the distance from point to center.                    */
            dist = norm(point, center);

            /*  If the point is outside of the circle, skip.                  */
            if (dist > circle_radius)
                brightness = 255;

            /*  Otherwise, draw a gradient for the sphere.                    */
            else
                brightness = (int)(255.0 * (1.0 - dist/circle_radius));

            /*  Color the current pixel and move on to the next one.          */
            color(brightness, brightness, brightness, fp);
        }
    }

    return 0;
}
