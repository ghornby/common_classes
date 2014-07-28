/***************************************************

Copyright (C) 1999-2003, Gregory S. Hornby.

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


double line_segment_distance(double seg1_a[3], double seg1_b[3],
			   double seg2_a[3], double seg2_b[3]);
double lines_distance_3d(double L0_a[3], double L0_b[3],
		       double L1_a[3], double L1_b[3]);


}

#endif
