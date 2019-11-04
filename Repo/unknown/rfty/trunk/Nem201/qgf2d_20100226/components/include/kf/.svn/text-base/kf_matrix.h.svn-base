#ifndef KF_MATRIX_HEADER
#define KF_MATRIX_HEADER

#include "kf/kf.h"
#include "kf/kf_matrix3.h"
#include "kf/kf_matrix4.h"

namespace kf
{
   inline kf::Matrix3 convertMatrix4ToMatrix3(const kf::Matrix4 &mat)
   {
      return kf::Matrix3(
         mat.m[0][0],mat.m[0][1],mat.m[0][2],
         mat.m[1][0],mat.m[1][1],mat.m[1][2],
         mat.m[2][0],mat.m[2][1],mat.m[2][2]);
   }

   inline kf::Matrix4 convertMatrix3ToMatrix4(const kf::Matrix3 &mat)
   {
      return kf::Matrix4(
         mat.m[0][0],mat.m[0][1],mat.m[0][2],0,
         mat.m[1][0],mat.m[1][1],mat.m[1][2],0,
         mat.m[2][0],mat.m[2][1],mat.m[2][2],0,
         0,0,0,1);
   }
   inline void insertMatrix3IntoMatrix4(kf::Matrix4 &mat4, const kf::Matrix3 &mat3)
   {
      mat4(0,0) = mat3(0,0);
      mat4(0,1) = mat3(0,1);
      mat4(0,2) = mat3(0,2);
      mat4(1,0) = mat3(1,0);
      mat4(1,1) = mat3(1,1);
      mat4(1,2) = mat3(1,2);
      mat4(2,0) = mat3(2,0);
      mat4(2,1) = mat3(2,1);
      mat4(2,2) = mat3(2,2);
   }

   inline kf::Quaternion convertMatrix3ToQuaternion(const kf::Matrix3 &mat)
   {
      kf::Quaternion q;

        float fTrace = mat.m[0][0]+mat.m[1][1]+mat.m[2][2];
        float fRoot;

        if ( fTrace > 0.0 )
        {
            // |w| > 1/2, may as well choose w > 1/2
            fRoot = sqrt(fTrace + 1.0);  // 2w
            q.w = 0.5*fRoot;
            fRoot = 0.5/fRoot;  // 1/(4w)
            q.x = (mat.m[2][1]-mat.m[1][2])*fRoot;
            q.y = (mat.m[0][2]-mat.m[2][0])*fRoot;
            q.z = (mat.m[1][0]-mat.m[0][1])*fRoot;
        }
        else
        {
            // |w| <= 1/2
            static size_t s_iNext[3] = { 1, 2, 0 };
            size_t i = 0;
            if ( mat.m[1][1] > mat.m[0][0] )
                i = 1;
            if ( mat.m[2][2] > mat.m[i][i] )
                i = 2;
            size_t j = s_iNext[i];
            size_t k = s_iNext[j];

            fRoot = sqrt(mat.m[i][i]-mat.m[j][j]-mat.m[k][k] + 1.0);
            float* apkQuat[3] = { &q.x, &q.y, &q.z };
            *apkQuat[i] = 0.5*fRoot;
            fRoot = 0.5/fRoot;
            q.w = (mat.m[k][j]-mat.m[j][k])*fRoot;
            *apkQuat[j] = (mat.m[j][i]+mat.m[i][j])*fRoot;
            *apkQuat[k] = (mat.m[k][i]+mat.m[i][k])*fRoot;
        }
        return q;
    }

   inline kf::Matrix4 convertQuaternionToMatrix4(const kf::Quaternion &q)
   {
      float xx = q.x * q.x;
      float xy = q.x * q.y;
      float xz = q.x * q.z;
      float xw = q.x * q.w;
      float yy = q.y * q.y;
      float yz = q.y * q.z;
      float yw = q.y * q.w;
      float zz = q.z * q.z;
      float zw = q.z * q.w;

      return kf::Matrix4(1 - 2 * ( yy + zz ),     2 * ( xy - zw ),     2 * ( xz + yw ), 0,
                             2 * ( xy + zw ), 1 - 2 * ( xx + zz ),     2 * ( yz - xw ), 0,
                             2 * ( xz - yw ),     2 * ( yz + xw ), 1 - 2 * ( xx + yy ), 0,
                                           0,                   0,                   0, 1);
   }
   inline kf::Matrix3 convertQuaternionToMatrix3(const kf::Quaternion &q)
   {
      float xx = q.x * q.x;
      float xy = q.x * q.y;
      float xz = q.x * q.z;
      float xw = q.x * q.w;
      float yy = q.y * q.y;
      float yz = q.y * q.z;
      float yw = q.y * q.w;
      float zz = q.z * q.z;
      float zw = q.z * q.w;

      return kf::Matrix3(1 - 2 * ( yy + zz ),     2 * ( xy - zw ),     2 * ( xz + yw ),
                             2 * ( xy + zw ), 1 - 2 * ( xx + zz ),     2 * ( yz - xw ),
                             2 * ( xz - yw ),     2 * ( yz + xw ), 1 - 2 * ( xx + yy ));
   }

   
}
#endif
