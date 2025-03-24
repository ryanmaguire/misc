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
 *      Example of the comma operator in Objective-C.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 24, 2025                                                *
 ******************************************************************************/
#import <Foundation/Foundation.h>

int main(void)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    /*  You can split one expression into several using the comma operator.   *
     *  Let's see an example.                                                 */
    int a, b, c;

    /*  The comma operator works left to right, returning the last entry in   *
     *  the sequence. So this will set b = 2, then set c = 3, and finally     *
     *  produce b + c. This value, b + c, is then assigned to a. Hence, a = 5.*/
    a = (b = 2, c = 3, b + c);

    /*  Print the results to the screen to see if our prediction is correct.  */
    NSLog(@"a = %i", a);
    NSLog(@"b = %i", b);
    NSLog(@"c = %i", c);

    /*  I'd argue the following is far more readable, even if it takes up two *
     *  more lines.                                                           */
    b = 2;
    c = 3;
    a = b + c;

    /*  The result will be the same.                                          */
    NSLog(@"a = %i", a);
    NSLog(@"b = %i", b);
    NSLog(@"c = %i", c);

    [pool drain];
    return 0;
}
