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
 *      Example of assignment operators with integers in Objective-C.         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 24, 2025                                                *
 ******************************************************************************/
#import <Foundation/Foundation.h>

int main(void)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    /*  The variables we will be playing with.                                */
    const int a = 2;
    const int b = 3;

    /*  We are going to update "c" using assignment operators. We cannot      *
     *  declare it as a "const" because of this.                              */
    int c;

    /*  Tell the user what we're working with. Print the values.              */
    NSLog(@"a = %i", a);
    NSLog(@"b = %i", b);

    /*  Start off by computing a sum and printing the result.                 */
    c = a + b;
    NSLog(@"c = a + b = %i", c);

    /*  Scale c by a and print the new result.                                */
    c *= a;
    NSLog(@"c *= a -> c = %i", c);

    /*  We can use bitwise operators too. Shift c update by 3.                */
    c <<= 3;
    NSLog(@"c <<= 3 -> c = %i", c);

    [pool drain];
    return 0;
}
