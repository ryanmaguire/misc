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
 *      Mounts all necessary things so that a chroot can use commands like    *
 *      lscpu. Useful when using QEMU to emulate various architectures like   *
 *      mips or ppc.                                                          *
 ******************************************************************************/

/*  sprintf and puts are here.                                                */
#include <stdio.h>

/*  system is here.                                                           */
#include <stdlib.h>

/*  Function for chroot-ing into an emulated system.                          */
int main(int argc, char *argv[])
{
    /*  Array for storing the command later.                                  */
    char arg1[256], arg2[256], arg3[256];
    int val;

    /*  Check for bad inputs.                                                 */
    if (argc != 3)
    {
        puts("You must supply a string an an integer");
        puts("Example: chrootmount MIPS 0");
        puts("0 for unmounting, 1 for mounting");
        return -1;
    }

    /*  Read in the user-provided value and convert it to an int with atod.   */
    val = atoi(argv[2]);

    /*  Check that the input was legal.                                       */
    if (val != 0 && val != 1)
    {
        /*  Display error message and exit.                                   */
        puts("The number needs to be between 0 or 1");
        puts("0 for unmounting, 1 for mounting");
        return -1;
    }

    /*  Create the argument being passed to "system" with sprintf.            */
    if (val == 1)
    {
        sprintf(arg1, "sudo mount --bind /dev/ %s/dev/", argv[1]);
        sprintf(arg2, "sudo mount --bind /sys/ %s/sys/", argv[1]);
        sprintf(arg3, "sudo mount --bind /proc/ %s/proc/", argv[1]);
    }

    /*  These are the unmounting commands for when chroot is finished.        */
    else
    {
        sprintf(arg1, "sudo umount %s/dev/", argv[1]);
        sprintf(arg2, "sudo umount %s/sys/", argv[1]);
        sprintf(arg3, "sudo umount %s/proc/", argv[1]);
    }

    /*  Run the command and return.                                           */
    system(arg1);
    system(arg2);
    system(arg3);
    return 0;
}
/*  End of main.                                                              */

