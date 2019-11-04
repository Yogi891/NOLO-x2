#ifndef KF_VECTOR3_HEADER
#define KF_VECTOR3_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"
#include <ostream>

namespace kf
{
   template<typename T>
   class Vector3T
   {
   public:
      typedef T type;
      T x;
      T y;
      T z;
      inline Vector3T(): x(0),y(0),z(0)
      {
      }
      inline Vector3T(const Vector3T &c): x(c.x),y(c.y),z(c.z)
      {
      }
      explicit inline Vector3T(T xyz): x(xyz),y(xyz),z(xyz)
      {
      }
      template<typename T2>
         explicit inline Vector3T(const T2 *p): x(T(p[0])),y(T(p[1])),z(T(p[2]))
      {
      }
      inline Vector3T(T xx, T yy, T zz): x(xx),y(yy),z(zz)
      {
      }

      inline T operator [] ( unsigned int i ) const
      {
         return *(&x+i);
      }

      inline T& operator [] ( unsigned int i )
      {
         return *(&x+i);
      }

      inline Vector3T operator*=(T c)
      {
         x *= c;
         y *= c;
         z *= c;
         return *this;
      }
      inline Vector3T operator/=(T c)
      {
         x /= c;
         y /= c;
         z /= c;
         return *this;
      }
      inline Vector3T operator+=(const Vector3T &c)
      {
         x += c.x;
         y += c.y;
         z += c.z;
         return *this;
      }
      inline Vector3T operator-=(const Vector3T &c)
      {
         x -= c.x;
         y -= c.y;
         z -= c.z;
         return *this;
      }
      inline Vector3T operator*=(const Vector3T &c)
      {
         x *= c.x;
         y *= c.y;
         z *= c.z;
         return *this;
      }
      inline Vector3T operator/=(const Vector3T &c)
      {
         x /= c.x;
         y /= c.y;
         z /= c.z;
         return *this;
      }
      inline Vector3T operator=(const T *p)
      {
         x = p[0];
         y = p[1];
         z = p[2];
         return *this;
      }
      inline Vector3T operator=(const Vector3T<T> &v)
      {
         x = v.x;
         y = v.y;
         z = v.z;
         return *this;
      }
      inline Vector3T normalise() const
      {
         T l;
         Vector3T temp;
         l=T(sqrt(x*x+y*y+z*z));
         if(l!=0.0)
         {
            temp.set(x/l,y/l,z/l);
         }
         return temp;
      }
      inline T length() const
      {
         return sqrt(x*x+y*y+z*z);
      }
      inline T length_squared() const
      {
         return x*x+y*y+z*z;
      }
      inline Vector3T swiz(int comp1, int comp2, int comp3) const
      {
         return Vector3T( comp1 == 0 ? x : (comp1 == 1 ? y : (comp1 == 2 ? z : 0)),
            comp2 == 0 ? x : (comp2 == 1 ? y : (comp2 == 2 ? z : 0)),
            comp3 == 0 ? x : (comp3 == 1 ? y : (comp3 == 2 ? z : 0)));
      }
      inline void set(const Vector3T &value)
      {
         x = value.x;
         y = value.y;
         z = value.z;
      }
      inline void set(T xyz)
      {
         x = y = z = xyz;
      }
      inline void set(T xx, T yy, T zz)
      {
         x = xx;
         y = yy;
         z = zz;
      }
      template<typename T2>
         inline void set(const T2 *p)
      {
         x = T(p[0]);
         y = T(p[1]);
         z = T(p[2]);
      }
      inline static T dot(const Vector3T &v1, const Vector3T &v2)
      {
         return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
      }
      inline static Vector3T cross(const Vector3T &v1, const Vector3T &v2)
      {
         return Vector3T(v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x);
      }

      inline T dot(const Vector3T &v)
      {
         return x * v.x + y * v.y + z * v.z;
      }
      inline Vector3T cross(const Vector3T &v)
      {
         return Vector3T(y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x);
      }

      inline friend std::ostream &operator<<(std::ostream &o, const Vector3T &v)
      {
         o << "<" << v.x << ", " << v.y << ", " << v.z << ">";
         return o;
      }

      inline friend Vector3T operator*(const Vector3T &v,const T &val)
      {
         return Vector3T(v.x*val,v.y*val,v.z*val);
      }
      inline friend Vector3T operator*(const T &val,const Vector3T &v)
      {
         return Vector3T(val*v.x, val*v.y, val*v.z);
      }
      inline friend Vector3T operator*(const Vector3T &v1,const Vector3T &v2)
      {
         return Vector3T(v1.x*v2.x,v1.y*v2.y,v1.z*v2.z);
      }

      inline friend Vector3T operator+(const Vector3T &v,const T &val)
      {
         return Vector3T(v.x+val,v.y+val,v.z+val);
      }
      inline friend Vector3T operator+(const T &val,const Vector3T &v)
      {
         return Vector3T(val+v.x, val+v.y, val+v.z);
      }
      inline friend Vector3T operator+(const Vector3T &v1,const Vector3T &v2)
      {
         return Vector3T(v1.x+v2.x,v1.y+v2.y,v1.z+v2.z);
      }

      inline friend Vector3T operator-(const Vector3T &v,const T &val)
      {
         return Vector3T(v.x-val,v.y-val,v.z-val);
      }
      inline friend Vector3T operator-(const T &val,const Vector3T &v)
      {
         return Vector3T(val-v.x, val-v.y, val-v.z);
      }
      inline friend Vector3T operator-(const Vector3T &v1,const Vector3T &v2)
      {
         return Vector3T(v1.x-v2.x,v1.y-v2.y,v1.z-v2.z);
      }

      inline friend Vector3T operator/(const Vector3T &v,const T &val)
      {
         return Vector3T(v.x/val,v.y/val,v.z/val);
      }
      inline friend Vector3T operator/(const T &val,const Vector3T &v)
      {
         return Vector3T(val/v.x, val/v.y, val/v.z);
      }
      inline friend Vector3T operator/(const Vector3T &v1,const Vector3T &v2)
      {
         return Vector3T(v1.x/v2.x,v1.y/v2.y,v1.z/v2.z);
      }
      inline Vector3T &operator=(T c)
      {
         x = c;
         y = c;
         z = c;
         return *this;
      }
      inline Vector3T &operator,(T c)
      {
         y=z;
         z=c;
         return *this;
      }
   
      KF_API static const Vector3T<T> ZERO;
      KF_API static const Vector3T<T> UNIT_X;
      KF_API static const Vector3T<T> UNIT_Y;
      KF_API static const Vector3T<T> UNIT_Z;
      KF_API static const Vector3T<T> NEGATIVE_UNIT_X;
      KF_API static const Vector3T<T> NEGATIVE_UNIT_Y;
      KF_API static const Vector3T<T> NEGATIVE_UNIT_Z;
   };

   typedef Vector3T<float>  Vector3f;
   typedef Vector3T<double> Vector3d;
   typedef Vector3T<float>  Vector3;

   template <typename T1, typename T2>
   T1 convertVector3(const T2 &v)
   {
      T1 result;
      result.x = v.x;
      result.y = v.y;
      result.z = v.z;
      return result;
   }

   template<typename T>
   inline Vector3T<T> normalise(const Vector3T<T> &v)
   {
      T l;
      Vector3T<T> temp;
      l = v.length();

      if(l != 0.0)
      {
         return Vector3T<T>(v.x / l, v.y / l, v.z / l);
      }
      return Vector3T<T>(0, 0, 0);
   }

}

#endif

