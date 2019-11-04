#ifndef KF_QUATERNION_HEADER
#define KF_QUATERNION_HEADER

#include "kf/kf.h"
#include "kf/kf_vector3.h"

namespace ogre
{
   class SceneNode;
   class MovableObject;
}

namespace kf
{
   template<typename T>
   class QuaternionT
   {
   public:
      T w;
      T x;
      T y;
      T z;

      QuaternionT()
      {
      }

      QuaternionT(const T &ww, const T &xx, const T &yy, const T &zz): w(ww),x(xx),y(yy),z(zz)
      {         
      }

      QuaternionT(const T &angle, const kf::Vector3T<T> &axis)
      {
         kf::Vector3T<T> naxis = kf::normalise(axis);
         T sin_a = sin( angle / T(2) );
         w = cos( angle / T(2) );
         x = naxis.x * sin_a;
         y = naxis.y * sin_a;
         z = naxis.z * sin_a;
      }

      QuaternionT operator*(const QuaternionT &q) const
      {
         return QuaternionT(w * q.w - x * q.x - y * q.y - z * q.z,
                            w * q.x + x * q.w + y * q.z - z * q.y,
                            w * q.y + y * q.w + z * q.x - x * q.z,
                            w * q.z + z * q.w + x * q.y - y * q.x);      
      }

      kf::Vector3T<T> operator*(const kf::Vector3T<T> &v) const
      {
         kf::Vector3T<T> uv, uuv;
		   kf::Vector3T<T> qvec(x, y, z);
		   uv = qvec.cross(v);
		   uuv = qvec.cross(uv);
		   uv *= (2.0f * w);
		   uuv *= 2.0f;
	   	return v + uv + uuv;
      }

      QuaternionT operator+(const QuaternionT &q) const
      {
         return QuaternionT(w + q.w, x + q.x, y + q.y, z + q.z);
      }

      QuaternionT operator-(const QuaternionT &q) const
      {
         return QuaternionT(w - q.w, x - q.x, y - q.y, z - q.z);
      }

      void conjugate()
      {
         x = -x;
         y = -y;
         z = -z;
      }

      T magnitude() const
      {
         return sqrt(w * w + x * x + y * y + z * z);
      }

      void normalise()
      {
         T mag = magnitude();
         w /= mag;
         x /= mag;
         y /= mag;
         z /= mag;
      }

      T scalar() const
      {
         return w;
      }

      void scalar(const T &val)
      {
         w = val;
      }

      Vector3T<T> vector() const
      {
         return Vector3T<T>(x,y,z);
      }

      void vector(const Vector3T<T> &val)
      {
         x = val.x;
         y = val.y;
         z = val.z;
      }

      inline friend std::ostream &operator<<(std::ostream &o, const QuaternionT<T> &q)
      {
         o << "{" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << "}";
         return o;
      }

	   KF_API static const QuaternionT<T> ZERO;
	   KF_API static const QuaternionT<T> IDENTITY;
   };
      
   typedef QuaternionT<float> Quaternion;

   template<typename T>
   QuaternionT<T> conjugate(const QuaternionT<T> &q)
   {
      return QuaternionT<T>(q.w, -q.x, -q.y, -q.z);
   }
   
   template<typename T>
   QuaternionT<T> normalise(const QuaternionT<T> &q)
   {
      T mag = q.magnitude();
      return QuaternionT<T>(q.w / mag, q.x / mag, q.y / mag, q.z / mag);
   }

   template <typename T1, typename T2>
   T1 convertQuaternion(const T2 &q)
   {
      T1 result;
      result.x = q.x;
      result.y = q.y;
      result.z = q.z;
      result.w = q.w;
      return result;
   }

}
#endif
