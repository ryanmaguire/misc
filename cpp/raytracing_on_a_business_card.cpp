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
 *      Detailed and expanded version of the famous raytracer on a bussiness  *
 *      card. This does not fit on a bussiness card, but hopefully it is      *
 *      more readable.                                                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       2021                                                          *
 ******************************************************************************/
#include <cstdlib>
#include <cstdio>
#include <cmath>

// Define a vector class with constructor and operator: 'v'
struct vector
{
    float x;
    float y;
    float z;

    vector operator+(vector r)
    {
        return vector(x+r.x,y+r.y,z+r.z);
    }

    vector operator*(float r)
    {
        return vector(x*r,y*r,z*r);
    }

    // Dot product.
    float operator%(vector r)
    {
        return x*r.x+y*r.y+z*r.z;
    }

    // Empty constructor
    vector (void){}

    // Cross-product
    vector operator^(vector r){
        return vector(y*r.z-z*r.y,z*r.x-x*r.z,x*r.y-y*r.x);
    }

    // Constructor
    vector(float a, float b, float c)
    {
        x=a;
        y=b;
        z=c;
    }

    // Used later for normalizing
    vector operator!(void)
    {
        return *this*(1.0F / sqrtf(*this%*this));
    }
};

/*  Initials
 *  Binary              Decimal
 *  ---------------------------
 *  111100111110000000  249728
 *  100100001000000000  147968
 *  101000001001000001  164417
 *  110000001001100011  197219
 *  101000001001010101  164437
 *  100100001001001001  148041
 *  100010001001000001  139841
 *  001000001001000001   33345
 *  001111111000000000   65024
 */

static const int initial_spheres[] = {
    65024, 33345, 139841, 148041, 164437, 197219, 164417, 147968, 249728
};

static float frand(void)
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

// The intersection test for line [o,v].
// Return 2 if a hit was found (and also return distance t and bouncing ray n).
// Return 0 if no hit was found but ray goes upward
// Return 1 if no hit was found but ray goes downward
static int Tracer(vector o, vector d, float& t, vector& n)
{
    int k, j;
    float s, b, c, q;
    vector P;
    t=1e9;
    int m=0;
    float p = -o.z/d.z;
    if (0.01F < p)
    {
        t = p;
        n = vector(0,0,1);
        m = 1;
    }

    // The world is encoded in initial_spheres, with 9 lines and 19 columns

    // For each columns of objects
    for (k = 19; k--;)
    {
        // For each line on that columns
        for (j = 9; j--;)
        {
            // For this line j, is there a sphere at column i ?
            if (initial_spheres[j] & 1 << k)
            {
                // There is a sphere but does the ray hits it ?
                const float x = static_cast<float>(-k);
                const float y = 0.0F;
                const float z = static_cast<float>(-j - 4);
                P = o + vector(x, y, z);

                b = P%d;
                c = P%P-1;
                q = b*b-c;

                // Does the ray hit the sphere ?
                if(q>0)
                {
                    // It does, compute the distance camera-sphere
                    s = -b - sqrtf(q);

                    // So far this is the minimum distance, save it. And also
                    // compute the bouncing ray vector into 'n'
                    if(s < t && s > 0.01F)
                    {
                        t = s;
                        n = !(P + d*t);
                        m = 2;
                    }
                }
            }
        }
    }

    return m;
}

// (S)ample the world and return the pixel color for
// a ray passing by point o (Origin) and d (Direction)
static vector Shader(vector o, vector d)
{
    float t;
    vector n;
    float b, p;

    // Search for an intersection ray Vs World.
    int m = Tracer(o, d, t, n);

    // No sphere found and the ray goes upward: Generate a sky color.
    if (m == 0)
        return vector(0.7F, 0.6F, 1.0F) * powf(1.0F - d.z, 4.0F);

    // A sphere was maybe hit.

    // h = intersection coordinate
    vector h = o + d*t;

    // 'l' = direction to light (random delta for shadows).
    vector l = !(vector(9 + frand(), 9+frand(), 16) + h*-1);

    // r = The half-vector
    vector r = d + n*(n%d*-2);

    // Calculated the lambertian factor
    b = l%n;

    // Calculate illumination factor (lambertian coefficient > 0 or in shadow)?
    if (b<0 || Tracer(h,l,t,n))
        b=0;

    // Calculate the color 'p' with diffuse and specular component
    p = powf(l % r * (b>0), 99.0F);

    // m == 1
    if (m & 1)
    {
        // No sphere was hit and the ray was going downward.
        // Generate a floor color.
        h = h*0.2F;
        if (static_cast<int>(ceilf(h.x) + ceilf(h.y)) & 1)
            return vector(3.0F, 1.0F, 1.0F)*(b*0.2F + 0.1F);

        else
            return vector(3.0F, 3.0F, 3.0F)*(b*0.2F + 0.1F);
    }

    // m == 2 A sphere was hit.
    // Cast an ray bouncing from the sphere surface.
    // Attenuate color by 50% since it is bouncing (* .5)
    return vector(p, p, p) + Shader(h,r)*.5;
}

static void color(vector p, FILE *fp)
{
    int x = static_cast<int>(p.x);
    int y = static_cast<int>(p.y);
    int z = static_cast<int>(p.z);
    fprintf(fp, "%c%c%c", x, y, z);

}

// The main function. It generates a PPM image to stdout.
// Usage of the program is hence: ./card > erk.ppm
int main(void)
{
    // The '!' are for normalizing each vectors with ! operator.
    FILE *fp = fopen("ray.ppm", "w");

    // Camera direction
    vector g = !vector(-6.0F, -16.0F, 0.0F);

    // Camera up vector... Seem Z is pointing up :/ WTF !
    vector a = !(vector(0.0F, 0.0F, 1.0F) ^ g) * 0.002F;

    // The right vector, obtained via traditional cross-product
    vector b = !(g ^ a) * 0.002F;

    // WTF ? See https://news.ycombinator.com/item?id=6425965.
    vector c=(a+b)*-256+g;

    int x, y, r;
    vector p, t;

    // The PPM Header is issued
    fprintf(fp, "P6\n512 512\n255\n");

    //For each column
    for (y = 512; y--;)
    {
        // For each pixel in a line
        for (x = 512; x--;)
        {
            // Reuse the vector class to store not XYZ but a RGB pixel color
            p = vector(13, 13, 13);

            // Cast 64 rays per pixel (For blur (stochastic sampling)
            // and soft-shadows.
            for (r = 64; r--;)
            {
                // The delta to apply to the origin of the view
                // (For Depth of View blur).

                // A little bit of delta
                t = a*(frand() - 0.5F)*99.0F + b*(frand() - 0.5F)*99.0F;

                // Set the camera focal point v(17,16,8) and Cast the ray
                // Accumulate the color returned in the p variable
                p = Shader(
                    // Ray Origin
                    vector(17.0F, 16.0F, 8.0F) + t,

                    // Ray Direction with random deltas for stochastic sampling
                    !(t * -1.0F + (
                        a*(frand() + static_cast<float>(x)) +
                        b*(frand() + static_cast<float>(y)) + c)*16.0F
                    )
                // +p for color accumulation
                ) * 3.5F + p;
            }

            color(p, fp);
        }
    }
}
