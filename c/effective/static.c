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
 *      Example of static usage in file and block scope.                      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 7, 2026                                                   *
 ******************************************************************************/

/*  printf function (which stands for "print format") found here.             */
#include <stdio.h>

/*  EXIT_SUCCESS and EXIT_FAILURE macros provided here.                       */
#include <stdlib.h>

/*  Static variable at file scope indicates linkage. This variable has        *
 *  internal linkage.                                                         */
static const char * const greeting = "Hello, World!";

/*  Static function declaration indicates the function is internal to this    *
 *  file, and files that #include this piece of code.                         */
static int increment(void)
{
    /*  Static variable at block scope within the function, this specifies    *
     *  storage duration. The variable retains its value even after the       *
     *  function exits. Note, to write reentrant code, you must not have      *
     *  functions modify static variables. In a single-threaded environment,  *
     *  using static is fine.                                                 */
    static int counter = 0;

    /*  Update the counter. The variable will retain this updated value after *
     *  the function exits.                                                   */
    ++counter;

    /*  Print the current count.                                              */
    return printf("%d\n", counter);
}
/*  End of increment.                                                         */

/*  Alternatively, we can achieve a similar effect using global variables.    *
 *  Be careful with global variables, since they are in the scope of any file *
 *  that #includes this code.                                                 */
static int global_counter = 0;

/*  This function achieves a similar goal to the last one, but it uses a      *
 *  global variable instead of a local static variable.                       */
static int increment_global(void)
{
    /*  No need to declare a new variable, simply update the global one.      */
    ++global_counter;

    /*  Print the current count.                                              */
    return printf("%d\n", global_counter);
}
/*  End of increment_global.                                                  */

/*  Test function for running our two routines.                               */
int main(void)
{
    /*  The number of times we will call the incrementing functions.          */
    const int max_count = 5;

    /*  Variable for looping, and a variable for checking if printf fails.    */
    int n, characters_printed;

    /*  Print our greeting (which is a global constant).                      */
    const int puts_success = puts(greeting);

    /*  Check if puts was unable to write to stdout. puts returns End-of-File *
     *  when this happens.                                                    */
    if (puts_success == EOF)
        return EXIT_FAILURE;

    /*  Loop using the increment function, which uses a static variable.      */
    for (n = 0; n < max_count; ++n)
    {
        /*  The function returns the number of characters printf printed.     *
         *  It returns a negative number on failure.                          */
        characters_printed = increment();

        /*  Check if printf failed.                                           */
        if (characters_printed < 0)
            return EXIT_FAILURE;
    }

    /*  Loop with the increment_global function, which uses a global variable.*/
    for (n = 0; n < max_count; ++n)
    {
        /*  The function should return '2' since printf should print an       *
         *  integer (the global_count) and a newline.                         */
        characters_printed = increment_global();

        /*  Check for errors.                                                 */
        if (characters_printed < 0)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
/*  End of main.                                                              */
