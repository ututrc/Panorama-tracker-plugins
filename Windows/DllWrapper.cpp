#include "DllWrapper.h"
#include <chrono>

Mat getMatFromMonoArray(MonoArray* frame){
	Mat img(image_height_, image_width_, CV_8UC3, (unsigned char*)frame);
	Mat rotated;
	//Rotate 180 degrees since images are rotated for some reason
	Point center(img.cols / 2, img.rows / 2);
	double angle = 180;
	Mat corrected;
	Mat rot_mat = getRotationMatrix2D(center, angle, 1);
	warpAffine(img, rotated, rot_mat, img.size());
	flip(rotated, corrected, 1);
	return corrected;
}

void TestOpencvEditor(MonoArray* image, int image_height, int image_width)
{
	image_height_ = image_height;
	image_width_ = image_width;
	Mat test_image = getMatFromMonoArray(image);
	imshow("Editor opencv test", test_image);
}

void InitializeTracker(MonoArray* image, int image_height, int image_width)
{
	image_height_ = image_height;
	image_width_ = image_width;
	Mat img_mat = getMatFromMonoArray(image);
	panorama_tracker_.InitializeMap(img_mat, false);
}

void CalculateOrientation(MonoArray* image)
{
	auto start_hr = std::chrono::high_resolution_clock::now();
	Mat img_mat = getMatFromMonoArray(image);
	panorama_tracker_.CalculateOrientation(img_mat);
	auto end_hr = std::chrono::high_resolution_clock::now();
	auto diff_hr = std::chrono::duration_cast<std::chrono::duration<double>>(end_hr - start_hr);
	calculate_orientation_time_ = diff_hr.count() * 1000;
}

float GetRotationX()
{
	return panorama_tracker_.GetOrientationX();
}
float GetRotationY()
{
	return panorama_tracker_.GetOrientationY();
}
float GetRotationZ()
{
	return panorama_tracker_.GetRotation();
}

void ViewMap(int mapSize, bool view_keypoints, bool view_cells)
{
	MapSize ms;
	switch (mapSize)
	{
	case 0:
		ms = MAP_SIZE_FULL;
		break;
	case 1:
		ms = MAP_SIZE_HALF;
		break;
	case 2:
		ms = MAP_SIZE_QUARTER;
		break;
	default:
		ms = MAP_SIZE_FULL;
		break;
	}
	panorama_tracker_.ViewMap(ms, view_cells, view_keypoints, true);
}

const char* GetDebugString()
{
	std::string data = panorama_tracker_.GetDebugData();
	char arr[1024];
	strncpy(arr, data.c_str(), sizeof(arr));
	return arr;
}

int GetMapHeight()
{
	return panorama_tracker_.panorama_map.GetHeight();
}

int GetMapWidth()
{
	return panorama_tracker_.GetViewMapWidth();
}


uchar* TestImgSend(MonoArray* image, int image_height, int image_width)
{
	image_height_ = image_height;
	image_width_ = image_width;	
	Mat testisettii = getMatFromMonoArray(image);
	if (ret_image) free(ret_image);
	ret_image = new uchar[image_height * image_width];
	memcpy(ret_image, testisettii.data, image_height*image_width);
	return ret_image;
}

uchar* GetMapImage()
{
	delete map_image;
	Mat map_mat = panorama_tracker_.GetMapImage();
	Mat flipped; flip(map_mat, flipped, 1);
	map_image = new uchar[flipped.cols * flipped.rows * 3];
	memcpy(map_image, flipped.data, flipped.cols * flipped.rows * 3);
	return map_image;
}


uchar* ResizeImage(MonoArray* image, int height, int width, int new_height, int new_width)
{
	Mat img(height, width, CV_8UC1, (unsigned char*)image);
	Mat resized;
	resize(img, resized, Size(new_width, new_height));
	if (resized_image) free(resized_image);
	resized_image = new uchar[new_width*new_height];
	memcpy(resized_image, resized.data, new_width*new_height);
	return resized_image;
}

void Reset()
{
	PanoramaTracker pt = PanoramaTracker();
	panorama_tracker_ = pt;
}

void SetCustomOrientation(float x, float y, float z)
{
	panorama_tracker_.SetOrientation(x, y, z);
}

float GetTrackingQuality()
{
	return panorama_tracker_.GetQuality();
}

float CalcOrientationTime()
{
	return calculate_orientation_time_;
}

void Set(int setting, double value)
{
	SettingValue val = static_cast<SettingValue>(setting);
	panorama_tracker_.tracker_settings.Set(val, value);
}
