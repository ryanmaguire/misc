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
 *      Example of using pointers in Objective-C.                             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 26, 2025                                                *
 ******************************************************************************/
#import <Foundation/Foundation.h>

int main(void)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    /*  Create an integer and create a pointer to the integer as well.        */
    const int anInteger = 5;
    const int * const pointerToAnInteger = &anInteger;

    /*  We can print both the address and the value of anInteger.             */
    NSLog(@"Address of anInteger = %p", pointerToAnInteger);
    NSLog(@"Value of anInteger   = %i", *pointerToAnInteger);

    [pool drain];
    return 0;
}
