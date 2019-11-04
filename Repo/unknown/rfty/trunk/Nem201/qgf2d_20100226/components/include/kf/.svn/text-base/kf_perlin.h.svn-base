#ifndef KF_PERLIN_H
#define KF_PERLIN_H
//#include "stdio.h"

#include "math.h"
#include "kf/kf_types.h"

//Public Domain Turbulence Source****************************************************
/*extern double bias(double a, double b);
extern double gain(double a, double b);
extern double noise1(double arg);
extern double noise2(double vec[]);
extern double noise3(double vec[]);
extern double noise(double vec[], int len);
extern double turbulence(double *v, double freq);
void init(void);
extern double noise1(double arg);
extern double noise2(double vec[2]);
extern double noise3(double vec[3]);
extern void normalize2(double v[2]);
extern void normalize3(double v[3]);
*/
//End Of Turbulence******************************************************************
namespace kf
{
class KF_API Perlin
{
public:
	double m_octave;
	double m_power;
	double *m_g1;
	double *m_g2;
	double *m_g3;
	int *m_p;
   Perlin();
//	Perlin(double octave,double power);
   ~Perlin();
	double noise(double x);
   double noise(double x,double y);
	double turbulence(double x,double y,double freq);
   double s_curve(double t);
   double lerp(double t, double a, double b);
   const int c_perlin_b;
   const int c_perlin_bm;
   const int c_perlin_n;
   const int c_perlin_np;
   const int c_perlin_nm;
};
}
#endif
