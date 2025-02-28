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
 *	    Simple program using OpenGL to render a rotating sphere.              *
 *      Linker arguments: -lGL -lGLU -lglut
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 28, 2025                                             *
 ******************************************************************************/
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

/*  Rotation angle for the sphere.                                            */
static float angle = 0.0F;

/*  Parameters for the sphere. It is a wire-sphere consisting of 32 latitute  *
 *  and 32 longitude lines (or "wires").                                      */
static const double radius = 1.0;
static const int number_of_slices = 32;
static const int number_of_stacks = 32;

/*  Parameters for the perspective of the image.                              */
static const double fov_angle = 45.0;
static const double z_near = 0.01;
static const double z_far = 100.0;

/*  Vector describing the plane of rotation.                                  */
static const float x_rot = 1.0F;
static const float y_rot = 1.0F;
static const float z_rot = 0.0F;

/*  Shift factor for the sphere. This places the camera on the outside.       */
static const double z_shift = -5.0;

/*  Parameters for the display window.                                        */
static const int display_width = 3840;
static const int display_height = 2160;

/*  Number of milliseconds between frames. Aiming for 60 FPS.                 */
static const int frequency = 16;

/*  Function used for initializing OpenGL settings.                           */
static void initOpenGL()
{
    /*  Set the background color to black, RGB value is (0, 0, 0). Alpha      *
     *  value 1 means opaque.                                                 */
    glClearColor(0.0, 0.0, 0.0, 1.0);

    /*  Enable depth testing for 3D rendering. See:                           *
     *      https://www.khronos.org/opengl/wiki/Depth_Test                    *
     *  for more details.                                                     */
    glEnable(GL_DEPTH_TEST);
}

/*  Function to set up the perspective and the camera.                        */
static void reshape(int width, int height)
{
    /*  Aspect ratio for the screen is the ratio of the lengths.              */
    const double aspect_ratio = (double)width / (double)height;

    /*  Set the viewport to the entirety of the window.                       */
    glViewport(0, 0, width, height);

    /*  Set the projection matrix.                                            */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /*  Set the perspective view.                                             */
    gluPerspective(fov_angle, aspect_ratio, z_near, z_far);

    /*  Switch back to the modelview matrix.                                  */
    glMatrixMode(GL_MODELVIEW);
}

/*  Function to render the sphere.                                            */
static void display()
{
    /*  Clear the color and depth buffers.                                    */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*  Reset transformations and move the sphere back so we're not inside it.*/
    glLoadIdentity();
    glTranslatef(0.0, 0.0, z_shift);

    /*  Rotate the sphere based on the current angle.                         */
    glRotatef(angle, x_rot, y_rot, z_rot);

    /*  Draw the sphere.                                                      */
    glutWireSphere(radius,  number_of_slices, number_of_stacks);

    /*  Swap the front and back buffers for a smooth animation. See:          *
     *      https://www.opengl.org/resources/libraries/glut/spec3/node21.html *
     *  for more details.                                                     */
    glutSwapBuffers();
}

/*  Function to update the rotation angle for animation.                      */
static void update(int update_value)
{
    /*  Update the angle of the sphere for the next frame.                    */
    angle += 1.0F;

    /*  Keep the rotation angle to with [0, 360). Decrement if necessary.     */
    if (angle > 360.0F)
        angle -= 360.0F;

    /*  Request a redraw.                                                     */
    glutPostRedisplay();

    /*  60 FPS is about one frame every 16 milliseconds. Call this function   *
     *  at this frequency while rendering.                                    */
    glutTimerFunc(frequency, update, 0);
}

/*  Main routine for rendering the sphere to the screen.                      */
int main(int argc, char **argv)
{
    /*  Initialize GLUT.                                                      */
    glutInit(&argc, argv);

    /*  Set the display mode. Double buffered RGB with alpha compositing.     */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    /*  Set the window size, 4k is 3840x2160.                                 */
    glutInitWindowSize(display_width, display_height);

    /*  Give the generated window a name.                                     */
    glutCreateWindow("Rotating Sphere");

    /*  Initialize OpenGL with current settings.                              */
    initOpenGL();

    /*  Tell glut and OpenGL what function is used for drawing.               */
    glutDisplayFunc(display);

    /*  Register the reshape function.                                        */
    glutReshapeFunc(reshape);

    /*  Start the timer, 16 milliseconds is 60 frames per second.             */
    glutTimerFunc(frequency, update, 0);

    /*  Start the animation.                                                  */
    glutMainLoop();

    /*  The animation should run until the user closes it. After that, the    *
     *  program finishes.                                                     */
    return 0;
}
