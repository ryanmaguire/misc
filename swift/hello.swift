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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 8, 2023                                               *
 ******************************************************************************/

/*  sqrt function is provided here. Different import for macOS vs. Linux.     */
#if canImport(Darwin)
import Darwin
#elseif canImport(Glibc)
import Glibc
#else
import Foundation
#endif

/*  Function for printing a simple message. Demonstrates basic syntax.        */
func myPrintFunction(x: Double) -> String {

    /*  The sqrt function is imported from the C standard library above.      */
    let y: Double = sqrt(x)

    /*  Triple-quotes allow for line-continuation and implicit newlines.      */
    return """
        \rHello, World!
        \rsqrt(\(x)) = \(y)
    """
}
/*  End of myPrintFunction.                                                   */

/*  The input to the function.                                                */
let input: Double = 2.0

/*  The output. Pass the input to the function.                               */
let output: String = myPrintFunction(x: input)

/*  The print function appends a newline automatically.                       */
print(output)
