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
 *      Shows some of the basic syntax in C.                                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       2021                                                          *
 ******************************************************************************/

/*  The printf function, used for printing to the terminal, is given here.    */
#include <stdio.h>

/*  Simple function for adding two integers together.                         */
static int add_int(int x, int y)
{
    return x + y;
}

/*  Simple function for adding two floating point numbers together.           */
static float add_float(float x, float y)
{
    return x + y;
}

/*  Routine for testing the functions we defined above.                       */
int main(void)
{
    /*  Declare the variables used in this function.                          */
    int n;
    float r;

    /*  Call the functions we defined above.                                  */
    n = add_int(1, 2);
    r = add_float(1.2F, 2.4F);

    /*  Print them to the console.                                            */
    printf("Int: %d Float: %f\n", n, (double)r);
    return 0;
}
