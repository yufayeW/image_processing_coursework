#include "attitude.h"
#include "Eigen/Geometry"

Eigen::Quaterniond Attitude::toQuaternion() const
{
  Eigen::AngleAxisd roll(x_rot, Eigen::Vector3d::UnitX());
  Eigen::AngleAxisd pitch(y_rot, Eigen::Vector3d::UnitY());
  Eigen::AngleAxisd yaw(z_rot, Eigen::Vector3d::UnitZ());
  return Eigen::Quaterniond(yaw * pitch * roll);
  // // Todo: Implement this correctly using Eigen::AngleAxisd (Z->Y->X).
  // return Eigen::Quaterniond(Eigen::AngleAxisd(0.0, Eigen::Vector3d::UnitX()));
}

Sophus::SO3d Attitude::toSO3() const
{
  return Sophus::SO3d(toQuaternion());
}

std::istream &operator>>(std::istream &is, Attitude &att)
{
  is >> att.x_rot >> att.y_rot >> att.z_rot;

  if (!is)
  {
    throw std::runtime_error("Could not read Attitude data");
  }

  return is;
}

std::ostream &operator<<(std::ostream &os, const Attitude &att)
{
  os << "x_rot: " << att.x_rot << "\n"
     << "y_rot: " << att.y_rot << "\n"
     << "z_rot: " << att.z_rot << "\n";

  return os;
}
