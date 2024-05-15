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
 *      Provides an example of using the Numpy C-API with the C-Python API.   *
 *      One function uses the Array API (the "max" function), and the other   *
 *      uses the Iterator API (the "cos" function).                           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       2024/05/15                                                    *
 ******************************************************************************/

/*  Numpy documentation recommends defining the following macro.              */
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

/*  Python API tools provided here.                                           */
#include <Python.h>

/*  Numpy C-API tools are found here.                                         */
#include <numpy/arrayobject.h>

/*  Standard header file with the cosine function.                            */
#include <math.h>

/*  This function is used to initialize the module.                           */
extern PyMODINIT_FUNC PyInit_mymodule(void);

/******************************************************************************
 *  Function:                                                                 *
 *      py_max:                                                               *
 *  Purpose:                                                                  *
 *      Computes the maximum of a numpy array object.                         *
 *  Arguments:                                                                *
 *      self (PyObject *):                                                    *
 *          Required argument for the C-Python API. It is not used here.      *
 *      args (PyObject *):                                                    *
 *          The arguments passed by the caller at the Python level.           *
 *  Output:                                                                   *
 *      maximum (PyObject *):                                                 *
 *          The maximum of the input array.                                   *
 *  Method:                                                                   *
 *      Extract the data from the Python level, loop over it and find the max.*
 *  Notes:                                                                    *
 *      1.) Numpy arrays are required. Any other Python type passed to this   *
 *          function will result in a PyErr telling the user the data type    *
 *          cannot be parsed. You can modify this function to accept various  *
 *          types of Python objects, but this is not done in this example.    *
 *      2.) The numpy array must contain data that can be parsed as double.   *
 *          If it cannot be parsed, an error will be raised for the caller.   *
 *      3.) This function uses the numpy Array API. The "cos" function        *
 *          below uses the Iterator API.                                      *
 ******************************************************************************/
static PyObject *
py_max(PyObject *self, PyObject *args)
{
    /*  The input argument. Should be a numpy array. We will try to parse     *
     *  this in a little bit.                                                 */
    PyArrayObject *arr;

    /*  A variable for indexing and a variable for the size of the array.     */
    npy_intp n, n_elements;

    /*  Variable specifying the type of the input data.                       */
    int typenum;

    /*  Variable for storing the maximum of the array.                        */
    double maximum;

    /*  Pointer to the data stored in the array, cast to double.              */
    const double *data;

    /*  Parse the input. It should be a numpy array. Check for this.          */
    if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &arr))
    {
        /*  Unable to parse the input. Abort with an error message.           */
        PyErr_Format(PyExc_RuntimeError, "Cannot parse input.");
        return NULL;
    }

    /*  If we get here we have a numpy array. Get the type of the data.       */
    typenum = PyArray_TYPE(arr);

    /*  We'll be returning a double array. Cast the input if necessary.       */
    if (typenum != NPY_DOUBLE)
    {
        /*  Numpy descriptor detailing a double array.                        */
        PyArray_Descr *descr = PyArray_DescrFromType(NPY_DOUBLE);

        /*  Create a new array from the old by casting to double.             */
        PyObject *pyarray = PyArray_FromArray(arr, descr, NPY_ARRAY_ALIGNED);

        /*  Cast to the numpy array type. This is a safe cast.                */
        PyArrayObject *tmp_array = (PyArrayObject *)pyarray;

        /*  Check that PyArray_FromArray did not return a NULL pointer.       */
        if (!tmp_array)
        {
            /*  We were unable to convert the data. Abort with an error.      */
            PyErr_Format(PyExc_RuntimeError, "Cannot cast data to float.");
            return NULL;
        }

        /*  Avoid memory leaks. Decrement the counter for arr.                */
        Py_DECREF(arr);

        /*  The temporary array has the input data cast to double. Use this.  */
        arr = tmp_array;
    }

    /*  This returns the total number of elements in the array. The           *
     *  dimensions of the array do not matter for this part.                  */
    n_elements = PyArray_SIZE(arr);

    /*  If the array is empty, return Not-A-Number.                           */
    if (!n_elements)
        return Py_BuildValue("d", (double)NAN);

    /*  Get a pointer to the data, cast to double.                            */
    data = PyArray_DATA(arr);

    /*  Start the computation. Set the maximum to the zeroth element.         */
    maximum = data[0];

    /*  Loop over the remaining elements and find the maximum.                */
    for (n = 1; n < n_elements; ++n)
        if (data[n] > maximum)
            maximum = data[n];

    /*  Create a Python object from the answer. This will be a float type at  *
     *  the Python level. "d" stands for "double."                            */
    return Py_BuildValue("d", maximum);
}
/*  End of py_max.                                                            */

/******************************************************************************
 *  Function:                                                                 *
 *      py_cos:                                                               *
 *  Purpose:                                                                  *
 *      Computes the cosine of a numpy array object.                          *
 *  Arguments:                                                                *
 *      self (PyObject *):                                                    *
 *          Required argument for the C-Python API. It is not used here.      *
 *      args (PyObject *):                                                    *
 *          The arguments passed by the caller at the Python level.           *
 *  Output:                                                                   *
 *      cos_arr (PyObject *):                                                 *
 *          The cosine of the input array.                                    *
 *  Method:                                                                   *
 *      Extract the data from the Python level, loop over it and compute.     *
 *  Notes:                                                                    *
 *      1.) Numpy arrays are required. Any other Python type passed to this   *
 *          function will result in a PyErr telling the user the data type    *
 *          cannot be parsed. You can modify this function to accept various  *
 *          types of Python objects, but this is not done in this example.    *
 *      2.) The numpy array must contain data that can be parsed as double.   *
 *          If it cannot be parsed, an error will be raised for the caller.   *
 *      3.) This function uses the Iterator API instead of the Array API.     *
 ******************************************************************************/
static PyObject *
py_cos(PyObject* self, PyObject* args)
{
    /*  Pointer for the input numpy array.                                    */
    PyArrayObject *in_array = NULL;

    /*  Output array, the new data is stored here.                            */
    PyObject *out_array = NULL;

    /*  Iterator for the input array.                                         */
    NpyIter *in_iter = NULL;

    /*  Iterator for the output array.                                        */
    NpyIter *out_iter = NULL;

    /*  Iterator function for the input array.                                */
    NpyIter_IterNextFunc *in_iternext = NULL;

    /*  Iterator function for the output array.                               */
    NpyIter_IterNextFunc *out_iternext = NULL;

    /*  Array descriptor for double arrays.                                   */
    PyArray_Descr *descr;

    /*  Pointers to the data for the input and output arrays, cast to double. */
    double **in_dataptr;
    double **out_dataptr;

    /*  Temporary pointers used for extracting data.                          */
    char **in_tmp;
    char **out_tmp;

    /*  Parse the input. It should be a numpy array. Check for this.          */
    if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &in_array))
    {
        /*  Cannot parse input. Abort the computation with an error.          */
        PyErr_Format(PyExc_RuntimeError, "Cannot parse input.");
        return NULL;
    }

    /*  Array descriptor for a double array.                                  */
    descr = PyArray_DescrFromType(NPY_DOUBLE);

    /*  Create the new array using the dimensions of the old one.             */
    out_array = PyArray_NewLikeArray(in_array, NPY_ANYORDER, descr, 0);

    /*  Check if this failed. out_array will be a NULL pointer in this case.  */
    if (!out_array)
    {
        PyErr_Format(PyExc_RuntimeError, "Could not create new array.");
        return NULL;
    }

    /*  Create the iterator for the input data. This needs copying and        *
     *  buffering permissions in case we need to cast to double.              */
    in_iter = NpyIter_New(
        in_array,
        NPY_ITER_READWRITE |
            NPY_ITER_BUFFERED |
            NPY_ITER_NBO |
            NPY_ITER_ALIGNED,
        NPY_KEEPORDER,
        NPY_UNSAFE_CASTING,
        descr
    );

    /*  Check if this failed. We'll have a NULL pointer if it did.            */
    if (!in_iter)
        goto FAILURE;

    /*  Same thing for the output array. No casting or copying needed here.   */
    out_iter = NpyIter_New(
        (PyArrayObject *)out_array,
        NPY_ITER_READWRITE,
        NPY_KEEPORDER,
        NPY_NO_CASTING,
        descr
    );

    /*  Same as before, check for failure.                                    */
    if (!out_iter)
        goto FAILURE;

    /*  Create the iterating functions from the two iterators.                */
    in_iternext = NpyIter_GetIterNext(in_iter, NULL);
    out_iternext = NpyIter_GetIterNext(out_iter, NULL);

    /*  Safety check, ensure we don't have any NULL pointers.                 */
    if (!in_iternext || !out_iternext)
        goto FAILURE;

    /*  We want the data represented as double array. First, get the data.    */
    in_tmp = NpyIter_GetDataPtrArray(in_iter);
    out_tmp = NpyIter_GetDataPtrArray(out_iter);

    /*  Cast the data to double. This is safe to do since the previous        *
     *  functions ensured the data is represented as doubles.                 */
    in_dataptr = (double **)in_tmp;
    out_dataptr = (double **)out_tmp;

    /*  Iterator over the array and perform the computation.                  */
    do {
        **out_dataptr = cos(**in_dataptr);

    /*  Increment to the next elements in the in and out arrays.              */
    } while(in_iternext(in_iter) && out_iternext(out_iter));

    /*  Clean up, avoiding memory leaks, and return the result.               */
    NpyIter_Deallocate(in_iter);
    NpyIter_Deallocate(out_iter);
    Py_INCREF(out_array);
    return out_array;

    /*  If we get here one of the routines returned NULL. Free memory and     *
     *  abort the computation.                                                */
FAILURE:
    if (in_iter)
        NpyIter_Deallocate(in_iter);

    if (out_iter)
        NpyIter_Deallocate(out_iter);

    Py_XDECREF(out_array);
    PyErr_Format(PyExc_RuntimeError, "Iterator API failed to create data.");
    return NULL;
}
/*  End of py_cos.                                                            */

/*  Definition of the functions / methods in the module.                      */
static PyMethodDef MyModuleMethods[] =
{
    {
        /*  Name of the function / method in the module.                      */
        "cos",

        /*  The C function associated to this.                                */
        py_cos,

        /*  Python API stuff. You generally don't need to worry about this.   */
        METH_VARARGS,

        /*  Description for the function. help(mymodule.cos) will print this. */
        "Computes the cosine of a numpy array."
    },

    /*  Same as before, but for the "max" function.                           */
    {
        "max",
        py_max,
        METH_VARARGS,
        "Computes the maximum of a numpy array."
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
 *  inside. If you do "import mymodule" you can then do "y = mymodule.cos(x)" *
 *  or "y = mymodule.max(x)".                                                 */
static struct PyModuleDef MyModuleDef =
{
    /*  Boilerplate stuff, part of the Python API.                            */
    PyModuleDef_HEAD_INIT,

    /*  The name of the module. This should match the PyMODINIT_FUNC          *
     *  function defined at the end of this file.                             */
    "mymodule",

    /*  Description of the module. Printed with help(mymodule).               */
    "Example module for using the C-Python and Numpy C APIs.",
    -1,

    /*  The methods defined for the module. Given above.                      */
    MyModuleMethods,

    /*  Python API stuff. You can ignore this.                                */
    NULL,
    NULL,
    NULL,
    NULL
};

/*  Function for initializing the module.                                     */
PyMODINIT_FUNC PyInit_mymodule(void)
{
    /*  Very important. This function must be called for the numpy API to     *
     *  work properly. Failure to do this may result in crashes.              */
    import_array();
    return PyModule_Create(&MyModuleDef);
}
/*  End of PyInit_mymodule.                                                   */
