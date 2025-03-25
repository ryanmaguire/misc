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
 *      Shows how to use Boolean types in Objective-C.                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 24, 2025                                                *
 ******************************************************************************/
#import <Foundation/Foundation.h>

/*  The "Boolean" type has been depcrated. Give it a typedef for this example.*/
typedef unsigned char Boolean;
const Boolean False = 0x00U;
const Boolean True = 0x01U;

int main(void)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    /*  Old version of Booleans, stems from the Mac OS X Carbon API. It is    *
     *  defined as an unsigned char. Deprecated and no longer part of the     *
     *  language, which is why we typedef'd it above.                         */
    Boolean oldBool = True;

    /*  The C way of doing it, introduced in the C99 standard.                */
    bool cBool = true;

    /*  The Objective-C method, which is a signed char.                       */
    BOOL newBool = YES;

    NSLog(oldBool ? @"oldBool = True" : @"oldBool = False");
    NSLog(cBool ? @"cBool   = true" : @"cBool   = false");
    NSLog(newBool ? @"newBool = YES" : @"newBool = NO");

    [pool drain];
    return 0;
}
