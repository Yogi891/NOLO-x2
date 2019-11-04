#ifndef KF_VECTOR2_HEADER
#define KF_VECTOR2_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"
#include "kf/kf_random.h"
#include <ostream>

namespace kf
{
   template<typename T>
   class Vector2T
   {
   public:
      T x;
      T y;
      inline Vector2T()
      {
         x = y = 0;
      }
      inline Vector2T(const Vector2T &c)
      {
         x = c.x;
         y = c.y;
      }
      explicit inline Vector2T(T xy)
      {
         x = y = xy;
      }
      template<typename T2>
         explicit inline Vector2T(const T2 *p)
      {
         x = T(p[0]);
         y = T(p[1]);
      }
      inline Vector2T(T xx, T yy)
      {
         x = xx;
         y = yy;
      }
      inline Vector2T &operator=(T c)
      {
         x = c;
         y = c;
         return *this;
      }
      inline Vector2T operator=(const Vector2T<T> &v)
      {
         x = v.x;
         y = v.y;
         return *this;
      }

      inline Vector2T operator,(T c)
      {
         y = c;
         return *this;
      }
      inline Vector2T operator*=(T c)
      {
         x *= c;
         y *= c;
         return *this;
      }
      inline Vector2T operator/=(T c)
      {
         x /= c;
         y /= c;
         return *this;
      }
      inline Vector2T operator+=(const Vector2T &c)
      {
         x += c.x;
         y += c.y;
         return *this;
      }
      inline Vector2T operator-=(const Vector2T &c)
      {
         x -= c.x;
         y -= c.y;
         return *this;
      }
      inline Vector2T operator*=(const Vector2T &c)
      {
         x *= c.x;
         y *= c.y;
         return *this;
      }
      inline Vector2T operator/=(const Vector2T &c)
      {
         x /= c.x;
         y /= c.y;
         return *this;
      }
      inline Vector2T operator=(const T *p)
      {
         x = p[0];
         y = p[1];
      }
      inline Vector2T normalise() const
      {
         T l;
         Vector2T temp;
         l=T(sqrt(x*x+y*y));
         if(l!=0.0)
         {
            temp.set(x/l,y/l);
         }
         return temp;
      }
      inline T length()
      {
         return sqrt(x*x+y*y);
      }
      inline T length_squared()
      {
         return x*x+y*y;
      }
      inline Vector2T swiz(int comp1, int comp2) const
      {
         return Vector2T( comp1 == 0 ? x : (comp1 == 1 ? y : 0),
            comp2 == 0 ? x : (comp2 == 1 ? y : 0));
      }
      inline void set(const Vector2T &value)
      {
         x = value.x;
         y = value.y;
      }
      inline void set(T xy)
      {
         x = y = xy;
      }
      inline void set(T xx, T yy)
      {
         x = xx;
         y = yy;
      }
      template<typename T2>
         inline void set(const T2 *p)
      {
         x = T(p[0]);
         y = T(p[1]);
      }
      inline static T dot(const Vector2T &v1, const Vector2T &v2)
      {
         return v1.x * v2.x + v1.y * v2.y;
      }

      inline friend std::ostream &operator<<(std::ostream &o, const Vector2T &v)
      {
         o << "<" << v.x << ", " << v.y << ">";
         return o;
      }

      inline friend Vector2T operator*(const Vector2T &v,const T &val)
      {
         return Vector2T(v.x*val,v.y*val);
      }
      inline friend Vector2T operator*(const T &val,const Vector2T &v)
      {
         return Vector2T(val*v.x, val*v.y);
      }
      inline friend Vector2T operator*(const Vector2T &v1,const Vector2T &v2)
      {
         return Vector2T(v1.x*v2.x,v1.y*v2.y);
      }

      inline friend Vector2T operator+(const Vector2T &v,const T &val)
      {
         return Vector2T(v.x+val,v.y+val);
      }
      inline friend Vector2T operator+(const T &val,const Vector2T &v)
      {
         return Vector2T(val+v.x, val+v.y);
      }
      inline friend Vector2T operator+(const Vector2T &v1,const Vector2T &v2)
      {
         return Vector2T(v1.x+v2.x,v1.y+v2.y);
      }

      inline friend Vector2T operator-(const Vector2T &v,const T &val)
      {
         return Vector2T(v.x-val,v.y-val);
      }
      inline friend Vector2T operator-(const T &val,const Vector2T &v)
      {
         return Vector2T(val-v.x, val-v.y);
      }
      inline friend Vector2T operator-(const Vector2T &v1,const Vector2T &v2)
      {
         return Vector2T(v1.x-v2.x,v1.y-v2.y);
      }

      inline friend Vector2T operator/(const Vector2T &v,const T &val)
      {
         return Vector2T(v.x/val,v.y/val);
      }
      inline friend Vector2T operator/(const T &val,const Vector2T &v)
      {
         return Vector2T(val/v.x, val/v.y);
      }
      inline friend Vector2T operator/(const Vector2T &v1,const Vector2T &v2)
      {
         return Vector2T(v1.x/v2.x,v1.y/v2.y);
      }

      inline void rotate(float angle)
      {
         T xx,yy;
         xx = x * cos(angle) - y * sin(angle);
         yy = x * sin(angle) + y * cos(angle);
         x=xx;
         y=yy;
      }
      inline friend Vector2T rotate(const Vector2T &v, float angle)
      {
         return Vector2T(v.x * cos(angle) - v.y * sin(angle), v.x * sin(angle) + v.y * cos(angle));
      }

	  inline static Vector2T randomUnit()
	  {
		  return Vector2T(cos(kf::random(kf::PI*1.99999)),sin(kf::random(kf::PI*1.99999)));
	  }

	  inline static Vector2T random(T minRange, T maxRange)
	  {
		  return Vector2T(cos(kf::random(kf::PI*2.0)),sin(kf::random(kf::PI*2.0)))*randomRange(minRange, maxRange);
	  }
	  
      KF_API static const Vector2T<T> ZERO;
      KF_API static const Vector2T<T> UNIT_X;
      KF_API static const Vector2T<T> UNIT_Y;
      KF_API static const Vector2T<T> NEGATIVE_UNIT_X;
      KF_API static const Vector2T<T> NEGATIVE_UNIT_Y;
   };

   typedef Vector2T<float>  Vector2f;
   typedef Vector2T<double> Vector2d;
   typedef Vector2T<float>  Vector2;

}


#endif

