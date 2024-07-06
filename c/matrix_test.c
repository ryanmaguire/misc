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
#include <stdarg.h>
#include <stdio.h>

struct matrix {
    double *data;
    unsigned int width;
    unsigned int height;
};

static struct matrix create_matrix(unsigned int width, unsigned int height, ...)
{
    struct matrix out;
    unsigned int x, y;
    double *vec;
    va_list ap;

    if ((height == 0U) || (width == 0U))
        goto FAIL;

    out.height = height;
    out.width = width;
    out.data = malloc(sizeof(*out.data) * width * height);

    if (!out.data)
        goto FAIL;

    va_start(ap, height);

    for (y = 0U; y < height; ++y)
    {
        vec = va_arg(ap, double *);
        for (x = 0U; x < width; ++x)
            out.data[x + y*width] = vec[x];
    }

    va_end(ap);
    return out;

FAIL:
    out.height = 0U;
    out.width = 0U;
    out.data = NULL;
    return out;
}

static void destroy_matrix(struct matrix * const mat)
{
    if (!mat)
        return;

    if (mat->data)
        free(mat->data);

    mat->data = NULL;
    mat->width = 0U;
    mat->height = 0U;
}

static void print_matrix(const struct matrix * const mat)
{
    unsigned int x, y;

    for (y = 0U; y < mat->height; ++y)
    {
        for (x = 0U; x < mat->width; ++x)
            printf("%f ", mat->data[x + y*mat->width]);

        printf("\n");
    }
}

int main(void)
{
    const double a1[3] = {1.0, 2.0, 3.0};
    const double a2[3] = {4.0, 5.0, 6.0};
    struct matrix mat = create_matrix(3, 2, a1, a2);

    /*  This works with C99 compatible compilers.
     *      struct matrix mat = create_matrix(
     *          3, 2, (double[3]){1.0, 2.0, 3.0}, (double[3]){4.0, 5.0, 6.0}
     *      );
     */
    print_matrix(&mat);
    destroy_matrix(&mat);
    return 0;
}
