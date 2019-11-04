#ifndef KF_VECTOR4_HEADER
#define KF_VECTOR4_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"
#include <ostream>

namespace kf
{
   template<typename T>
   class Vector4T
   {
   public:
      T x;
      T y;
      T z;
	  T w;
      inline Vector4T()
      {
         x = y = z = w = 0;
      }
      inline Vector4T(const Vector4T &c)
      {
         x = c.x;
         y = c.y;
         z = c.z;
		   w = c.w;
      }
      explicit inline Vector4T(T xyzw)
      {
         x = y = z = w = xyzw;
      }
      template<typename T2>
         explicit inline Vector4T(const T2 *p)
      {
         x = T(p[0]);
         y = T(p[1]);
         z = T(p[2]);
         w = T(p[3]);
      }
      inline Vector4T(T xx, T yy, T zz, T ww)
      {
         x = xx;
         y = yy;
         z = zz;
		   w = ww;
      }
      inline Vector4T operator*=(T c)
      {
         x *= c;
         y *= c;
         z *= c;
		   w *= c;
         return *this;
      }
      inline Vector4T operator/=(T c)
      {
         x /= c;
         y /= c;
         z /= c;
		   w /= c;
         return *this;
      }
      inline Vector4T operator+=(const Vector4T &c)
      {
         x += c.x;
         y += c.y;
         z += c.z;
		   w += c.w;
         return *this;
      }
      inline Vector4T operator-=(const Vector4T &c)
      {
         x -= c.x;
         y -= c.y;
         z -= c.z;
		   w -= c.w;
         return *this;
      }
      inline Vector4T operator*=(const Vector4T &c)
      {
         x *= c.x;
         y *= c.y;
         z *= c.z;
		   w *= c.w;
         return *this;
      }
      inline Vector4T operator/=(const Vector4T &c)
      {
         x /= c.x;
         y /= c.y;
         z /= c.z;
		   w /= c.w;
         return *this;
      }
      inline Vector4T operator=(const T *p)
      {
         x = p[0];
         y = p[1];
         z = p[2];
         w = p[3];
         return *this;
      }
      inline Vector4T operator=(const Vector4T<T> &v)
      {
         x = v.x;
         y = v.y;
         z = v.z;
         w = v.w;
         return *this;
      }

      inline Vector4T normalise()
      {
         T l;
         Vector4T temp;
         l=T(sqrt(x*x+y*y+z*z+w*w));
         if(l!=0.0)
         {
            temp.set(x/l,y/l,z/l,w/l);
         }
         return temp;
      }
      inline T length()
      {
         return sqrt(x*x+y*y+z*z+w*w);
      }
      inline T length_squared()
      {
         return x*x+y*y+z*z+w*w;
      }
	  inline Vector4T swiz(kf::dword comp1, kf::dword comp2, kf::dword comp3, kf::dword comp4) const
      {
		  return Vector4T( comp1 == 0 ? x : (comp1 == 1 ? y : (comp1 == 2 ? z : (comp1 == 3 ? w : 0))),
            comp2 == 0 ? x : (comp2 == 1 ? y : (comp2 == 2 ? z : (comp2 == 3 ? w : 0))),
            comp3 == 0 ? x : (comp3 == 1 ? y : (comp3 == 2 ? z : (comp3 == 3 ? w : 0))),
			comp4 == 0 ? x : (comp4 == 1 ? y : (comp4 == 2 ? z : (comp4 == 3 ? w : 0))));
      }
      inline void set(const Vector4T &value)
      {
         x = value.x;
         y = value.y;
         z = value.z;
		   w = value.w;
      }
      inline void set(T xyzw)
      {
         x = y = z = w= xyzw;
      }
      inline void set(T xx, T yy, T zz, T ww)
      {
         x = xx;
         y = yy;
         z = zz;
		   w = ww;
      }
      template<typename T2>
         inline void set(const T2 *p)
      {
         x = T(p[0]);
         y = T(p[1]);
         z = T(p[2]);
		   w = T(p[3]);
      }
      inline friend T dot(const Vector4T &v1, const Vector4T &v2)
      {
         return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
      }

      inline friend std::ostream &operator<<(std::ostream &o, const Vector4T &v)
      {
         o << "<" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ">";
         return o;
      }

      inline friend Vector4T operator*(const Vector4T &v,const T &val)
      {
         return Vector4T(v.x*val, v.y*val, v.z*val, v.w*val);
      }
      inline friend Vector4T operator*(const T &val,const Vector4T &v)
      {
         return Vector4T(val*v.x, val*v.y, val*v.z, val*v.w);
      }
      inline friend Vector4T operator*(const Vector4T &v1,const Vector4T &v2)
      {
         return Vector4T(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z, v1.w*v2.w);
      }

      inline friend Vector4T operator+(const Vector4T &v,const T &val)
      {
         return Vector4T(v.x+val, v.y+val, v.z+val, v.w+val);
      }
      inline friend Vector4T operator+(const T &val,const Vector4T &v)
      {
         return Vector4T(val+v.x, val+v.y, val+v.z, val+v.w);
      }
      inline friend Vector4T operator+(const Vector4T &v1,const Vector4T &v2)
      {
         return Vector4T(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z, v1.w+v2.w);
      }

      inline friend Vector4T operator-(const Vector4T &v,const T &val)
      {
         return Vector4T(v.x-val, v.y-val, v.z-val, v.w-val);
      }
      inline friend Vector4T operator-(const T &val,const Vector4T &v)
      {
         return Vector4T(val-v.x, val-v.y, val-v.z, val-v.w);
      }
      inline friend Vector4T operator-(const Vector4T &v1,const Vector4T &v2)
      {
         return Vector4T(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z, v1.w-v2.w);
      }

      inline friend Vector4T operator/(const Vector4T &v,const T &val)
      {
         return Vector4T(v.x/val, v.y/val, v.z/val, v.w/val);
      }
      inline friend Vector4T operator/(const T &val,const Vector4T &v)
      {
         return Vector4T(val/v.x, val/v.y, val/v.z, val/v.w);
      }
      inline friend Vector4T operator/(const Vector4T &v1,const Vector4T &v2)
      {
         return Vector4T(v1.x/v2.x, v1.y/v2.y, v1.z/v2.z, v1.w/v2.w);
      }
      inline Vector4T &operator=(T c)
      {
         x = c;
         y = c;
         z = c;
		   w = c;
         return *this;
      }
      inline Vector4T &operator,(T c)
      {
         y=z;
         z=w;
         w=c;
         return *this;
      }

      KF_API static const Vector4T<T> ZERO;
      KF_API static const Vector4T<T> UNIT_X;
      KF_API static const Vector4T<T> UNIT_Y;
      KF_API static const Vector4T<T> UNIT_Z;
      KF_API static const Vector4T<T> UNIT_W;
      KF_API static const Vector4T<T> NEGATIVE_UNIT_X;
      KF_API static const Vector4T<T> NEGATIVE_UNIT_Y;
      KF_API static const Vector4T<T> NEGATIVE_UNIT_Z;
      KF_API static const Vector4T<T> NEGATIVE_UNIT_W;
   };

   template <typename T1, typename T2>
   T1 convertVector4(const T2 &v)
   {
      T1 result;
      result.x = v.x;
      result.y = v.y;
      result.z = v.z;
      result.w = v.w;
      return result;
   }


   typedef Vector4T<float>  Vector4f;
   typedef Vector4T<double> Vector4d;
   typedef Vector4T<float>  Vector4;


}

//#include "kf_vector.inl"

#endif

