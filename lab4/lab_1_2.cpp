#include "lab_1_2.h"

#include "dataset.h"
#include "local_coordinate_system.h"
#include "viewer_3d.h"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

Lab_1_2::Lab_1_2(const std::string &data_path)
    : data_path_{data_path}, window_name_{"World point in camera"}
{
}

void Lab_1_2::run()
{
  // Set up dataset.
  Dataset dataset{data_path_};

  // Define local coordinate system based on the position of a light pole.
  const GeodeticPosition light_pole_position{59.963516, 10.667307, 321.0};
  const LocalCoordinateSystem local_system(light_pole_position);

  // Construct viewers.
  cv::namedWindow(window_name_);
  Viewer3D viewer;
  int img_num = 0;
  // Process each image in the dataset.
  for (DataElement element{}; dataset >> element; ++img_num)
  {
    // Compute the pose of the body in the local coordinate system.
    // Todo: Finish Attitude::toQuaternion().
    const Sophus::SE3d pose_local_body = local_system.toLocalPose(element.body_position_in_geo,
                                                                  element.body_attitude_in_geo.toSO3());

    // Add body coordinate axis to the 3D viewer.
    // Todo: Write line of code below to add body to viewer.
    viewer.addBody(pose_local_body, img_num);
    // Compute the pose of the camera relative to the body.
    // Todo: Finish CartesianPosition::toVector().
    // Todo: Construct pose_body_camera correctly using element.
    Eigen::Vector3d translation(element.camera_position_in_body.x, element.camera_position_in_body.y, element.camera_position_in_body.z);
    const Sophus::SE3d pose_body_camera(Eigen::Quaterniond::Identity(), translation);
    ;

    // Compute the pose of the camera relative to the local coordinate system.
    // Todo: Construct pose_local_camera correctly using the poses above.
    const Sophus::SE3d pose_local_camera = pose_local_body * pose_body_camera;

    // Construct a camera model based on the intrinsic calibration and camera pose.
    // Todo: Finish Intrinsics::toCalibrationMatrix().
    // Todo: Finish Intrinsics::toDistortionVector().
    const PerspectiveCameraModel camera_model{element.intrinsics.toCalibrationMatrix(),
                                              pose_local_camera,
                                              element.intrinsics.toDistortionCoefficientVector()};

    // Undistort image.
    // Todo: Undistort image using the camera model. Why should we undistort the image?
    cv::Mat undistorted_img = camera_model.undistortImage(element.image);

    // Project world point (the origin) into the image.
    // Todo: Finish PerspectiveCameraModel::computeCameraProjectionMatrix().
    // Todo: Finish PerspectiveCameraModel::projectWorldPoint().
    // Todo: Optionally finish PerspectiveCameraModel::projectWorldPoints().
    const Eigen::Vector2d pix_pos = camera_model.projectWorldPoint(Eigen::Vector3d::Zero());

    // Draw a marker in the image at the projected position.
    const Eigen::Vector2i pix_pos_int = (pix_pos.array().round()).cast<int>();
    cv::drawMarker(undistorted_img, {pix_pos_int.x(), pix_pos_int.y()}, {0., 0., 255.}, cv::MARKER_CROSS, 40, 3);

    // Show the image.
    // Todo: Write line of code below to show the image with the marker.
    cv::imshow(window_name_, undistorted_img);

    // Add the camera to the 3D viewer.
    viewer.addBody(pose_local_body, img_num);

    // Update the windows.
    viewer.spinOnce();
    cv::waitKey(100);
  }

  // Remove image viewer.
  cv::destroyWindow(window_name_);

  // Run 3D viewer until stopped.
  viewer.spin();
}
