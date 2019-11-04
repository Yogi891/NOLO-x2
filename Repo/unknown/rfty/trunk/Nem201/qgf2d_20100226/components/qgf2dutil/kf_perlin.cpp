#include "kf/kf_perlin.h"
#include <stdlib.h>
namespace kf
{
//Public Domain Turbulence Source**********************************************************
/*
double bias(double a, double b)
{
	return (double)pow(a, log(b) / log(0.5));
}

double gain(double a, double b)
{
	double p = log(1. - b) / log(0.5);
	
	if (a < .001)
		return 0.;
	else if (a > .999)
		return 1.;
	if (a < 0.5)
		return pow(2 * a, p) / 2;
	else
		return 1. - pow(2 * (1. - a), p) / 2;
}

double noise1(double arg);
double noise2(double vec[]);
double noise3(double vec[]);

double noise(double vec[], int len)
{
	switch (len) {
		case 0:
			return 0.;
		case 1:
			return noise1(vec[0]);
		case 2:
			return noise2(vec);
		default:
			return noise3(vec);
	}
}

double turbulence(double *v, double freq)
{
	double t, vec[3];
	
	for (t = 0. ; freq >= 1. ; freq /= 2) {
		vec[0] = freq * v[0];
		vec[1] = freq * v[1];
		vec[2] = freq * v[2];
		t += fabs(noise3(vec)) / freq;
	}
	return t;
}


#define B 0x100
#define BM 0xff

#define N 0x1000
#define NP 12
#define NM 0xfff

static p[B + B + 2];
static double g3[B + B + 2][3];
static double g2[B + B + 2][2];
static double g1[B + B + 2];
int start=1;
#define s_curve(t) ( t * t * (3. - 2. * t) )













#define lerp(t, a, b) ( a + t * (b - a) )

#define setup(i,b0,b1,r0,r1)\
t = vec[i] + N;\
b0 = ((int)t) & BM;\
b1 = (b0+1) & BM;\
r0 = t - (int)t;\
r1 = r0 - 1.;

double noise1(double arg)
{
	int bx0, bx1;
	double rx0, rx1, sx, t, u, v, vec[1];
	
	vec[0] = arg;
	if (start) {
		start = 0;
		init();
	}
	
	setup(0, bx0,bx1, rx0,rx1);
	
	sx = s_curve(rx0);
	
	u = rx0 * g1[ p[ bx0 ] ];
	v = rx1 * g1[ p[ bx1 ] ];
	
	return lerp(sx, u, v);
}

double noise2(double vec[2])
{
	int bx0, bx1, by0, by1, b00, b10, b01, b11;
	double rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v;
	register i, j;
	
	if (start) {
		start = 0;
		init();
	}
	
	setup(0, bx0,bx1, rx0,rx1);
	setup(1, by0,by1, ry0,ry1);
	
	i = p[ bx0 ];
	j = p[ bx1 ];
	
	b00 = p[ i + by0 ];
	b10 = p[ j + by0 ];
	b01 = p[ i + by1 ];
	b11 = p[ j + by1 ];
	
	sx = s_curve(rx0);
	sy = s_curve(ry0);
	
#define at2(rx,ry) ( rx * q[0] + ry * q[1] )
	
	q = g2[ b00 ] ; u = at2(rx0,ry0);
	q = g2[ b10 ] ; v = at2(rx1,ry0);
	a = lerp(sx, u, v);
	
	q = g2[ b01 ] ; u = at2(rx0,ry1);
	q = g2[ b11 ] ; v = at2(rx1,ry1);
	b = lerp(sx, u, v);
	
	return lerp(sy, a, b);
}

double noise3(double vec[3])
{
	int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
	double rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
	register i, j;
	
	if (start) {
		start = 0;
		init();
	}
	
	setup(0, bx0,bx1, rx0,rx1);
	setup(1, by0,by1, ry0,ry1);
	setup(2, bz0,bz1, rz0,rz1);
	
	i = p[ bx0 ];
	j = p[ bx1 ];
	
	b00 = p[ i + by0 ];
	b10 = p[ j + by0 ];
	b01 = p[ i + by1 ];
	b11 = p[ j + by1 ];
	
	t  = s_curve(rx0);
	sy = s_curve(ry0);
	sz = s_curve(rz0);
	
#define at3(rx,ry,rz) ( rx * q[0] + ry * q[1] + rz * q[2] )
	
	q = g3[ b00 + bz0 ] ; u = at3(rx0,ry0,rz0);
	q = g3[ b10 + bz0 ] ; v = at3(rx1,ry0,rz0);
	a = lerp(t, u, v);
	
	q = g3[ b01 + bz0 ] ; u = at3(rx0,ry1,rz0);
	q = g3[ b11 + bz0 ] ; v = at3(rx1,ry1,rz0);
	b = lerp(t, u, v);
	
	c = lerp(sy, a, b);
	
	q = g3[ b00 + bz1 ] ; u = at3(rx0,ry0,rz1);
	q = g3[ b10 + bz1 ] ; v = at3(rx1,ry0,rz1);
	a = lerp(t, u, v);
	
	q = g3[ b01 + bz1 ] ; u = at3(rx0,ry1,rz1);
	q = g3[ b11 + bz1 ] ; v = at3(rx1,ry1,rz1);
	b = lerp(t, u, v);
	
	d = lerp(sy, a, b);
	
	return lerp(sz, c, d);
}

static void normalize2(double v[2])
{
	double s;
	
	s = sqrt(v[0] * v[0] + v[1] * v[1]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
}

static void normalize3(double v[3])
{
	double s;
	
	s = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
	v[2] = v[2] / s;
}

void init(void)
{
	int i, j, k;
	
	for (i = 0 ; i < B ; i++) {
		p[i] = i;
		
		g1[i] = (double)((rand() % (B + B)) - B) / B;
		
		for (j = 0 ; j < 2 ; j++)
			g2[i][j] = (double)((rand() % (B + B)) - B) / B;
		normalize2(g2[i]);
		
		for (j = 0 ; j < 3 ; j++)
			g3[i][j] = (double)((rand() % (B + B)) - B) / B;
		normalize3(g3[i]);
	}
	
	while (--i) {
		k = p[i];
		p[i] = p[j = rand() % B];
		p[j] = k;
	}
	
	for (i = 0 ; i < B + 2 ; i++) {
		p[B + i] = p[i];
		g1[B + i] = g1[i];
		for (j = 0 ; j < 2 ; j++)
			g2[B + i][j] = g2[i][j];
		for (j = 0 ; j < 3 ; j++)
			g3[B + i][j] = g3[i][j];
	}
}

*/

Perlin::~Perlin()
{
   delete [] m_p;
   delete [] m_g1;
   delete [] m_g2;
   delete [] m_g3;
}

Perlin::Perlin():c_perlin_b(0x100),
c_perlin_bm(0xff),c_perlin_n(0x1000),c_perlin_np(12),c_perlin_nm(0xfff)
{
   int size = int(c_perlin_b) + int(c_perlin_b) + 2;
   m_p = new int[size];
	m_g1 = new double[size];
   m_g2 = new double[size * 2];
   m_g3 = new double[size * 3];
   
   int i, j, k,temp2;
  	double s,temp;

	
	for (i = 0 ; i < int(c_perlin_b) ; i++) 
   {
		m_p[i] = i;
		
		m_g1[i] = (double)((rand() % (int(c_perlin_b) * 2)) - int(c_perlin_b)) / int(c_perlin_b);
		
		for (j = 0 ; j < 2 ; j++)
      {
         temp2=rand() % (int(c_perlin_b) * 2);
         temp=double(((temp2) - int(c_perlin_b))) / int(c_perlin_b);
			m_g2[i*2+j] = temp;
      }
	
	   s = sqrt(m_g2[i*2] * m_g2[i*2] + m_g2[i*2+1] * m_g2[i*2+1]);
	   m_g2[i*2] = m_g2[i*2] / s;
	   m_g2[i*2+1] = m_g2[i*2+1] / s;
		
		for (j = 0 ; j < 3 ; j++)
      {
			m_g3[i*3+j] = (double)((rand() % (int(c_perlin_b) * 2)) - int(c_perlin_b)) / int(c_perlin_b);
      }
	   s = sqrt(m_g3[i*3] * m_g3[i*3] + m_g3[i*3+1] * m_g3[i*3+1] + m_g3[i*3+2] * m_g3[i*3+2]);
	   m_g3[i*3] = m_g3[i*3] / s;
	   m_g3[i*3+1] = m_g3[i*3+1] / s;
	   m_g3[i*3+2] = m_g3[i*3+2] / s;
	}
	
	while (--i) 
   {
		k = m_p[i];
		m_p[i] = m_p[j = rand() % int(c_perlin_b)];
		m_p[j] = k;
	}
	
	for (i = 0 ; i < int(c_perlin_b) + 2 ; i++) 
   {
		m_p[int(c_perlin_b) + i] = m_p[i];
		m_g1[int(c_perlin_b) + i] = m_g1[i];
		for (j = 0 ; j < 2 ; j++)
      {
			m_g2[(int(c_perlin_b) + i)*2+j] = m_g2[i*2+j];
      }
		for (j = 0 ; j < 3 ; j++)
      {
			m_g3[(int(c_perlin_b) + i)*3+j] = m_g3[i*3+j];
      }
	}
}

double Perlin::s_curve(double t)
{
   return t * t * (3. - 2. * t);
}

double Perlin::lerp(double t, double a, double b) 
{
   return ( a + t * (b - a) );
}

double Perlin::noise(double x,double y)
{
	int bx0, bx1, by0, by1, b00, b10, b01, b11;
	double rx0, rx1, ry0, ry1, *q, sx, sy, a, b, u, v;
	register int i, j;
	
   bx0 = int(x + int(c_perlin_n)) & int(c_perlin_bm);
   bx1 = (bx0 + 1) & int(c_perlin_bm);
   rx0 = (x + int(c_perlin_n)) - int(x + int(c_perlin_n));
   rx1 = rx0 - 1;

   by0 = int(y + int(c_perlin_n)) & int(c_perlin_bm);
   by1 = (by0 + 1) & int(c_perlin_bm);
   ry0 = (y + int(c_perlin_n)) - int(y + int(c_perlin_n));
   ry1 = ry0 - 1;

	i = m_p[ bx0 ];
	j = m_p[ bx1 ];
	
	b00 = m_p[ i + by0 ];
	b10 = m_p[ j + by0 ];
	b01 = m_p[ i + by1 ];
	b11 = m_p[ j + by1 ];
	
	sx = s_curve(rx0);
	sy = s_curve(ry0);
	
	
	q = &m_g2[ b00*2 ] ; u = rx0 * q[0] + ry0 * q[1];
	q = &m_g2[ b10*2 ] ; v = rx1 * q[0] + ry0 * q[1];
	a = lerp(sx, u, v);
	
	q = &m_g2[ b01*2 ] ; u = rx0 * q[0] + ry1 * q[1];
	q = &m_g2[ b11*2 ] ; v = rx1 * q[0] + ry1 * q[1];
	b = lerp(sx, u, v);
	
	return lerp(sy, a, b);
}

double Perlin::turbulence(double x,double y,double freq)
{
	double t, u,v;
	
	for (t = 0.0 ; freq >= 1.0 ; freq /= 2.0) {
		u = freq * x;
		v = freq * y;
		t += (noise(u,v)) / freq;
	}
	return t*0.5+0.5;
}
}
//End Of Turbulence***************************************************************************


