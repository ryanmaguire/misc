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
 *      Example of ternary expressions and logical operations in Objective-C. *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 26, 2025                                                *
 ******************************************************************************/
#import <Foundation/Foundation.h>

int main(void)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    /*  The ints we'll work with.                                             */
    const int a = 5;
    const int b = 6;
    const int c = 3;

    /*  Create Booleans from the three ints. These are ternary expressions.   */
    const BOOL firstLessThanSecond = (a < b ? YES : NO);
    const BOOL firstLessThanThird = (a < c ? YES : NO);

    /*  Logical and can be used to check if a is the smallest.                */
    const BOOL firstIsSmallest = (firstLessThanSecond && firstLessThanThird);

    /*  Logical or can be used to check if a is not the largest.              */
    const BOOL firstIsNotLargest = (firstLessThanSecond || firstLessThanThird);

    /*  We can prove the truth values of these Booleans using if-else.        */
    if (firstIsSmallest)
        NSLog(@"a is the smallest integer");
    else
        NSLog(@"a is not the smallest integer");

    if (firstIsNotLargest)
        NSLog(@"a is not the largest integer");
    else
        NSLog(@"a is the largest integer");

    [pool drain];
    return 0;
}
