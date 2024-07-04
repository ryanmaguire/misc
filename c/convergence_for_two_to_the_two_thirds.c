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
 *      I have no idea why I made this, but this code shows the convergence   *
 *      of the sequence a_{n+2} = sqrt(a_{n} * a_{n+1}) with starting values  *
 *      a_{0} = 1, a_{1} = 2, to the value 2^(2/3).                           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 28, 2021                                                 *
 ******************************************************************************/

/*  Needed for printf, fopen, fclose, fputs, fprintf, and the FILE type.      */
#include <stdlib.h>

/*  Needed for malloc and free.                                               */
#include <stdio.h>

/*  square root function provided here.                                       */
#include <math.h>

/*  Struct to represent an ordered pair for points in the plane.              */
struct pair {
    double x, y;
};

/*  Struct for dealing with colors in RGB format.                             */
struct color {
    unsigned char red, green, blue;
};

/*  Struct for creating the SVG file.                                         */
struct canvas {
    FILE *fp;
    unsigned int width, height;
    struct color background, outline;
    double xshift, yshift, xscale, yscale;
    double xmin, ymin, xmax, ymax;

    /*  Opacity should be a real number between 0 and 1.                      */
    double opacity;
};

static const char svg_preamble[363] =
    "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"
    "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" "
    "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n"
    "<svg viewBox=\"0 0 %u %u\" "
    "xmlns=\"http://www.w3.org/2000/svg\" "
    "xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
    "<rect fill=\"#%02x%02x%02x\" stroke=\"#%02x%02x%02x\" "
    "x=\"0\" y=\"0\" width=\"%u\" height=\"%u\"/>\n"
    "<g opacity=\"%f\">\n";

/*  Function for creating the preamble to an SVG file.                        */
static void create_svg(struct canvas * const layout, const char * const name)
{
    /*  Check that the input isn't NULL. Abort if so.                         */
    if (!layout)
        return;

    /*  Open the file and give it write permissions.                          */
    layout->fp = fopen(name, "w");

    /*  fopen returns NULL on failure. Check for this.                        */
    if (!layout->fp)
        return;

    /*  Write the preamble to the file.                                       */
    fprintf(
        layout->fp,
        svg_preamble,
        layout->width, layout->height,
        layout->background.red,  layout->background.green,
        layout->background.blue,
        layout->outline.red, layout->outline.green, layout->outline.blue,
        layout->width, layout->height,
        layout->opacity
    );
}
/*  End of create_svg.                                                        */

/*  Function for writing the ending of an SVG file.                           */
static void close_svg(struct canvas * const layout)
{
    /*  If fp is a NULL pointer, trying to write to it will result in a       *
     *  segmentation fault. Check that this isn't the case.                   */
    if (!layout->fp)
        return;

    /*  Print the closing line for an SVG to the file.                        */
    fputs("</g>\n</svg>\n", layout->fp);

    /*  The SVG is finished being written to at this point. Close the file.   */
    fclose(layout->fp);

    /*  Avoid repeated calls to fclose. Set the file pointer to NULL.         */
    layout->fp = NULL;
}
/*  End of close_svg.                                                         */

/*  Function for computing a_{n+2} = sqrt(a_{n} * a_{n+1}).                   */
static void func(unsigned int n, double *arr)
{
    /*  The initial conditions are 1 and 2.                                   */
    if (n == 0)
        arr[0] = 1.0;
    else if (n == 1)
        arr[1] = 2.0;

    /*  For all other values, use the recursive definition.                   */
    else
        arr[n] = sqrt(arr[n - 2U] * arr[n - 1U]);
}
/*  End of func.                                                              */

/*  Function for converting between Cartesian and SVG coordinates.            */
static struct pair
cart_to_svg(struct pair P, const struct canvas * const layout)
{
    /*  Declare variable for the output.                                      */
    struct pair out;

    /*  Convert the Cartesian values to the SVG values.                       */
    out.x = layout->xscale*(P.x + layout->xshift);
    out.y = layout->yscale*(layout->yshift - P.y);
    return out;
}
/*  End of cart_to_svg.                                                       */

/*  Function for adding a line to the SVG file.                               */
static void
draw_line(struct canvas * const layout, struct pair P, struct pair Q,
          struct color line_color, double thickness)
{
    const struct pair P_svg = cart_to_svg(P, layout);
    const struct pair Q_svg = cart_to_svg(Q, layout);

    fprintf(
        layout->fp,
        "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" "
        "stroke=\"#%02x%02x%02x\" stroke-width=\"%f\" "
        "stroke-linecap=\"round\" />\n",
        P_svg.x, P_svg.y, Q_svg.x, Q_svg.y,
        line_color.red, line_color.green, line_color.blue, thickness
    );
}
/*  End of draw_line.                                                         */

/*  Function for showing the convergence of a_{n} to 2^(2/3).                 */
int main(void)
{
    /*  Name of the SVG file that is created. The picture is drawn here.      */
    const char * filename = "convergence_for_two_to_the_two_thirds.svg";

    /*  Variable for indexing.                                                */
    unsigned int n;

    /*  Number of iterations to perform.                                      */
    const unsigned int max_iters = 56U;

    /*  Size of the output SVG file.                                          */
    const unsigned int width = 1024U;
    const unsigned int height = 576U;

    /*  Coordinates of the output.                                            */
    const double xmax = (double)(max_iters - 1U);
    const double ymax = 3.0;
    const double xmin = -1.0;
    const double ymin = -0.5;

    /*  The value 2^(2/3).                                                    */
    const double val = 1.5874010519681994747517056392723082603914933;

    /*  The background will be white, which is (255, 255, 255).               */
    const struct color white = {0xFFU, 0xFFU, 0xFFU};

    /*  And the line color is black.                                          */
    const struct color black = {0x00U, 0x00U, 0x00U};

    /*  Thickness for lines.                                                  */
    const double thickness = 1.0;

    /*  The canvas details the layout of the SVG file.                        */
    struct canvas layout;

    /*  Pairs for the axes.                                                   */
    const struct pair x_axis[2] = {{xmin, 0.0}, {xmax, 0.0}};
    const struct pair y_axis[2] = {{0.0, ymin}, {0.0, ymax}};

    /*  Thickness for axes.                                                   */
    const double axes_thickness = 2.0;

    /*  And a pointer to an array to store the sequence.                      */
    double * const arr = malloc(sizeof(*arr) * max_iters);

    /*  Check if malloc failed.                                               */
    if (!arr)
    {
        puts("Malloc failed and returned NULL. Returning.");
        return -1;
    }

    /*  Store the necessary values in the layout.                             */
    layout.width = width;
    layout.height = height;
    layout.background = white;
    layout.outline = black;
    layout.opacity = 1.0;
    layout.xmin = xmin;
    layout.xmax = xmax;
    layout.ymin = ymin;
    layout.ymax = ymax;
    layout.xshift = -xmin;
    layout.yshift = +ymax;
    layout.xscale = (double)width  / (xmax - xmin);
    layout.yscale = (double)height / (ymax - ymin);

    /*  Write the preamble to the SVG file we're making.                      */
    create_svg(&layout, filename);

    /*  Check if create_svg failed.                                           */
    if (!layout.fp)
    {
        puts("create_svg failed to create SVG file. Aborting.");

        /*  Free the data that has been malloced so far.                      */
        free(arr);
        return -1;
    }

    /*  Perform the iteration a_{n+2} = sqrt(a_n * a_{n+1}).                  */
    for (n = 0U; n < max_iters; ++n)
        func(n, arr);

    /*  Draw the curve in the SVG file.                                       */
    for (n = 0U; n < max_iters - 1U; ++n)
    {
        const double n_real = (double)n;
        const struct pair P = {n_real, arr[n]};
        const struct pair Q = {n_real + 1.0, arr[n + 1U]};
        draw_line(&layout, P, Q, black, thickness);
    }

    /*  Draw the axes.                                                        */
    draw_line(&layout, x_axis[0], x_axis[1], black, axes_thickness);
    draw_line(&layout, y_axis[0], y_axis[1], black, axes_thickness);

    /*  Write the ending of the SVG and close the file.                       */
    close_svg(&layout);

    /*  Print the error for the final iteration.                              */
    printf("Final Iteration: %+.18E\n", arr[max_iters - 1U]);
    printf("2^(2/3):         %+.18E\n", val);
    printf("Error:           %+.18E\n", val - arr[max_iters - 1U]);

    /*  Free memory allocated for the array and exit the function.            */
    free(arr);
    return 0;
}
/*  End of main.                                                              */
