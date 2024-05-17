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
 *      Shows how to use C code in the D programming language. In particular, *
 *      a very small wrapper is provided for libtmpl's complex and vector     *
 *      structs and example code is given.                                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 29, 2024                                              *
 ******************************************************************************/
import std.stdio : writeln;

/*  Direct translation of the libtmpl complex struct to D.                    */
struct tmpl_ComplexDouble {
    double[2] dat;
};

/*  Same translation for the Vec3 struct provided by libtmpl.                 */
struct tmpl_ThreeVectorDouble {
    double[3] dat;
};

/*  libtmpl is written in C, so we need to let the D compiler know that.      */
extern (C) {
    /*  Computes the modulus of a complex number.                             */
    double tmpl_CDouble_Abs(tmpl_ComplexDouble z);

    /*  Creates a complex number of the form z = x + iy.                      */
    tmpl_ComplexDouble tmpl_CDouble_Rect(double x, double y);

    /*  Creates a 3D vector from its Cartesian, or rectangular, coordinates.  */
    tmpl_ThreeVectorDouble tmpl_3DDouble_Rect(double x, double y, double z);

    /*  Computes the length, or magnitude, or Euclidean norm, of a vector.    */
    double tmpl_3DDouble_L2_Norm(tmpl_ThreeVectorDouble *v);
}

/*  Simple test of the libtmpl routines.                                      */
void main()
{
    tmpl_ThreeVectorDouble v = tmpl_3DDouble_Rect(1.0, 1.0, 1.0);
    tmpl_ComplexDouble z = tmpl_CDouble_Rect(1.0, 1.0);

    /*  Should be sqrt(2) ~= 1.414...                                         */
    double magz = tmpl_CDouble_Abs(z);

    /*  Should be sqrt(3) ~= 1.732...                                         */
    double magv = tmpl_3DDouble_L2_Norm(&v);

    /*  Print the results to the screen and conclude this example.            */
    writeln(magz);
    writeln(magv);
}
