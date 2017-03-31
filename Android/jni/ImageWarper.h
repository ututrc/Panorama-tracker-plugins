#pragma once

#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/stitching/warpers.hpp>
#include <chrono>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace cv;
class ImageWarper
{
private:

	detail::CylindricalWarper warper;
	int interpolation_method_ = INTER_NEAREST;

	Mat_<float> K;
	Mat_<float> dist_coeffs;
	float radiansToDegrees(float radians);
	float degreesToRadians(float degrees);
	Mat getMask(Mat warpedImage);
	Mat_<float> getRotationMatrix(float yaw, float pitch, float roll);
	Mat undistortImage(Mat image);

public:
	ImageWarper();
	ImageWarper(float warper_scale, bool use_android);

	//Warp image and return a binary mask_current_view_ 
	Mat warpImageCylindrical(Mat image, float yaw, float pitch, float roll, Mat &result);
};
