/***************************************************
<<<<<<< HEAD

Copyright (C) 1999-2003, Gregory S. Hornby.

=======
GENRE: An evolutionary design system.
Copyright (C) 1999-2003, Gregory S. Hornby.
hornby@email.arc.nasa.gov
http://ic.arc.nasa.gov/people/hornby

This library is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free
Software Foundation; either version 2.1 of the License,
or (at your option) any later version.

This library is distributed in the hope that it will
be useful, but WITHOUT ANY WARRANTY; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

The text of the GNU Lesser General Public License is
included with this library in the file LICENSE.TXT.
If this file is not included with this library write
to the Free Software Foundation, Inc., 59 Temple Place,
Suite 330, Boston, MA  02111-1307  USA
>>>>>>> 610f4b8cec34e3839778e2c63397d98f031107b7
****************************************************/


#ifndef CMN_ALGEBRA_HEADER_FILE
#define CMN_ALGEBRA_HEADER_FILE

#include <vector>


namespace CmnClass {

void sv_mult(double s, std::vector<double>& v);

double distance2(double p1[2], double p2[2]);
double simplify_angle(double angle);
double simplify_angle_180(double angle);
double sum_vals(std::vector<double>& vals);
double calc_avg(std::vector<double>& vals);
double calc_sample_stdev(std::vector<double>& vals);
double calc_sample_var(std::vector<double>& vals);


double angle_btw_abcd_2d(double ax, double ay, double bx, double by,
			 double cx, double cy, double dx, double dy);
double angle_btw_abbc_2d(double ax, double ay, double bx, double by,
			 double cx, double cy);
double angle_btw_abcb_2d(double ax, double ay, double bx, double by,
			 double cx, double cy);
double angle_btw_babc_2d(double ax, double ay, double bx, double by,
			 double cx, double cy);

double angle_btw_vec3(double vec1[3], double vec2[3]);


<<<<<<< HEAD
=======
void m4_print(double m[4][4], const char *string);
void sp_m_print(double m[6][6], const char *string);
void sp_v_print(double v[6], const char *string);
void v_print(double v[3], const char *string);
void v4_print(double v[4], const char *string);

bool vec_norm(double v[3]);

void mm3_transpose(double dst[3][3], double src[3][3]);



void make_rotx_m3(double angle, double mat[3][3]);
void make_roty_m3(double angle, double mat[3][3]);
void make_rotz_m3(double angle, double mat[3][3]);
void mmm3_mult(double mdst[3][3], const double mat1[3][3], 
           const double mat2[3][3]);




double svTv6_mult(double v1[6], double v2[6]);
double svv6_mult(double v1[6], double v2[6]);
void vvm4_mult(double dst[3], double src[3], double mat[4][4]);
void vmv_mult(double dst[3], double mat[3][3], double src[3]);
void vmv4_mult(double dst[3], double mat[4][4], double src[3]);
void vmv443_mult(double dst[4], double mat[4][3], double src[3]);
void mm3_copy(double dst[3][3], double msrc[3][3]);
void mm3_copy(int dst[3][3], const int msrc[3][3]);
void mmm3_mult(int dst[3][3], const int mat1[3][3], const int mat2[3][3]);
void mmm3_mult(double dst[3][3], double mat1[3][3], double mat2[3][3]);
void mmm_mult(double dst[4][4], double mat1[4][4], double mat2[4][4]);
void msm6_mult(double dst[6][6], double sc, double src[6][6]);
void vvTm6_mult(double dst[6], double src[6], double mat[6][6]);
void vvm6_mult(double dst[6], double src[6], double mat[6][6]);

void vmv6_mult(double dst[6], double mat[6][6], double src[6]);
void mvv6_mult(double mat[6][6], double v1[6], double v2[6]);
void ms6_mult(double mat[6][6], double sc);
void ms6_div(double mat[6][6], double sc);
void mmm6_mult(double dst[6][6], double m1[6][6], double m2[6][6]);
void mm6_plus(double dst[6][6], double src[6][6]);
void mmm6_subt(double d[6][6], double m1[6][6], double m2[6][6]);

>>>>>>> 610f4b8cec34e3839778e2c63397d98f031107b7
double line_segment_distance(double seg1_a[3], double seg1_b[3],
			   double seg2_a[3], double seg2_b[3]);
double lines_distance_3d(double L0_a[3], double L0_b[3],
		       double L1_a[3], double L1_b[3]);


}

#endif
