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
 *      Example of using volatile to ensure the correct result is obtained.   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 10, 2026                                                  *
 ******************************************************************************/

/*  puts function (which stands for "put string") found here.                 */
#include <stdio.h>

/*  EXIT_SUCCESS and EXIT_FAILURE macros provided here.                       */
#include <stdlib.h>

/*  jmp_buf typedef and the longjmp and setjmp functions are provided here.   */
#include <setjmp.h>

/*  jmp_buf is an array type used for storing information to restore a        *
 *  calling environment.                                                      */
static jmp_buf buffer;

/*  Function for exploring the volatile keyword and setjmp routines.          */
int main(void)
{
    /*  Using either GCC 14.2 or clang 19.1.7 with -O2 or -O3, failure to     *
     *  declare this variable as volatile produces an infinite loop. These    *
     *  compilers optimize away the check for count != 5 since it is not able *
     *  to see that the longjmp function will result in the count being 6     *
     *  when the if statement is checked a second time. Using the volatile    *
     *  keyword prevents this. The function prints "Hello, World!" once, the  *
     *  count will be set to 6, and then the the routine will exit. GCC and   *
     *  clang are not alone here, many optimizing compilers require volatile. */
    volatile int count = 5;

    /*  Save the current execution content into the buffer. The first time    *
     *  this is called, setjmp will output "0," meaning the contents of the   *
     *  following block will be executed.                                     */
    if (setjmp(buffer) != 2)
    {
        /*  During the first pass, count = 5 so this block is skipped.        */
        if (count != 5)
        {
            /*  When we get here, count = 6 and longjmp was called with       *
             *  status = 1. Print a greeting.                                 */
            const int puts_success = puts("Hello, World!");

            /*  Check that puts was successful. It returns EOF on failure.    */
            if (puts_success == EOF)
                return EXIT_FAILURE;

            /*  If we get here, then the "longjmp(buffer, 1);" line below has *
             *  already been called and count is now set to 6. Return back to *
             *  the initial "if" block, but make it so that setjmp returns 2, *
             *  meaning the block for this if statement will not execute.     */
            longjmp(buffer, 2);
        }

        /*  Reset the count to 6 and return to the start of the initial "if"  *
         *  block, but now have setjmp output "1" instead of "0".             */
        count = 6;
        longjmp(buffer, 1);
    }

    /*  We have printed our greeting and can now exit.                        */
    return EXIT_SUCCESS;
}
/*  End of main.                                                              */
