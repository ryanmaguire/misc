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
 *      Simple test of using OpenMP to parallelize things.                    *
 ******************************************************************************/

/*  Basic input/output. printf provided here.                                 */
#include <stdio.h>

/*  OpenMP utilities provided here. Not part of the standard library.         */
#include <omp.h>

/*  Function for testing some of the OpenMP routines.                         */
int main(void)
{
    puts("Now testing OpenMP:\n");

#pragma omp parallel
    printf(
        "Hello from thread %d, nthreads %d\n",
        omp_get_thread_num(), omp_get_num_threads()
    );

    return 0;
}
/*  End of main.                                                              */
