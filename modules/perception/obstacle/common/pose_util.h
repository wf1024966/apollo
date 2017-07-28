// Copyright 2016 Baidu Inc. All Rights Reserved.
// @author: wang jun(wangjun21@baidu.com)
//          zhang ye(zhangye09@baidu.com)
// @file: pose_util.h
// @brief: pose util

#ifndef ADU_PERCEPTION_OBSTACLE_COMMON_POSE_UTIL_H
#define ADU_PERCEPTION_OBSTACLE_COMMON_POSE_UTIL_H

#include <Eigen/Core>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace apollo {
namespace perception {

template <typename T>
void quaternion_to_rotation_matrix(const T * quat, T * R) {
    T x2 = quat[0] * quat[0];
    T xy = quat[0] * quat[1];
    T rx = quat[3] * quat[0];
    T y2 = quat[1] * quat[1];
    T yz = quat[1] * quat[2];
    T ry = quat[3] * quat[1];
    T z2 = quat[2] * quat[2];
    T zx = quat[2] * quat[0];
    T rz = quat[3] * quat[2];
    T r2 = quat[3] * quat[3];
    R[0] = r2 + x2 - y2 - z2;         // fill diagonal terms
    R[4] = r2 - x2 + y2 - z2;
    R[8] = r2 - x2 - y2 + z2;
    R[3] = 2 * (xy + rz);             // fill off diagonal terms
    R[6] = 2 * (zx - ry);
    R[7] = 2 * (yz + rx);
    R[1] = 2 * (xy - rz);
    R[2] = 2 * (zx + ry);
    R[5] = 2 * (yz - rx);
}

bool read_pose_file(const std::string& filename, 
        Eigen::Matrix4d& pose, 
        int& frame_id, 
        double& time_stamp);

bool read_pose_file_mat12(const std::string& filename, 
        Eigen::Matrix4d& pose, 
        int& frame_id, 
        double& time_stamp);

} // namespace perception
} // namespace apollo

#endif // ADU_PERCEPTION_OBSTACLE_COMMON_POSE_UTIL_H
