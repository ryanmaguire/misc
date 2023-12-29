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
 *      Idea given to me for working with a single "real" data type. This     *
 *      tests the efficiency of such a data structure.                        *
 *                                                                            *
 *      Outputs for 10^8 samples between 0 and 10 are:                        *
 *          Standard:   0.3947                                                *
 *          By Address: 1.2420                                                *
 *          By Value:   1.6770                                                *
 *      Interesting idea, but performance suffers dramatically for 32-bit     *
 *      single precision floats.                                              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 22, 2023                                             *
 ******************************************************************************/

/*  printf provided here.                                                     */
#include <stdio.h>

/*  malloc, free, and the size_t data type all provided here.                 */
#include <stdlib.h>

/*  Functions for measuring time down to the microsecond.                     */
#include <sys/time.h>

/*  sine function for float, double, and long double given here.              */
#include <math.h>

/*  Flags for the three types of real numbers in the union.                   */
#define FLOAT_FLAG (0)
#define DOUBLE_FLAG (1)
#define LDOUBLE_FLAG (2)

/*  Type for representing a real number at any of the provided precisions.    */
typedef struct {

    /*  A union for the data of the real number. Note, the size of such a     *
     *  union is the size of the largest data type (long double here).        */
    union {
        float f;
        double d;
        long double ld;
    } r;

    /*  Flag indicating which of the above data types is being used.          */
    int flag;
} real;

/*  Computes sine of a real number passed by address.                         */
static real sine_by_ptr(const real *val)
{
    /*  Struct for the output.                                                */
    real sin_val;

    /*  C99 (and higher) provided sinf for single precision sine.             */
    if (val->flag == FLOAT_FLAG)
    {
        sin_val.flag = FLOAT_FLAG;
        sin_val.r.f = sinf(val->r.f);
    }

    /*  All versions of the C standard have sine for double precision.        */
    else if (val->flag == DOUBLE_FLAG)
    {
        sin_val.flag = DOUBLE_FLAG;
        sin_val.r.d = sin(val->r.d);
    }

    /*  Long double implementation was introduced in C99 as well.             */
    else
    {
        sin_val.flag = LDOUBLE_FLAG;
        sin_val.r.ld = sinl(val->r.ld);
    }

    return sin_val;
}
/*  End of sine_by_ptr.                                                       */

/*  Computes sine of a real number passed by value.                           */
static real sine_by_val(real val)
{
    /*  Struct for the output.                                                */
    real sin_val;

    /*  C99 (and higher) provided sinf for single precision sine.             */
    if (val.flag == FLOAT_FLAG)
    {
        sin_val.flag = FLOAT_FLAG;
        sin_val.r.f = sinf(val.r.f);
    }

    /*  All versions of the C standard have sine for double precision.        */
    else if (val.flag == DOUBLE_FLAG)
    {
        sin_val.flag = DOUBLE_FLAG;
        sin_val.r.d = sin(val.r.d);
    }

    /*  Long double implementation was introduced in C99 as well.             */
    else
    {
        sin_val.flag = LDOUBLE_FLAG;
        sin_val.r.ld = sinl(val.r.ld);
    }

    return sin_val;
}
/*  End of sine_by_val.                                                       */

/*  Computes the computational time from the given start and end times.       */
static double comp_time(const struct timeval *t0, const struct timeval *t1)
{
    /*  Number of seconds that occured, as an integer.                        */
    const long secs = t1->tv_sec - t0->tv_sec;

    /*  Number of microseconds after the last number of seconds.              */
    const long usecs = t1->tv_usec - t0->tv_usec;

    /*  Convert seconds to micro-seconds by multiplying by 10^6.              */
    const long sum = 1000000L * secs + usecs;

    /*  Convert back to seconds by using a double.                            */
    return 1.0E-6 * (double)sum;
}
/*  End of comp_time.                                                         */

/*  Function for testing the efficiency of the above functions.               */
int main(void)
{
    /*  Variables for keeping track of computation time.                      */
    struct timeval t0, t1;

    /*  Arrays for performing the computation on native types.                */
    float *xf, *yf;

    /*  Arrays for computing with the union type specified above.             */
    real *xr, *yr, *zr;

    /*  The number of samples we'll test.                                     */
    const size_t n_samples = (size_t)(1E8);

    /*  Variable for indexing over all of the arrays.                         */
    size_t n;

    /*  Constant for zero cast to type "size_t".                              */
    const size_t zero = (size_t)0;

    /*  Increment factor. x[n] = dx * n_samples.                              */
    const float dx = 10.0F / (float)n_samples;

    /*  Dummy variables used for ensuring the compiler does not optimize the  *
     *  for-loops away. We'll compute the "error" in the computation.         */
    float tmp, erry, errz;

    /*  Variable for printing the computational time.                         */
    double ctime;

    /*  Allocate memory for all variables. Out of laziness we'll assume       *
     *  malloc is successful and not check if it returns NULL.                */
    xf = malloc(sizeof(*xf) * n_samples);
    yf = malloc(sizeof(*yf) * n_samples);

    /*  Memory for the "real" variables as well. Same laziness as before.     */
    xr = malloc(sizeof(*xr) * n_samples);
    yr = malloc(sizeof(*yr) * n_samples);
    zr = malloc(sizeof(*zr) * n_samples);

    /*  Create the independent variable. An array of equally spaced numbers.  */
    for (n = zero; n < n_samples; ++n)
    {
        xf[n] = dx * (float)n;

        /*  We're working with float, so set the flag accordingly.            */
        xr[n].flag = FLOAT_FLAG;
        xr[n].r.f = xf[n];
    }

    /*  Time test for the native method. float in, float out.                 */
    gettimeofday(&t0, NULL);
    for (n = zero; n < n_samples; ++n)
        yf[n] = sinf(xf[n]);
    gettimeofday(&t1, NULL);

    ctime = comp_time(&t0, &t1);
    printf("Standard:   %.4f\n", ctime);

    /*  Time test for unions where the data is passed by address.             */
    gettimeofday(&t0, NULL);
    for (n = zero; n < n_samples; ++n)
        yr[n] = sine_by_ptr(&xr[n]);

    gettimeofday(&t1, NULL);

    ctime = comp_time(&t0, &t1);
    printf("By Address: %.4f\n", ctime);

    /*  Time test for unions where the data is passed by value.               */
    gettimeofday(&t0, NULL);
    for (n = zero; n < n_samples; ++n)
        zr[n] = sine_by_val(xr[n]);
    gettimeofday(&t1, NULL);

    ctime = comp_time(&t0, &t1);
    printf("By Value:   %.4f\n", ctime);

    /*  Stupid test to avoid the compiler optimizing everything way.          */
    erry = 100.0;
    errz = 100.0;

    for (n = zero; n < n_samples; ++n)
    {
        /*  Find the max error in the computation. If everything was set up   *
         *  correctly this should be zero since the same function is called.  */
        tmp = fabsf(yf[n] - yr[n].r.f);

        if (tmp < erry)
            erry = tmp;

        /*  Same test for the pass-by-value data.                             */
        tmp = fabsf(yf[n] - zr[n].r.f);

        if (tmp < errz)
            errz = tmp;

    }

    /*  Now use those variables to avoid compiler optimizing the test way.    */
    printf("By Address Error: %e\n", (double)erry);
    printf("By Value Error:   %e\n", (double)errz);

    /*  Free all of the data and exit the computation.                        */
    free(xf);
    free(yf);
    free(xr);
    free(yr);
    free(zr);

    return 0;
}
/*  End of main.                                                              */
