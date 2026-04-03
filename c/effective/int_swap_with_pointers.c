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
 *      Swaps the values of two int's using pointers.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 3, 2026                                                 *
 ******************************************************************************/

/*  printf function (which stands for "print format") found here.             */
#include <stdio.h>

/*  EXIT_SUCCESS and EXIT_FAILURE macros provided here.                       */
#include <stdlib.h>

/*  Function for swapping the values of two int's.                            */
static void swap(int * const pa, int * const pb)
{
    /*  We'll use a temporary variable for the swap, no fancy bit tricks.     */
    int tmp;

    /*  Safety check, make sure neither pointer is NULL.                      */
    if ((!pa) || (!pb))
        return;

    /*  Neither pa nor pb are NULL, try to dereference them. Store the value  *
     *  pointed to by pa into tmp to avoid losing it during the swap.         */
    tmp = *pa;

    /*  pa's value is saved, store pb's value in pa.                          */
    *pa = *pb;

    /*  Lastly, recover pa's original value from tmp and store it in pb.      */
    *pb = tmp;
}
/*  End of swap.                                                              */

/*  Main routine for testing our swap function above.                         */
int main(void)
{
    /*  Two variables for testing our swap function.                          */
    int a = 21;
    int b = 17;

    /*  Variable for checking if printf fails. printf returns the number of   *
     *  characters that were written to stdout on success, and a negative     *
     *  integer otherwise.                                                    */
    int characters_written = printf("Before Swap: a = %d, b = %d\n", a, b);

    /*  Check if printf succeeded.                                            */
    if (characters_written < 0)
        return EXIT_FAILURE;

    /*  Perform the swap. The swap function wants pointers to int's, so we    *
     *  must obtain the address of a and b using the ampersand operator.      */
    swap(&a, &b);

    /*  Print the new values (while checking for errors in printf).           */
    characters_written = printf("After Swap:  a = %d, b = %d\n", a, b);

    /*  Again, check to see if printf failed to print to stdout.              */
    if (characters_written < 0)
        return EXIT_FAILURE;

    /*  Otherwise, the program ran as intended. Return success.               */
    return EXIT_SUCCESS;
}
/*  End of main.                                                              */
