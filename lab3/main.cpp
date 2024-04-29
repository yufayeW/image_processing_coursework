#include <Eigen/Dense>
#include <Eigen/Core>
#include <opencv2/core/eigen.hpp>
#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat mat = cv::Mat::zeros(200, 200, CV_32FC3);
    cv::rectangle(mat, cv::Point(50, 50), cv::Point(150, 150), cv::Scalar(0, 255, 0), -1);
    cv::cvtColor(mat, mat, cv::COLOR_BGR2GRAY);

    Eigen::MatrixXf eigenMatrix;
    cv::cv2eigen(mat, eigenMatrix);

    double angle = -15 * M_PI / 180;
    Eigen::Matrix2f rotationMatrix;
    rotationMatrix << cos(angle), -sin(angle),
        sin(angle), cos(angle);
    Eigen::MatrixXf rotatedMatrix = Eigen::MatrixXf::Zero(eigenMatrix.rows(), eigenMatrix.cols());

    for (int i = 0; i < eigenMatrix.rows(); ++i)
    {
        for (int j = 0; j < eigenMatrix.cols(); ++j)
        {
            Eigen::Vector2f point(i, j);
            Eigen::Vector2f rotatedPoint = rotationMatrix * point;
            if (rotatedPoint[0] >= 0 && rotatedPoint[0] < eigenMatrix.rows() &&
                rotatedPoint[1] >= 0 && rotatedPoint[1] < eigenMatrix.cols())
            {
                rotatedMatrix.coeffRef(rotatedPoint[0], rotatedPoint[1]) = eigenMatrix(i, j);
            }
        }
    }
    cv::Mat rotatedMat;
    cv::eigen2cv(rotatedMatrix, rotatedMat);
    cv::imshow("Original Image", mat);
    cv::imshow("Rotated Image", rotatedMat);
    cv::waitKey(0);

    return 0;
}