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
 *      Shows how to use if-then statements in Objective-C.                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 25, 2025                                                *
 ******************************************************************************/
#import <Foundation/Foundation.h>

int main(void)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    /*  The ints we'll work with.                                             */
    const int a = 5;
    const int b = 6;

    /*  Create Booleans from the two ints.                                    */
    const BOOL intsAreEqual = (a == b);
    const BOOL firstIsLessThenSecond = (a < b);

    /*  Use if-else to probe the truth of the intsAreEqual Boolean.           */
    if (intsAreEqual)
        NSLog(@"a and b are equal.");
    else
        NSLog(@"a and b are not equal.");

    /*  Similarly, check the second Boolean.                                  */
    if (firstIsLessThenSecond)
        NSLog(@"a is less than b.");

    [pool drain];
    return 0;
}
