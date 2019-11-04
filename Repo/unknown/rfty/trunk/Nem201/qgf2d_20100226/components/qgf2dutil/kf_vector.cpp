#include "kf/kf_math.h"
#include "kf/kf_vector.h"

namespace kf
{
    KF_API const kf::Vector2 kf::Vector2::ZERO(0,0);
    KF_API const kf::Vector3 kf::Vector3::ZERO(0,0,0);
    KF_API const kf::Vector4 kf::Vector4::ZERO(0,0,0,0);

    KF_API const kf::Vector2 kf::Vector2::UNIT_X(1,0);
    KF_API const kf::Vector2 kf::Vector2::UNIT_Y(0,1);
    KF_API const kf::Vector2 kf::Vector2::NEGATIVE_UNIT_X(-1,0);
    KF_API const kf::Vector2 kf::Vector2::NEGATIVE_UNIT_Y(0,-1);

    KF_API const kf::Vector3 kf::Vector3::UNIT_X(1,0,0);
    KF_API const kf::Vector3 kf::Vector3::UNIT_Y(0,1,0);
    KF_API const kf::Vector3 kf::Vector3::UNIT_Z(0,0,1);
    KF_API const kf::Vector3 kf::Vector3::NEGATIVE_UNIT_X(-1,0,0);
    KF_API const kf::Vector3 kf::Vector3::NEGATIVE_UNIT_Y(0,-1,0);
    KF_API const kf::Vector3 kf::Vector3::NEGATIVE_UNIT_Z(0,0,-1);

    KF_API const kf::Vector4 kf::Vector4::UNIT_X(1,0,0,0);
    KF_API const kf::Vector4 kf::Vector4::UNIT_Y(0,1,0,0);
    KF_API const kf::Vector4 kf::Vector4::UNIT_Z(0,0,1,0);
    KF_API const kf::Vector4 kf::Vector4::UNIT_W(0,0,0,1);
    KF_API const kf::Vector4 kf::Vector4::NEGATIVE_UNIT_X(-1,0,0,0);
    KF_API const kf::Vector4 kf::Vector4::NEGATIVE_UNIT_Y(0,-1,0,0);
    KF_API const kf::Vector4 kf::Vector4::NEGATIVE_UNIT_Z(0,0,-1,0);
    KF_API const kf::Vector4 kf::Vector4::NEGATIVE_UNIT_W(0,0,0,-1);
}
