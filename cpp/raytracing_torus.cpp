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
 *  This is my first poor attempt at raytracing a torus using the implicit    *
 *  equation of a torus. It is slow, not optimized, and does not use          *
 *  parallel processing.                                                      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       2022/03/02                                                    *
 ******************************************************************************/

/*  Needed for the FILE data type and fprintf function.                       */
#include <stdio.h>

/*  Square root function found here.                                          */
#include <math.h>

/*  A simple structure for dealing with vectors. Used for rays of light.      */
struct vec3 {

    /*  A vector will be defined by it's Euclidean components, x, y, z.       */
    double x, y, z;

    /*  Empty constructor for the vec3.                                       */
    vec3(void)
    {
        return;
    }

    /*  Main constructor. Set x, y, and z to a, b, and c, respectively.       */
    vec3(double a, double b, double c)
    {
        x = a;
        y = b;
        z = c;
    }

    /*  Vector addition. This is done component-wise.                         */
    vec3 operator + (const vec3 &r) const
    {
        return vec3(x + r.x, y + r.y, z + r.z);
    }

    /*  Vector subtraction. Again, done component-wise.                       */
    vec3 operator - (const vec3 &r) const
    {
        return vec3(x - r.x, y - r.y, z - r.z);
    }

    /*  Scalar multiplication.                                                */
    vec3 operator * (double r) const
    {
        return vec3(x*r, y*r, z*r);
    }

    /*  Euclidean dot product of two vectors.                                 */
    double operator % (const vec3 &r) const
    {
        return x*r.x + y*r.y + z*r.z;
    }

    /*  A method for computing the Euclidean norm of a vector.                */
    double norm(void) const
    {
        return sqrt(x*x + y*y + z*z);
    }

    /*  A method for computing the square of the Euclidean norm of a vector.  *
     *  This is computationally useful since it avoids redundant square roots.*/
    double normsq(void) const
    {
        return x*x + y*y + z*z;
    }

    vec3 unit_vector(void) const
    {
        double rcpr = 1.0 / sqrt(x*x + y*y + z*z);
        return vec3(x*rcpr, y*rcpr, z*rcpr);
    }
};
/*  End of definition of vec3.                                                */

/*  Struct for working with colors in RGB format.                             */
struct color {
    unsigned char red, green, blue;

    color(void)
    {
        return;
    }

    color(unsigned char a, unsigned char b, unsigned char c)
    {
        red = a;
        green = b;
        blue = c;
    }

    color operator * (double a) const
    {
        unsigned char r = static_cast<unsigned char>(a*red);
        unsigned char g = static_cast<unsigned char>(a*green);
        unsigned char b = static_cast<unsigned char>(a*blue);
        return color(r, g, b);
    }

    /*  Function for writing a color to a PPM file.                           */
    void write(FILE *fp) const
    {
        fputc(red, fp);
        fputc(green, fp);
        fputc(blue, fp);
    }
};

static color sky_color(double zenith)
{
    color out;
    double factor;
    if (zenith < 0.1745)
        return color(0xFFU, 0xFFU, 0x00U);

    factor = cos(zenith);
    out.blue = 255U;
    out.red = static_cast<unsigned char>(factor * 135.0);
    out.green = static_cast<unsigned char>(factor * 206.0);
    return out;
}

static const double Inner_Radius = 1.0;
static const double Outer_Radius = 2.0;
static const double threshold = 0.01;

static double torus_implicit(vec3 p)
{
    const double a = sqrt(p.x*p.x + p.y*p.y) - Outer_Radius;
    return a*a + p.z*p.z - Inner_Radius*Inner_Radius;
}

static vec3 torus_gradient(vec3 p)
{
    double rho = sqrt(p.x*p.x + p.y*p.y);
    double factor = 2.0*(rho - Outer_Radius) / rho;
    return vec3(factor * p.x, factor * p.y, 2.0 * p.z);
}

static color sampler(vec3 p, vec3 v, double dt)
{
    const unsigned int max_iters = 1000U;
    const unsigned int max_reflections = 3U;
    static unsigned int iters = 0U;
    static unsigned int reflections = 0U;
    vec3 grad_p;

    while (iters < max_iters && reflections < max_reflections)
    {
        ++iters;

        if (fabs(torus_implicit(p)) <= threshold)
        {
            ++reflections;
            grad_p = torus_gradient(p).unit_vector();
            v = v - (grad_p * 2.0*(v % grad_p));
            return sampler(p, v, dt) * 0.95;
        }

        else
            p = p + v*dt;
    }

    reflections = 0U;
    iters = 0U;

    if (v.z <= 0.0)
    {
        const double t = -p.z / v.z;
        const vec3 intesect = p + v*t;

        if (int(ceil(intesect.x) + ceil(intesect.y)) & 1)
            return color(0xFFU, 0xFFU, 0xFFU);
        else
            return color(0xFFU, 0x00U, 0x00U);
    }

    else
    {
        double rho = sqrt(v.x*v.x + v.y*v.y);
        double zenith = M_PI_2 - atan(v.z / rho);
        return sky_color(zenith);
    }
}

/*  Main function for performing the raytracing.                              */
int main(void)
{
    const vec3 v = vec3(0.0, 0.0, -1.0);
    const vec3 u0 = vec3(1.0,  0.0,  0.0);
    const vec3 u1 = vec3(0.0,  1.0, 0.0);
    const vec3 eye = vec3(0.0, 0.0, 4.0);
    unsigned int x, y;

    /*  Set the values for the size of the detector.                          */
    const double start = -2.0;
    const double end =  2.0;
    const double dt = 0.01;

    /*  Set the number of pixels in the detector.                             */
    const unsigned int size = 1024U;

    /*  And compute the factor that allows us to convert between a pixel      *
     *  and the corresponding point on the detector.                          */
    const double factor = (end - start) / static_cast<double>(size);
    const double prog_factor = 100.0 / static_cast<double>(size);

    /*  Open the file "torus_raytracer.ppm" and give it write permissions.    */
    FILE *fp = fopen("torus_raytracer.ppm", "w");

    /*  If fopen fails it returns NULL. Check that this didn't happen.        */
    if (!fp)
    {
        puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    /*  Print the preamble to the PPM file. A PPM file wants Pn followed by   *
     *  three numbers. P6 means we're encoding an RGB image in binary format. *
     *  The first two numbers are the number of pixels in the x and y axes.   *
     *  The last number is the size of our color spectrum, which is 255.      */
    fprintf(fp, "P6\n%u %u\n255\n", size, size);

    /*  We can NOT do parallel processing with the creation of our PPM file   *
     *  since the order the values are computed is essential.                 */
    for (y = 0U; y < size; ++y)
    {
        for (x = 0U; x < size; ++x)
        {
            /*  We're incrementing p across our detector.                     */
            const vec3 u = u0*(start + x*factor) + u1*(start + y*factor) + eye;
            const vec3 p = u + v;
            const vec3 dir = (p - eye).unit_vector();
            const color c = sampler(p, dir, dt);
            c.write(fp);
        }

        if ((y % 20) == 0)
            fprintf(stderr, "Progress: %.4f%%\r", prog_factor*y);
    }

    fclose(fp);
    return 0;
}
/*  End of main.                                                              */
