#ifndef KF_MATRIX4_HEADER
#define KF_MATRIX4_HEADER

#include "kf/kf.h"
#include "kf/kf_vector.h"

namespace kf
{
   template<typename T>
   class Matrix4T
   {
   public:
      enum {rows = 4,columns = 4};

      T m[rows][columns];

      Matrix4T()
      {
      }

      Matrix4T(T m11, T m12, T m13, T m14, T m21, T m22, T m23, T m24, T m31, T m32, T m33, T m34, T m41, T m42, T m43, T m44)
      {
         m[0][0] = m11;
         m[0][1] = m12;
         m[0][2] = m13;
         m[0][3] = m14;
         m[1][0] = m21;
         m[1][1] = m22;
         m[1][2] = m23;
         m[1][3] = m24;
         m[2][0] = m31;
         m[2][1] = m32;
         m[2][2] = m33;
         m[2][3] = m34;
         m[3][0] = m41;
         m[3][1] = m42;
         m[3][2] = m43;
         m[3][3] = m44;
      }

      Matrix4T operator*(const Matrix4T &mat) const
      {
         return Matrix4T(m[0][0]*mat.m[0][0] + m[0][1]*mat.m[1][0] + m[0][2]*mat.m[2][0] + m[0][3]*mat.m[3][0],
                        m[0][0]*mat.m[0][1] + m[0][1]*mat.m[1][1] + m[0][2]*mat.m[2][1] + m[0][3]*mat.m[3][1],
                        m[0][0]*mat.m[0][2] + m[0][1]*mat.m[1][2] + m[0][2]*mat.m[2][2] + m[0][3]*mat.m[3][2],
                        m[0][0]*mat.m[0][3] + m[0][1]*mat.m[1][3] + m[0][2]*mat.m[2][3] + m[0][3]*mat.m[3][3],

                        m[1][0]*mat.m[0][0] + m[1][1]*mat.m[1][0] + m[1][2]*mat.m[2][0] + m[1][3]*mat.m[3][0],
                        m[1][0]*mat.m[0][1] + m[1][1]*mat.m[1][1] + m[1][2]*mat.m[2][1] + m[1][3]*mat.m[3][1],
                        m[1][0]*mat.m[0][2] + m[1][1]*mat.m[1][2] + m[1][2]*mat.m[2][2] + m[1][3]*mat.m[3][2],
                        m[1][0]*mat.m[0][3] + m[1][1]*mat.m[1][3] + m[1][2]*mat.m[2][3] + m[1][3]*mat.m[3][3],

                        m[2][0]*mat.m[0][0] + m[2][1]*mat.m[1][0] + m[2][2]*mat.m[2][0] + m[2][3]*mat.m[3][0],
                        m[2][0]*mat.m[0][1] + m[2][1]*mat.m[1][1] + m[2][2]*mat.m[2][1] + m[2][3]*mat.m[3][1],
                        m[2][0]*mat.m[0][2] + m[2][1]*mat.m[1][2] + m[2][2]*mat.m[2][2] + m[2][3]*mat.m[3][2],
                        m[2][0]*mat.m[0][3] + m[2][1]*mat.m[1][3] + m[2][2]*mat.m[2][3] + m[2][3]*mat.m[3][3],

                        m[3][0]*mat.m[0][0] + m[3][1]*mat.m[1][0] + m[3][2]*mat.m[2][0] + m[3][3]*mat.m[3][0],
                        m[3][0]*mat.m[0][1] + m[3][1]*mat.m[1][1] + m[3][2]*mat.m[2][1] + m[3][3]*mat.m[3][1],
                        m[3][0]*mat.m[0][2] + m[3][1]*mat.m[1][2] + m[3][2]*mat.m[2][2] + m[3][3]*mat.m[3][2],
                        m[3][0]*mat.m[0][3] + m[3][1]*mat.m[1][3] + m[3][2]*mat.m[2][3] + m[3][3]*mat.m[3][3]);
      }
      Matrix4T operator+(const Matrix4T &mat) const
      {
         return Matrix4T(m[0][0]+mat.m[0][0], m[0][1]+mat.m[0][1], m[0][2]+mat.m[0][2], m[0][3]+mat.m[0][3],
						 m[1][0]+mat.m[1][0], m[1][1]+mat.m[1][1], m[1][2]+mat.m[1][2], m[1][3]+mat.m[1][3],
						 m[2][0]+mat.m[2][0], m[2][1]+mat.m[2][1], m[2][2]+mat.m[2][2], m[2][3]+mat.m[2][3],
						 m[3][0]+mat.m[3][0], m[3][1]+mat.m[3][1], m[3][2]+mat.m[3][2], m[3][3]+mat.m[3][3]);
      }
      Matrix4T operator-(const Matrix4T &mat) const
      {
         return Matrix4T(m[0][0]-mat.m[0][0], m[0][1]-mat.m[0][1], m[0][2]-mat.m[0][2], m[0][3]-mat.m[0][3],
						 m[1][0]-mat.m[1][0], m[1][1]-mat.m[1][1], m[1][2]-mat.m[1][2], m[1][3]-mat.m[1][3],
						 m[2][0]-mat.m[2][0], m[2][1]-mat.m[2][1], m[2][2]-mat.m[2][2], m[2][3]-mat.m[2][3],
						 m[3][0]-mat.m[3][0], m[3][1]-mat.m[3][1], m[3][2]-mat.m[3][2], m[3][3]-mat.m[3][3]);
      }
      kf::Vector3T<T> operator * ( const kf::Vector3T<T> &v ) const
        {
            T inv = 1.0 / ( m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] );
            return kf::Vector3T<T>(( m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] ) * inv, ( m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] ) * inv, ( m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] ) * inv);
        }
        kf::Vector4T<T> operator * (const kf::Vector4T<T>& v) const
        {
            return kf::Vector3T<T>( m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,  m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w, m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w);
        }

      Matrix4T transpose()
      {
         return Matrix4T(m[0][0],m[1][0],m[2][0],m[3][0],m[0][1],m[1][1],m[2][1],m[3][1],m[0][2],m[1][2],m[2][2],m[3][2],m[0][3],m[1][3],m[2][3],m[3][3]);
      }

	  kf::Vector4T<T> row(kf::dword i) const
	  {
		  return kf::Vector4T<T>(m[i][0], m[i][1], m[i][2], m[i][3]);
	  }
	  kf::Vector4T<T> column(kf::dword i) const
	  {
		  return kf::Vector4T<T>(m[0][i], m[1][i], m[2][i], m[3][i]);
	  }
	  void row(kf::dword i, kf::Vector4T<T> v)
	  {
		  m[i][0] = v.x;
        m[i][1] = v.y;
        m[i][2] = v.z;
        m[i][3] = v.w;
	  }
	  void column(kf::dword i, kf::Vector4T<T> v)
	  {
		  m[0][i] = v.x;
        m[1][i] = v.y;
        m[2][i] = v.z;
        m[3][i] = v.w;
	  }
	  T *operator[](kf::dword i)
	  {
		  return m[i];
	  }
	  const T *operator[](kf::dword i) const
	  {
		  return m[i];
	  }
	  T &operator()(kf::dword j,kf::dword i)
	  {
		  return m[j][i];
	  }
	  const T &operator()(kf::dword j,kf::dword i) const
	  {
		  return m[j][i];
	  }

     kf::Vector3 xaxis()
     {
        return kf::Vector3(m[0][0],m[1][0],m[2][0]);
     }
     void xaxis(const kf::Vector3 &v)
     {
        m[0][0] = v.x;
        m[1][0] = v.y;
        m[2][0] = v.z;
     }
     kf::Vector3 yaxis()
     {
        return kf::Vector3(m[0][1],m[1][1],m[2][1]);
     }
     void yaxis(const kf::Vector3 &v)
     {
        m[0][1] = v.x;
        m[1][1] = v.y;
        m[2][1] = v.z;
     }
     kf::Vector3 zaxis()
     {
        return kf::Vector3(m[0][2],m[1][2],m[2][2]);
     }
     void zaxis(const kf::Vector3 &v)
     {
        m[0][2] = v.x;
        m[1][2] = v.y;
        m[2][2] = v.z;
     }
     kf::Vector3 translation()
     {
        return kf::Vector3(m[0][3],m[1][3],m[2][3]);
     }
     void translation(const kf::Vector3 &v)
     {
        m[0][3] = v.x;
        m[1][3] = v.y;
        m[2][3] = v.z;
     }

	  inline friend std::ostream &operator<<(std::ostream &o, const Matrix4T &mat)
      {
         o << "[" << mat.row(0) << "," << mat.row(1) << "," << mat.row(2) << "," << mat.row(3) << "]";
         return o;
      }



      KF_API static const Matrix4T<T> ZERO;
      KF_API static const Matrix4T<T> IDENTITY;

   };

   typedef Matrix4T<float> Matrix4;
}
#endif
