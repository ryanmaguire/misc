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
 *      Provides an example of using the ctypes package to call C functions.  *
 *      This also notes the benefit of using a compiled language. A decent    *
 *      compiler will optimize the for-loop away and just return the input.   *
 *      This makes an O(n) computation into O(1). The time test in add.py     *
 *      demonstrates this very well.                                          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 15, 2023                                                  *
 ******************************************************************************/

/*  The function we're defining.                                              */
extern int add(int n);

/*  Function for performing 1 + 1 + 1 + ... n times.                          */
int add(int n)
{
    /*  Dummy variable for indexing over the sum.                             */
    int ind;

    /*  Variable for the output. Start the sum at zero.                       */
    int x = 0;

    /*  Loop through and keep incrementing the input. A decent compiler with  *
     *  optimizations on should get rid of this loop completely and return    *
     *  the input, performing the calculation instantly.                      */
    for (ind = 0; ind < n; ++ind)
        x += 1;

    return x;
}
/*  End of add.                                                               */
