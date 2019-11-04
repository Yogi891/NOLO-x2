#include "kf/kf_math.h"
#include "kf/kf_matrix3.h"

namespace kf
{
   KF_API const Matrix3 Matrix3::ZERO(0,0,0,0,0,0,0,0,0);
   KF_API const Matrix3 Matrix3::IDENTITY(1,0,0,0,1,0,0,0,1);
}
