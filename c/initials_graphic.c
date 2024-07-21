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
 *      Modification of the famous raytracer on a business card. Uses         *
 *      libtmpl to handle all of the vector arithmetic and mathematics.       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       2021                                                          *
 ******************************************************************************/
#include <libtmpl/include/tmpl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
 *  TODO:
 *      Clean up this absolute trainwreck.
 */

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

static double random_unit_interval(void)
{
    const int n_rand = rand();
    return (double)n_rand / (double)RAND_MAX;
}

static const int G[9] = {
    65024, 33345, 139841, 148041, 164437, 197219, 164417, 147968, 249728
};

static int
Tracer(const tmpl_ThreeVectorDouble * const o,
       const tmpl_ThreeVectorDouble * const d,
       double * const t,
       tmpl_ThreeVectorDouble * const n)
{
    int k, j;
    double s, b, c, q;
    tmpl_ThreeVectorDouble P, temp;

    double o_z = tmpl_3DDouble_Z(o);
    double d_z = tmpl_3DDouble_Z(d);
    int m = 0;
    double p = -o_z / d_z;

    *t = 1.0E9;
    m = 0;
    p = - o_z/d_z;

    if (p > 0.01)
    {
        *t = p;
        *n = tmpl_3DDouble_Rect(0.0, 0.0, 1.0);
        m = 1;
    }

    for (k = 0; k < 18; ++k)
    {
        for (j = 0; j < 9; ++j)
        {
            if (G[j] & (1 << k))
            {
                temp = tmpl_3DDouble_Rect(-k, 0.0, -j-4);
                P = tmpl_3DDouble_Add(o, &temp);
                b = tmpl_3DDouble_Dot_Product(&P, d);
                c = tmpl_3DDouble_Dot_Product(&P, &P) - 1.0;
                q = b*b - c;

                if (q > 0.0)
                {
                    s = -b - tmpl_Double_Sqrt(q);

                    if ((s<*t) && (s > 0.01))
                    {
                        *t = s;
                        temp = tmpl_3DDouble_Scale(*t, d);
                        temp = tmpl_3DDouble_Add(&P, &temp);
                        *n = tmpl_3DDouble_Normalize(&temp);
                        m = 2;
                    }
                }
            }
        }
    }

    return m;
}

static tmpl_ThreeVectorDouble
Shader(const tmpl_ThreeVectorDouble * const o,
       const tmpl_ThreeVectorDouble * const d)
{
    double t, b, p, factor, d_z, h_x, h_y;
    tmpl_ThreeVectorDouble n, h, temp, l, r, shade;
    int m;

    /*  Initialize variables.                                                 */
    t = 0.0;
    n = tmpl_3DDouble_Zero;

    m = Tracer(o, d, &t, &n);
    d_z = tmpl_3DDouble_Z(d);

    if (m == 0)
    {
        factor = d_z*d_z;
        factor = factor*factor;
        shade = tmpl_3DDouble_Rect(1.0-factor, 0.7, 1.0);
        return shade;
    }

    temp = tmpl_3DDouble_Scale(t, d);
    h = tmpl_3DDouble_Add(o, &temp);

    temp = tmpl_3DDouble_Rect(
        9.0 + 5*random_unit_interval(),
        9.0 + 5*random_unit_interval(),
        46.0
    );

    tmpl_3DDouble_Scaled_AddTo(&temp, -1.0, &h);
    l = tmpl_3DDouble_Normalize(&temp);

    factor = -2.0*tmpl_3DDouble_Dot_Product(&n, d);
    temp = tmpl_3DDouble_Scale(factor, &n);
    r = tmpl_3DDouble_Add(d, &temp);
    b = tmpl_3DDouble_Dot_Product(&l, &n);

    if ((b<0.0) || Tracer(&h, &l, &t, &n))
        b = 0.0;

    if (b > 0)
        p = pow(tmpl_3DDouble_Dot_Product(&l, &r), 99.0);
    else
        p = 0.0;

    if (m == 1)
    {
        tmpl_3DDouble_ScaleBy(&h, 0.2);
        h_x = ceil(tmpl_3DDouble_X(&h));
        h_y = ceil(tmpl_3DDouble_Y(&h));

        if (((int)h_x + (int)h_y) & 1)
        {
            temp = tmpl_3DDouble_Rect(3.0, 1.0, 1.0);
            factor = 0.2*b + 0.1;
            shade = tmpl_3DDouble_Scale(factor, &temp);
            return shade;
        }

        else
        {
            temp = tmpl_3DDouble_Rect(3.0, 3.0, 3.0);
            factor = 0.2*b + 0.1;
            shade = tmpl_3DDouble_Scale(factor, &temp);
            return shade;
        }
    }

    temp = tmpl_3DDouble_Rect(p, p, p);
    shade = Shader(&h, &r);
    tmpl_3DDouble_ScaleBy(&shade, 0.5);
    tmpl_3DDouble_AddTo(&shade, &temp);
    return shade;
}

int main(void)
{
    tmpl_ThreeVectorDouble g, a, b, c, p, t, temp1, temp2, alpha, beta;
    unsigned int x, y, r;
    double factor, px, py, pz;
    FILE *fp;
    unsigned int size = 1024;

    g = tmpl_3DDouble_Rect(-6.0, -16.0, 0.0);
    tmpl_3DDouble_NormalizeSelf(&g);
    a = tmpl_3DDouble_Cross_Product(&tmpl_3DDouble_Z_Hat, &g);

    tmpl_3DDouble_NormalizeSelf(&a);
    tmpl_3DDouble_ScaleBy(&a, 0.002);
    b = tmpl_3DDouble_Cross_Product(&g, &a);
    tmpl_3DDouble_NormalizeSelf(&b);
    tmpl_3DDouble_ScaleBy(&b, 0.002);

    c = tmpl_3DDouble_Add(&a, &b);
    tmpl_3DDouble_ScaleBy(&c, -256.0);
    tmpl_3DDouble_AddTo(&c, &g);

    fp = fopen("initials_graphic.ppm", "w");
    fprintf(fp, "P6\n%u %u\n255\n", size, size);

    for (y = 0; y < size; ++y)
    {
        for(x = 0; x < size; ++x)
        {
            p = tmpl_3DDouble_Rect(13.0, 13.0, 13.0);

            for (r = 0; r < 64; ++r)
            {
                factor = (random_unit_interval() - 0.5);
                temp1 = tmpl_3DDouble_Scale(factor, &a);

                factor = (random_unit_interval()-0.5);
                temp2 = tmpl_3DDouble_Scale(factor, &b);

                t = tmpl_3DDouble_Add(&temp1, &temp2);
                tmpl_3DDouble_ScaleBy(&t, 99.0);

                temp1 = tmpl_3DDouble_Rect(18.0, 20.0, 8.0);
                alpha = tmpl_3DDouble_Add(&temp1, &t);

                factor = (random_unit_interval() + 0.5*(size-x));
                temp1 = tmpl_3DDouble_Scale(factor, &a);

                factor = (random_unit_interval() + 0.5*(size-y));
                temp2 = tmpl_3DDouble_Scale(factor, &b);
                beta = tmpl_3DDouble_Add(&temp1, &temp2);
                tmpl_3DDouble_AddTo(&beta, &c);
                tmpl_3DDouble_ScaleBy(&beta, 16.0);
                temp1 = tmpl_3DDouble_Scale(-1.0, &t);
                tmpl_3DDouble_AddTo(&beta, &temp1);
                tmpl_3DDouble_NormalizeSelf(&beta);

                temp1 = Shader(&alpha, &beta);
                temp2 = tmpl_3DDouble_Scale(3.5, &temp1);
                tmpl_3DDouble_AddTo(&p, &temp2);
            }

            px = tmpl_3DDouble_X(&p);
            py = tmpl_3DDouble_Y(&p);
            pz = tmpl_3DDouble_Z(&p);
            fprintf(fp, "%c%c%c", (int)px, (int)py, (int)pz);
        }
        printf("%u %u\n", y, size);
    }

    return 0;
}
