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
 *      Shows how to use channels in Go.                                      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 9, 2026                                                 *
 ******************************************************************************/
package main

import (
    "fmt"
    "time"
)

func workerWithNoSleep() {

    /*  Create a channel, we'll use this to wait for the go routine to finish.*/
    var channel chan struct{} = make(chan struct{}, 0)

    /*  Start a background worker function to test using the channel.         */
    go func() {

        /*  Print something so we can see what triggers first, this go        *
         *  routine, or the print statement in the main part of this function.*/
        fmt.Println("Worker: Working...")

        /*  This function doesn't do any actual work, it just sleeps a bit.   */
        time.Sleep(2 * time.Second)

        /*  The "work" (that is, taking a nap) is done, print this.           */
        fmt.Println("Worker: Done!")

        /*  Send the signal to the channel that this worker is done.          */
        channel <- struct{}{}
    }()

    /*  Print something from the main part of this function.                  */
    fmt.Println("workerWithNoSleep: Function has started...")

    /*  Wait for the go routine to finish.                                    */
    <- channel

    /*  Print a message indicating the go routine is done.                    */
    fmt.Println("workerWithNoSleep: Function is done!")
}

func workerWithSleep() {

    /*  Same setup as before, create a channel and a go routine.              */
    var channel chan struct{} = make(chan struct{}, 0)

    go func() {

        fmt.Println("Worker: Working...")
        time.Sleep(2 * time.Second)
        fmt.Println("Worker: Done!")
        channel <- struct{}{}
    }()

    /*  First, sleep for a bit, see if this helps the go routine finish first.*/
    time.Sleep(2 * time.Second)

    /*  Print something from the main part of this function.                  */
    fmt.Println("workerWithSleep: Function has started...")

    /*  Wait for the go routine to finish.                                    */
    <- channel

    /*  Print a message indicating the go routine is done.                    */
    fmt.Println("workerWithSleep: Function is done!")
}

func main() {
    fmt.Println("Main: Trying workerWithNoSleep first...\n")
    workerWithNoSleep()

    fmt.Println("\nMain: Now trying workerWithSleep...\n")
    workerWithSleep()
}
