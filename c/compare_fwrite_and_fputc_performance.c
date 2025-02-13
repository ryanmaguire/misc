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
 *		Benchmarks writing a PPM using fputc or fwrite.                       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 13, 2025                                             *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    unsigned char dat[3];
} color;

static void write(const color c, FILE *fp)
{
    fputc(c.dat[0], fp);
    fputc(c.dat[1], fp);
    fputc(c.dat[2], fp);
}

static void write_alt(const color c, FILE *fp)
{
    fwrite(c.dat, sizeof(c.dat), 1, fp);
}

static FILE *create(const char *name)
{
    FILE *fp = fopen(name, "w");
    fputs("P6\n4096 4096\n255\n", fp);
    return fp;
}

static color random_color(void)
{
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;
    color out;

    out.dat[0] = (unsigned char)r;
    out.dat[1] = (unsigned char)g;
    out.dat[2] = (unsigned char)b;
    return out;
}

int main(void)
{
    FILE *fp0 = create("write.ppm");
    FILE *fp1 = create("alt.ppm");
    FILE *fp2 = create("full.ppm");
    size_t size = (1 << 24);
    size_t n;
    clock_t t0, t1;

    color * const c = malloc(sizeof(*c) * size);

    for (n = 0; n < size; ++n)
        c[n] = random_color();

    t0 = clock();
    for (n = 0; n < size; ++n)
        write(c[n], fp0);

    t1 = clock();
    printf("%E\n", (double)(t1 - t0) / CLOCKS_PER_SEC);

    t0 = clock();
    for (n = 0; n < size; ++n)
            write_alt(c[n], fp1);

    t1 = clock();
    printf("%E\n", (double)(t1 - t0) / CLOCKS_PER_SEC);

    t0 = clock();
    fwrite(c, sizeof(c->dat), size, fp2);
    t1 = clock();
    printf("%E\n", (double)(t1 - t0) / CLOCKS_PER_SEC);

    free(c);
    fclose(fp0);
    fclose(fp1);
    return 0;
}
