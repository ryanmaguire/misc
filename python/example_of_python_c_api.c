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
 *      Provides an example of using the C-Python API.                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       2024/05/15                                                    *
 ******************************************************************************/

/*  The C-Python API is provided here.                                        */
#include <Python.h>

/*  This function is used to initialize the module.                           */
extern PyMODINIT_FUNC PyInit_fibonacci(void);

/******************************************************************************
 *  Function:                                                                 *
 *      fibonacci                                                             *
 *  Purpose:                                                                  *
 *      Computes the nth Fibonacci number using the power method.             *
 *  Arguments:                                                                *
 *      n (unsigned long int):                                                *
 *          An integer. The index of the Fibonacci number we want.            *
 *  Output:                                                                   *
 *      fib_n (unsigned long int):                                            *
 *          The nth Fibonacci number.                                         *
 *  Method:                                                                   *
 *      Use the power method. This runs in O(log(n)) time. The standard       *
 *      iterative method runs in O(n) and the recursive definition requires   *
 *      O(2^n). Let's derive it. We have:                                     *
 *                                                                            *
 *          F_{n+2} = F_{n+1} + F_{n}                                         *
 *                                                                            *
 *      Propose a power solution of the form F_{n} = A * a^n. The difference  *
 *      equation is linear, so a linear combination of solutions will again   *
 *      be a solution. Substituting, we get:                                  *
 *                                                                            *
 *          A * a^{n+2} = A * a^{n+1} + A * a^n                               *
 *                                                                            *
 *      Simplifying, we have:                                                 *
 *                                                                            *
 *          a^{2} = a + 1                                                     *
 *                                                                            *
 *      The solutions are:                                                    *
 *                                                                            *
 *          a_{-} = (1 - sqrt(5)) / 2                                         *
 *          a_{+} = (1 + sqrt(5)) / 2                                         *
 *                                                                            *
 *      The golden ratio, and the "anti" golden ratio. The general solution   *
 *      is then:                                                              *
 *                                                                            *
 *          F_{n} = A a_{-}^n + B a_{+}^n                                     *
 *                                                                            *
 *      Using F_{0} = 0 and F_{1} = 1 we can explicitly solve for A and B.    *
 *                                                                            *
 *          A = -1 / sqrt(5)                                                  *
 *          B = +1 / sqrt(5)                                                  *
 *                                                                            *
 *      We use this formula to compute F_{n}.                                 *
 *  Notes:                                                                    *
 *      Floating point error can lead to incorrect values for large n. The    *
 *      relative error should be within epsilon for long double. For 64-bit   *
 *      integers, and with 80-bit extended precision, this gets the correct   *
 *      number for n < 85, and within 2^-60 for n < 94. For larger n the      *
 *      corresponding Fibonacci number goes beyond the bounds of 64-bit       *
 *      integers and zero is returned.                                        *
 ******************************************************************************/
static unsigned long int fibonacci(unsigned long int n)
{
    /*  The anti-golden ratio, (1 - sqrt(5)) / 2.                             */
    const long double FIBO_A = -6.180339887498948482045868343656381177203E-01L;

    /*  The golden ratio, (1 + sqrt(5)) / 2.                                  */
    const long double FIBO_B = +1.618033988749894848204586834365638117720E+00L;

    /*  Coefficients for the power method. +/- 1 / sqrt(5).                   */
    const long double FIBO_C = -4.472135954999579392818347337462552470881E-01L;
    const long double FIBO_D = +4.472135954999579392818347337462552470881E-01L;

    /*  Variables for computing the powers via exponentiation by squaring.    */
    long double fibo_ax, fibo_ay, fibo_bx, fibo_by;

    /*  Special cases, for n < 2 we can just return the input.                */
    if (n < 2UL)
        return n;

    /*  We compute a_{-}^n and a_{+}^n using exponentiation by squaring. We   *
     *  start the computation with a_{-} and a_{+}, the golden ratios.        */
    fibo_ax = FIBO_A;
    fibo_bx = FIBO_B;
    fibo_ay = 1.0L;
    fibo_by = 1.0L;

    /*  Compute a_{-}^n and a_{+}^n by repeated squaring.                     */
    while (n > 1UL)
    {
        /*  If n is odd write x^{2k+1} = x^{2k} * x = (x^2)^k * x. We         *
         *  multiply by x, and then compute a square. This roughly halves     *
         *  n meaning we need about log(n), instead of n, multiplications.    *
         *  We do this for x = a_{-} and x = a_{+}.                           */
        if (n & 0x01U)
        {
            fibo_ay *= fibo_ax;
            fibo_by *= fibo_bx;

            /*  After decrementing, n will be even.                           */
            --n;
        }

        /*  n is now even. Compute x^{2k} = (x^2)^k. Compute the squares      */
        fibo_ax *= fibo_ax;
        fibo_bx *= fibo_bx;

        /*  Having squared the values, we can cut n in half.                  */
        n >>= 1UL;
    }

    /*  Final multiplication for the power computation.                       */
    fibo_ax *= fibo_ay;
    fibo_bx *= fibo_by;

    /*  Get the correctly rounded value by shifting by 0.5 and casting.       */
    return (unsigned long int)(0.5L + fibo_ax*FIBO_C + fibo_bx*FIBO_D);
}
/*  End of fibonacci.                                                         */

/******************************************************************************
 *  Function:                                                                 *
 *      py_fibonacci:                                                         *
 *  Purpose:                                                                  *
 *      Computes the nth Fibonacci number.                                    *
 *  Arguments:                                                                *
 *      self (PyObject *):                                                    *
 *          Required argument for the C-Python API. It is not used here.      *
 *      args (PyObject *):                                                    *
 *          The arguments passed by the caller at the Python level.           *
 *  Output:                                                                   *
 *      fib_n (PyObject *):                                                   *
 *          The nth Fibonacci number.                                         *
 *  Method:                                                                   *
 *      Extract the data from the Python level and pass it to the C function. *
 ******************************************************************************/
static PyObject *py_fibonacci(PyObject* self, PyObject* args)
{
    /*  Variable for the input. We'll parse the Python argument and attempt   *
     *  to store it in this variable.                                         */
    unsigned long int n;

    /*  Parse the input. It should be represented as an integer.              */
    if (!PyArg_ParseTuple(args, "k", &n))
    {
        /*  Unable to parse the input. Abort with an error message.           */
        PyErr_Format(PyExc_RuntimeError, "Cannot parse input.");
        return NULL;
    }

    /*  Pass the argument to the C function and return it as a Python object. */
    return Py_BuildValue("k", fibonacci(n));
}
/*  End of py_fibonacci.                                                      */

/*  Definition of the functions / methods in the module.                      */
static PyMethodDef FibonacciMethods[] =
{
    {
        /*  Name of the function / method in the module.                      */
        "fibonacci",

        /*  The C function associated to this.                                */
        py_fibonacci,

        /*  Python API stuff. You generally don't need to worry about this.   */
        METH_VARARGS,

        /*  Function description. help(fibonacci.fibonacci) prints this.      */
        "Computes the nth Fibonacci number."
    },

    /*  More Python API stuff. You can ignore this.                           */
    {
        NULL,
        NULL,
        0,
        NULL
    }
};

/*  The definition of the Python module. These are the functions contained    *
 *  inside. If you do "import mymodule" you can then use "mymodule.fibonacci".*/
static struct PyModuleDef FibonacciModuleDef =
{
    /*  Boilerplate stuff, part of the Python API.                            */
    PyModuleDef_HEAD_INIT,

    /*  The name of the module. This should match the PyMODINIT_FUNC          *
     *  function defined at the end of this file.                             */
    "fibonacci",

    /*  Description of the module. Printed with help(fibonacci).              */
    "Example module for using the C-Python API.",
    -1,

    /*  The methods defined for the module. Given above.                      */
    FibonacciMethods,

    /*  Python API stuff. You can ignore this.                                */
    NULL,
    NULL,
    NULL,
    NULL
};

/*  Function for initializing the module.                                     */
PyMODINIT_FUNC PyInit_fibonacci(void)
{
    return PyModule_Create(&FibonacciModuleDef);
}
