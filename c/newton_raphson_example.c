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
 *      Basic implementation of the Newton-Raphson method.                    *
 ******************************************************************************/

/*  printf function provided here.                                            */
#include <stdio.h>

/*  Math functions like sin, cos, and sqrt are found here.                    */
#include <math.h>

/*  Typedef for function pointers, real in, real out.                         */
typedef double (*function)(double);

/*  Maximum number of iterations allowed in Newton-Raphson's method.          */
#define MAX_ITERS (20U)

/*  Allowed tolerance in Newton-Raphson. Two times double epsilon.            */
#define EPS (+4.440892098500626E-16)

/*  Function for performing Newton-Raphon's method on f with guess x_0 = x.   */
static double newton(double x, function f, function f_prime)
{
    /*  Variable for the Newton-Raphson iterate.                              */
    double dx;

    /*  Variable for keeping track of the number of iterations performed.     */
    unsigned int iters = 0U;

    do {
        /*  Compute the Newton-Raphson iterate, f(x_n) / f'(x_n).             */
        dx = f(x) / f_prime(x);

        /*  Perform the Newton-Raphson update: x_{n+1} = x_n - dx_n.          */
        x -= dx;

        /*  Avoid an infinite loop, update the number of iterations performed.*/
        ++iters;

        /*  Break out of the loop if this takes too long.                     */
        if (iters == MAX_ITERS)
            break;

    /*  Abort the computation once the Newton-Raphson factor is small.        */
    } while(fabs(dx) > EPS);

    return x;
}
/*  End of newton.                                                            */

/*  Function used to compute sqrt(2).                                         */
static double x_square(double x){return x*x - 2.0;}
static double d_x_square(double x){return 2.0*x;}

/*  Function used to compute exp(1).                                          */
static double log_minus_1(double x){return log(x) - 1.0;}
static double d_log_minus_1(double x){return 1.0/x;}

/*  Function used to compute the golden ratio, (-1 + sqrt(5)) / 2.            */
static double golden_ratio(double x){return x*x - x - 1.0;}
static double d_golden_ratio(double x){return 2.0*x - 1.0;}

/*  Function used to compute the "music" number, 2^{1/12}.                    */
static double x_12_minus_2(double x){return pow(x, 12.0) - 2.0;}
static double d_x_12_minus_2(double x){return 12.0*pow(x, 11.0);}

/*  Routine for testing the Newton-Raphson method on several functions.       */
int main(void)
{
    /*  Variable for the guess point, and the computed root.                  */
    double x, root;

    /*  Use Newton-Raphson to compute sqrt(2).                                */
    x = 2.0;
    root = newton(x, x_square, d_x_square);
    printf("The Square Root of Two: %0.16F\n", root);
    printf("Exact:                  1.414213562373095048801688724\n\n");

    /*  Use Newton-Raphson to compute pi.                                     */
    x = 3.0;
    root = newton(x, sin, cos);
    printf("The Value of Pi: %0.16F\n", root);
    printf("Exact:           3.14159265358979323846\n\n");

    /*  Use Newton-Raphson to compute exp(1).                                 */
    x = 3.0;
    root = newton(x, log_minus_1, d_log_minus_1);
    printf("Euler's Number (e): %0.16F\n", root);
    printf("Exact:              2.71828182845904523536028\n\n");

    /*  Use Newton-Raphson to compute the golden ratio.                       */
    x = 2.0;
    root = newton(x, golden_ratio, d_golden_ratio);
    printf("The Golden Ratio: %0.16F\n", root);
    printf("Exact:            1.618033988749894848204\n\n");

    /*  Use Newton-Raphson to compute the music number, 2^{1/12}.             */
    x = 1.0;
    root = newton(x, x_12_minus_2, d_x_12_minus_2);
    printf("The Music Number is: %0.16F\n", root);
    printf("Exact:               1.059463094359295264561825\n");
}
/*  End of main.                                                              */
