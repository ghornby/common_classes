/***************************************************
<<<<<<< HEAD

Copyright (C) 1999-2003, Gregory S. Hornby.

=======
GENRE: An evolutionary design system.
Copyright (C) 1999-2003, Gregory S. Hornby.
ghornby@gmail.com

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

#include "cmn_algebra.h"

#include <cstdio>
#include <cmath>
#include <iostream>

using namespace std;

#define mval(m, i, j) m[i][j]
#define vec_cross(v1, v2, v3) v1[0]=v2[1]*v3[2]-v2[2]*v3[1]; v1[1]=v2[2]*v3[0]-v2[0]*v3[2]; v1[2]=v2[0]*v3[1]-v2[1]*v3[0]
#define vec_cross_pl(v1, v2, v3) v1[0]+=v2[1]*v3[2]-v2[2]*v3[1]; v1[1]+=v2[2]*v3[0]-v2[0]*v3[2]; v1[2]+=v2[0]*v3[1]-v2[1]*v3[0]
#define vec_plus(v1, v2, v3) v1[0]=v2[0]+v3[0]; v1[1]=v2[1]+v3[1];v1[2]=v2[2]+v3[2]
#define vec_neg(v1) v1[0]=-v1[0]; v1[1]=-v1[1];v1[2]=-v1[2]
#define vec_subt(v1, v2, v3) v1[0]=v2[0]-v3[0]; v1[1]=v2[1]-v3[1];v1[2]=v2[2]-v3[2]
#define vec_dot(v1, v2) ((v1[0]*v2[0])+(v1[1]*v2[1])+(v1[2]*v2[2]))
#define vs_mult(v, s) v[0]=v[0]*s; v[1]=v[1]*s; v[2]=v[2]*s
#define vs_div(v, s) v[0]=v[0]/s; v[1]=v[1]/s; v[2]=v[2]/s
#define vec_copy(d, s) d[0]=s[0]; d[1]=s[1]; d[2]=s[2]
#define vsv_mult(dv, sc, sv) dv[0]=sc*sv[0];dv[1]=sc*sv[1];dv[2]=sc*sv[2]






namespace CmnClass {

#define PRINT_OFFa

#define div(n, d) (d == 0 ? (div_zero = TRUE) : (n)/(d))


const double PI = 3.14159265358979323846;


#define sqr(val) (val)*(val)


template<typename T> inline T absv(const T a)
{
  return ((a >= 0.0) ? a : -a);
}


void sv_mult(double s, vector<double>& v)
{
  for (vector<double>::size_type i=0; i<v.size(); i++) {
    v[i] *= s;
  }
}


double simplify_angle(double angle)
{
  double mult;

  if (angle > 2.0*PI) {
    mult = angle/(2.0*PI);
    mult = floor(mult);
    angle -= mult*2.0*PI;

  } else if (angle < -2.0*PI) {
    mult = angle/(-2.0*PI);
    mult = floor(mult);
    angle += mult*2.0*PI;
  }

  return angle;
}

#define ANGLE_TOLERANCE 0.0001

double simplify_angle_180(double angle)
{
  double mult;

  if (angle > PI) {
    mult = angle/(2.0*PI);
    mult = floor(mult);
    angle -= mult*2.0*PI;
    if (angle > PI)
      angle -= 2.0 * PI;

  } else if (angle < PI) {
    mult = angle/(-2.0*PI);
    mult = floor(mult);
    angle += mult*2.0*PI;
    if (angle < -PI)
      angle += 2.0 * PI;
  }

  if (absv(angle+PI) < ANGLE_TOLERANCE)
    angle = PI;

  return angle;
}



double sum_vals(vector<double>& vals)
{
  double total = 0;
  for (vector<double>::size_type i=0; i<vals.size(); i++) {
    total += vals[i];
  }
  return total;
}


double calc_avg(vector<double>& vals)
{
  double mean = 0;

  for (vector<double>::size_type i=0; i<vals.size(); i++) {
    mean += vals[i];
  }

  return mean / double(vals.size());
}



double calc_sample_var(vector<double>& vals)
{
  // From: http://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
  
  double n = 0;
  double mean = 0;
  double m2 = 0;

  for (vector<double>::size_type i=0; i<vals.size(); i++) {
    n += 1.0;
    double delta = vals[i] - mean;
    mean += delta / n;
    m2 += delta * (vals[i] - mean);
  }

  return m2 / (n - 1.0);
}


double calc_sample_stdev(vector<double>& vals)
{
  // From: http://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
  
  double n = 0;
  double mean = 0;
  double m2 = 0;

  for (vector<double>::size_type i=0; i<vals.size(); i++) {
    n += 1.0;
    double delta = vals[i] - mean;
    mean += delta / n;
    m2 += delta * (vals[i] - mean);
  }

  double var = m2 / (n - 1.0);
  return sqrt(var);
}



// Returns the angle between the vectors: A->B and C->D:
// Want angle between the two vectors AB and CD
//  - Range is [-PI,PI]
//  - Negative angles are a right/clockwise bend (for a right-handed system)
//     Positive angles are a left/counter-clockwise bend (for a right-handed system)
// From: http://stackoverflow.com/questions/3057448/angle-between-3-vertices
// given A, B, C are 2D points:
//  BA = B - A; CA= C - A  // vector subtraction, to get vector between points
//  dot =    BA.x * CA.x + BA.y * CA.y
//  pcross = BA.x * CA.y - BA.y * CA.x
// angle= atan2(pcross, dot)  // this should be the angle BAC, in radians
// Note: above algorithm has angle btw BA and CA and not AB and CD.
double angle_btw_abcd_2d(double ax, double ay, double bx, double by,
			 double cx, double cy, double dx, double dy)
{
  double abx = bx - ax;
  double aby = by - ay;

  double cdx = dx - cx;
  double cdy = dy - cy;

  double dot = abx * cdx + aby * cdy;
  double pcross = abx * cdy - aby * cdx;
  double angle = atan2(pcross, dot);

  /*
  cout << ax << ":" << ay << "; " << bx << ":" << by << "; "
       << cx << ":" << cy << " => " << bax << ":" << bay
       << ", " << bcx << ":" << bcy << endl;
  cout << angle << " = atan2(" << pcross << ", " << dot << ")" << endl;
  */
  return angle;
}



double angle_btw_abbc_2d(double ax, double ay, double bx, double by,
			 double cx, double cy)
{
  return angle_btw_abcd_2d(ax, ay, bx, by, bx, by, cx, cy);

#ifdef OLD
  double abx = bx - ax;
  double aby = by - ay;

  double bcx = cx - bx;
  double bcy = cy - by;

  double dot = abx * bcx + aby * bcy;
  double pcross = abx * bcy - aby * bcx;
  double angle = atan2(pcross, dot);

  /*
  cout << ax << ":" << ay << "; " << bx << ":" << by << "; "
       << cx << ":" << cy << " => " << bax << ":" << bay
       << ", " << bcx << ":" << bcy << endl;
  cout << angle << " = atan2(" << pcross << ", " << dot << ")" << endl;
  */
  return angle;
#endif
}


double angle_btw_abcb_2d(double ax, double ay, double bx, double by,
			 double cx, double cy)
{
  return angle_btw_abcd_2d(ax, ay, bx, by, cx, cy, bx, by);
}


double angle_btw_babc_2d(double ax, double ay, double bx, double by,
			 double cx, double cy)
{
  return angle_btw_abcd_2d(bx, by, ax, ay, bx, by, cx, cy);
}



<<<<<<< HEAD
=======


#ifdef OLD
double angle_btw_pts2(double ax, double ay, double bx, double by,
		      double cx, double cy)
{
  double bax = ax - bx;
  double bay = ay - by;

  //  double bcx = cx - bx;
  //  double bcy = cy - by;

  double bcx = bx - cx;
  double bcy = by - cy;

  double dot = bax * bcx + bay * bcy;
  double pcross = bax * bcy - bay * bcx;
  double angle = atan2(pcross, dot);

  /*
  cout << ax << ":" << ay << "; " << bx << ":" << by << "; "
       << cx << ":" << cy << " => " << bax << ":" << bay
       << ", " << bcx << ":" << bcy << endl;
  cout << angle << " = atan2(" << pcross << ", " << dot << ")" << endl;
  */
  return angle;
}


// Angle between the vectors: AB and CD:
// This works by moving CD to be BD and calling the above function.
double angle_btw_pts2(double ax, double ay, double bx, double by,
		      double cx, double cy, double dx, double dy)
{
  double delta_x = bx - cx;
  double delta_y = by - cy;

  double dx2 = dx + delta_x;
  double dy2 = dy + delta_y;

  return angle_btw_pts2(ax, ay, bx, by, dx2, dy2);
}
#endif



// Want angle between the two vectors c-p1 and c-p2.
// Calculate angle as:
//   a.b = |a||b|cos(theta)
#ifdef OLD
double angle_btw_pts(double cx, double cy, double p1x, double p1y,
		   double p2x, double p2y)
{
  double numer = p1x*p2x + p1y*p2y;
  double denom = sqrt(sqr(p1x)+sqr(p1y)) * sqrt(sqr(p2x)+sqr(p2y));

  if (denom < ANGLE_TOLERANCE)
    return 0.0;
  return acos(numer / denom);
}
#endif


>>>>>>> 610f4b8cec34e3839778e2c63397d98f031107b7
// Returns the angle between the two vectors vec1 and vec2.
// Calculate angle as:
//   a.b = |a||b|cos(theta)
double angle_btw_vec3(double vec1[3], double vec2[3])
{
  double numer = vec_dot(vec1, vec2);
  double denom = vec_dot(vec1, vec1) * vec_dot(vec2, vec2);

  //  v_print(vec1, 0);
  //  v_print(vec2, 0);
  //  printf("%.4f / %.4f\n", numer, sqrt(denom));

  if (denom < ANGLE_TOLERANCE)
    return 0.0;

  // Delay taking the square-root 
  double angle = numer / sqrt(denom);
  //  printf("angle: %.4f, ", angle);
  angle = acos(angle);
  //  printf(" %.4f <%.4f>\n", angle, angle*RAD2DEG);
  return angle;
}


<<<<<<< HEAD
=======
void m4_print(double m[4][4], const char *string)
{
  int i, j;

#ifndef PRINT_OFF
  if (string)
    cout << string;
  for (i=0; i<4; i++)
    {
      for (j=0; j<4; j++)
	cout << m[i][j]<<"  ";
      cout <<endl;
    }
#endif
} 

void sp_m_print(double m[6][6], const char *string)
{
  int i, j;

#ifndef PRINT_OFF
  if (string)
    cout << string;
  for (i=0; i<6; i++)
    {
      for (j=0; j<6; j++)
	cout << m[i][j]<<" ";
      cout << endl;
    }
#endif
} 

void sp_v_print(double v[6], const char *string)
{
#ifndef PRINT_OFF
  int i;

  if (string)
    cout << string;
  for (i=0; i<6; i++)
    cout << v[i]<<"  ";
  cout << endl;
#endif
} 

void v_print(double v[3], const char *string)
{
#ifndef PRINT_OFF
  int i;
  double l = 0.0;

  if (string)
    cout << string;
  for (i=0; i<3; i++)
    cout << v[i]<<"  ";

  for (i=0; i<3; i++)
    l += sqr(v[i]);
  l = sqrt(l);
  cout << "("<<l<<")"<<endl;
#endif
} 


void v4_print(double v[4], const char *string)
{
#ifndef PRINT_OFF
  int i;
  double l = 0.0;

  if (string)
    cout << string;
  for (i=0; i<4; i++)
    cout << v[i]<<"  ";

  for (i=0; i<4; i++)
    l += sqr(v[i]);
  l = sqrt(l);
  cout << "("<<l<<")" << endl;
#endif
} 

>>>>>>> 610f4b8cec34e3839778e2c63397d98f031107b7

bool vec_norm(double v[3])
{
  double len;
  len = sqrt(sqr(v[0]) + sqr(v[1]) + sqr(v[2]));
  if (len != 0.0) {
    vs_div(v, len);
    return true;
  }
  return false;
}


double distance2(double p1[2], double p2[2])
{
  return sqrt(sqr(p1[0] - p2[0]) + sqr(p1[1] - p2[1]));
}


<<<<<<< HEAD
=======
void mm3_transpose(double dst[3][3], double src[3][3])
{
  for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
      dst[i][j] = src[j][i];
}


double svTv6_mult(double v1[6], double v2[6])
{
  int i;
  double val = 0.0;

  for (i=0; i<3; i++)
    val += v1[i+3]*v2[i];
  for (i=3; i<6; i++)
    val += v1[i-3]*v2[i];

  return val;
}

double svv6_mult(double v1[6], double v2[6])
{
  int i;
  double val = 0.0;

  for (i=0; i<6; i++)
    val += v1[i]*v2[i];

  return val;
}


void mm3_copy(double mdst[3][3], double msrc[3][3])
{
  mdst[0][0] = msrc[0][0];
  mdst[0][1] = msrc[0][1];
  mdst[0][2] = msrc[0][2];
  mdst[1][0] = msrc[1][0];
  mdst[1][1] = msrc[1][1];
  mdst[1][2] = msrc[1][2];
  mdst[2][0] = msrc[2][0];
  mdst[2][1] = msrc[2][1];
  mdst[2][2] = msrc[2][2];
}

void mm3_copy(int mdst[3][3], const int msrc[3][3])
{
  mdst[0][0] = msrc[0][0];
  mdst[0][1] = msrc[0][1];
  mdst[0][2] = msrc[0][2];
  mdst[1][0] = msrc[1][0];
  mdst[1][1] = msrc[1][1];
  mdst[1][2] = msrc[1][2];
  mdst[2][0] = msrc[2][0];
  mdst[2][1] = msrc[2][1];
  mdst[2][2] = msrc[2][2];
}


void mmm3_mult(int mdst[3][3], const int mat1[3][3], 
	       const int mat2[3][3])
{
   int i, j, k;
   int sum;

   for (i=0; i<3; i++) {
     for (j=0; j<3; j++) {
       sum = 0;
       for (k=0; k<3; k++) {
	 sum += mval(mat1, i, k)*mval(mat2, k, j);
       }
       mval(mdst, i, j) = sum;
     }
   }
}




void make_rotx_m3(double angle, double mat[3][3])
{
  double cos_ang = cos(angle);
  double sin_ang = sin(angle);

    mat[0][0] = 1.0;
    mat[0][1] = 0.0;
    mat[0][2] = 0.0;

    mat[1][0] = 0.0;
    mat[1][1] = cos_ang;
    mat[1][2] = -sin_ang;

    mat[2][0] = 0.0;
    mat[2][1] = sin_ang;
    mat[2][2] = cos_ang;
  }



  void make_roty_m3(double angle, double mat[3][3])
  {
    double cos_ang = cos(angle);
    double sin_ang = sin(angle);

    mat[0][0] = cos_ang;
    mat[0][1] = 0.0;
    mat[0][2] = sin_ang;

    mat[1][0] = 0.0;
    mat[1][1] = 1.0;
    mat[1][2] = 0.0;

    mat[2][0] = -sin_ang;
    mat[2][1] = 0.0;
    mat[2][2] = cos_ang;
  }


  void make_rotz_m3(double angle, double mat[3][3])
  {
    double cos_ang = cos(angle);
    double sin_ang = sin(angle);

    mat[0][0] = cos_ang;
    mat[0][1] = -sin_ang;
    mat[0][2] = 0.0;

    mat[1][0] = sin_ang;
    mat[1][1] = cos_ang;
    mat[1][2] = 0.0;

    mat[2][0] = 0.0;
    mat[2][1] = 0.0;
    mat[2][2] = 1.0;
  }


void mmm3_mult(double mdst[3][3], double mat1[3][3], 
	       double mat2[3][3])
{
   int i, j, k;
   double sum;

   for (i=0; i<3; i++) {
      for (j=0; j<3; j++) {
	sum = 0.0;
	for (k=0; k<3; k++) {
	  sum += mval(mat1, i, k)*mval(mat2, k, j);
	}
	mval(mdst, i, j) = sum;
      }
   }
}





void mmm_mult(double mdst[4][4], double mat1[4][4], 
	      double mat2[4][4])
{
   int i, j, k;
   double sum;

   for (i=0; i<4; i++)
      for (j=0; j<4; j++)
      {
	 sum = 0.0;
	 for (k=0; k<4; k++)
	    sum += mval(mat1, i, k)*mval(mat2, k, j);
	 mval(mdst, i, j) = sum;
      }
}

void vvm4_mult(double dst[3], double src[3], double mat[4][4])
{
  int i, j;

  for (i=0; i<3; i++)
    {
      dst[i] = 0.0;
      for (j=0; j<3; j++)
	dst[i] += src[j]*mat[j][i];
    }
}

void vvTm6_mult(double dst[6], double src[6], double mat[6][6])
{
  int i, j;

  for (i=0; i<6; i++)
    {
      dst[i] = 0.0;
      for (j=0; j<3; j++)
	dst[i] += src[j+3]*mat[j][i];
      for (j=3; j<6; j++)
	dst[i] += src[j-3]*mat[j][i];
    }
}

void vvm6_mult(double dst[6], double src[6], double mat[6][6])
{
  int i, j;

  for (i=0; i<6; i++)
    {
      dst[i] = 0.0;
      for (j=0; j<6; j++)
	dst[i] += src[j]*mat[j][i];
    }
}

void vmv_mult(double dst[3], double mat[3][3], double src[3])
{
  int i, j;

  for (i=0; i<3; i++)
    {
      dst[i] = 0.0;
      for (j=0; j<3; j++)
	dst[i] += mat[i][j]*src[j];
    }
}


void vmv4_mult(double dst[3], double mat[4][4], double src[3])
{
  int i, j;

  for (i=0; i<3; i++)
    {
      dst[i] = 0.0;
      for (j=0; j<3; j++)
	dst[i] += mat[i][j]*src[j];
    }
}


void vmv443_mult(double dst[4], double mat[4][3], double src[3])
{
  int i, j;

  for (i=0; i<4; i++)
    {
      dst[i] = 0.0;
      for (j=0; j<3; j++)
	dst[i] += mat[i][j]*src[j];
    }
}


void msm6_mult(double dst[6][6], double sc, double src[6][6])
{
  int i, j;

  for (i=0; i<6; i++)
    for (j=0; j<6; j++)
      dst[i][j] = sc * src[i][j];
}


void ms6_mult(double m[6][6], double sc)
{
  int i, j;

  for (i=0; i<6; i++)
    for (j=0; j<6; j++)
      m[i][j] = sc*m[i][j];
}

void ms6_div(double m[6][6], double sc)
{
  int i, j;

  for (i=0; i<6; i++)
    for (j=0; j<6; j++)
      m[i][j] = m[i][j]/sc;
}

void mvv6_mult(double m[6][6], double v1[6], double v2[6])
{
  int i, j;
  /* handle transpose "funny"? : no */

  for (i=0; i<6; i++)
    for (j=0; j<6; j++)
      m[i][j] = v1[i]*v2[j];
}

void vmv6_mult(double dst[6], double mat[6][6], double src[6])
{
  int i, j;

  for (i=0; i<6; i++)
    {
      dst[i] = 0.0;
      for (j=0; j<6; j++)
	dst[i] += mat[i][j]*src[j];
    }
}

void mm6_plus(double d[6][6], double s[6][6])
{
  int i, j;

  for (i=0; i<6; i++)
    for (j=0; j<6; j++)
      d[i][j]+=s[i][j];
}

void mmm6_subt(double d[6][6], double m1[6][6], double m2[6][6])
{
  int i, j;

  for (i=0; i<6; i++)
    for (j=0; j<6; j++)
      d[i][j]=m1[i][j]-m2[i][j];
}

void mmm6_mult(double mdst[6][6], double mat1[6][6], 
	       double mat2[6][6])
{
   int i, j, k;
   double sum;

   for (i=0; i<6; i++)
      for (j=0; j<6; j++)
      {
	 sum = 0.0;
	 for (k=0; k<6; k++)
	    sum += mval(mat1, i, k)*mval(mat2, k, j);
	 mval(mdst, i, j) = sum;
      }
}


#define ALMOST_ZERO 0.0000001

double line_segment_distance(double seg1_a[3], double seg1_b[3],
			   double seg2_a[3], double seg2_b[3])
{
  double sc, sd, sn, tc, td, tn;
  double uu, uv, vv, uw, vw, det;
  double u[3], v[3], w[3];

  vec_subt(u, seg1_b, seg1_a);
  vec_subt(v, seg2_b, seg2_a);
  vec_subt(w, seg1_a, seg2_a);

  uu = vec_dot(u, u);
  uv = vec_dot(u, v);
  vv = vec_dot(v, v);
  uw = vec_dot(u, w);
  vw = vec_dot(v, w);
  
  det = uu*vv - sqr(uv);
  sd = det;
  td = det;

  if (det < ALMOST_ZERO) {
    sn = 0.0;
    sd = 1.0;
    tn = vw;
    td = vv;
  } else {
    sn = uv*vw - vv*uw;
    tn = uu*vw - uv*uw;
    if (sn < 0.0) {
      sn = 0.0;
      tn = vw;
      td = vv;
    } else if (sn > sd) {
      sn = sd;
      tn = vw + uv;
      td = vv;
    }
  }

  if (tn < 0.0) {
    tn = 0.0;
    if (-uw < 0.0) {
      sn = 0.0;
    } else if (-uw > uu) {
      sn = sd;
    } else {
      sn = -uw;
      sd = uu;
    }
  } else if (tn > td) {
    tn = td;
    if (uv-uw < 0.0) {
      sn = 0.0;
    } else if (uv-uw > uu) {
      sn = sd;
    } else {
      sn = uv-uw;
      sd = uu;
    }
  }

  sc = (absv(sn) < ALMOST_ZERO ? 0.0 : sn / sd);
  tc = (absv(tn) < ALMOST_ZERO ? 0.0 : tn / td);

  vs_mult(u, sc);
  vs_mult(v, tc);
  vec_plus(w, w, u);
  vec_subt(w, w, v);

  return vec_dot(w, w);
}

>>>>>>> 610f4b8cec34e3839778e2c63397d98f031107b7

// This function is adapted from geom.cpp in ODE, which
// is copyright Russell Smith.
// given two line segments A and B with endpoints a1-a2 and b1-b2, return the
// points on A and B that are closest to each other (in cp1 and cp2).
// in the case of parallel lines where there are multiple solutions, a
// solution involving the endpoint of at least one line will be returned.
// this will work correctly for zero length lines, e.g. if a1==a2 and/or
// b1==b2.
//
// the algorithm works by applying the voronoi clipping rule to the features
// of the line segments. the three features of each line segment are the two
// endpoints and the line between them. the voronoi clipping rule states that,
// for feature X on line A and feature Y on line B, the closest points PA and
// PB between X and Y are globally the closest points if PA is in V(Y) and
// PB is in V(X), where V(X) is the voronoi region of X.
void line_segment_closest_points(double a1[3], double a2[3],
				 double b1[3], double b2[3],
				 double cp1[3], double cp2[3])
{
  double la, lb, k, da1, da2, da3, da4, db1, db2, db3, db4, det;
  double a1a2[3], b1b2[3], a1b1[3], a1b2[3], a2b1[3], a2b2[3], n[3], tmp[3];

  // check vertex-vertex features

  vec_subt(a1a2, a2, a1);
  vec_subt(b1b2, b2, b1);
  vec_subt(a1b1, b1, a1);

  da1 = vec_dot(a1a2, a1b1);
  db1 = vec_dot(b1b2, a1b1);

  if ((da1 <= 0) && (db1 >= 0)) {
    vec_copy(cp1, a1);
    vec_copy(cp2, b1);
    return;
  }

  vec_subt(a1b2, b2, a1);
  da2 = vec_dot(a1a2, a1b2);
  db2 = vec_dot(b1b2,a1b2);
  if ((da2 <= 0) && (db2 <= 0)) {
    vec_copy(cp1, a1);
    vec_copy(cp2, b2);
    return;
  }

  vec_subt(a2b1, b1, a2);
  da3 = vec_dot(a1a2, a2b1);
  db3 = vec_dot(b1b2, a2b1);
  if ((da3 >= 0) && (db3 >= 0)) {
    vec_copy(cp1, a2);
    vec_copy(cp2, b1);
    return;
  }

  vec_subt(a2b2, b2, a2);
  da4 = vec_dot(a1a2, a2b2);
  db4 = vec_dot(b1b2, a2b2);
  if ((da4 >= 0) && (db4 <= 0)) {
    vec_copy(cp1, a2);
    vec_copy(cp2, b2);
    return;
  }

  // check edge-vertex features.
  // if one or both of the lines has zero length, we will never get to here,
  // so we do not have to worry about the following divisions by zero.

  la = vec_dot(a1a2, a1a2);
  if ((da1 >= 0) && (da3 <= 0.0)) {
    k = da1 / la;
    vsv_mult(tmp, k, a1a2);
    vec_subt(n, a1b1, tmp);

    if (vec_dot(b1b2, n) >= 0.0) {
      vec_plus(cp1, a1, tmp);
      vec_copy(cp2, b1);
      return;
    }
  }

  if ((da2 >= 0) && (da4 <= 0)) {
    k = da2 / la;
    vsv_mult(tmp, k, a1a2);
    vec_subt(n, a1b2, tmp);
    if (vec_dot(b1b2, n) <= 0.0) {
      vec_plus(cp1, a1, tmp);
      vec_copy(cp2, b2);
      return;
    }
  }

  lb = vec_dot(b1b2, b1b2);
  if ((db1 <= 0) && (db2 >= 0.0)) {
    k = -db1 / lb;
    vsv_mult(tmp, k, b1b2);
    vec_neg(a1b1);
    vec_subt(n, a1b1, tmp);
    if (vec_dot(a1a2, n) >= 0.0) {
      vec_copy(cp1,a1);
      vec_plus(cp2, b1, tmp);
      return;
    }
  }

  if ((db3 <= 0.0) && (db4 >= 0.0)) {
    k = -db3 / lb;
    vsv_mult(tmp, k, b1b2);
    vec_neg(a2b1);
    vec_subt(n, a2b1, tmp);
    if (vec_dot(a1a2, n) <= 0.0) {
      vec_copy(cp1,a2);
      vec_plus(cp2, b1, tmp);
      return;
    }
  }

  // it must be edge-edge

  k = vec_dot(a1a2, b1b2);
  det = la*lb - k*k;
  if (det <= 0.0) {
    // this should never happen, but just in case...
    vec_copy(cp1, a1);
    vec_copy(cp2, b1);
    return;
  }

  det = 1.0/det;
  double alpha = (lb*da1 -  k*db1) * det;
  double beta  = ( k*da1 - la*db1) * det;

  vs_mult(a1a2, alpha);
  vec_plus(cp1, a1, a1a2);

  vs_mult(b1b2, beta);
  vec_plus(cp2, b1, b1b2);
}


double lines_distance_3d(double a1[3], double a2[3],
		       double b1[3], double b2[3])
{
  double cp1[3], cp2[3], len[3];

  line_segment_closest_points(a1, a2, b1, b2, cp1, cp2);

  vec_subt(len, cp2, cp1);
  return vec_dot(len, len);
}


}
