#include <jni.h>
#include "PanoramaTrackerAndroid.h"
#include <opencv2/core/core.hpp>


Mat getMatFromMonoArray(MonoArray* frame){
	Mat img(image_height_, image_width_, CV_8UC3, (unsigned char*)frame);
	Mat rotated;
	if(!mirrored_image_) return img;
	Mat corrected;
	flip(img, corrected, 1);
	return corrected;
}

extern "C"{
int pluginTest(){
	return 123;
}

bool TestCamera(){
	VideoCapture cap;
	int id = 0;
	while(id < 2222){
		cap.open(id);
		if(cap.isOpened()) return true;
		id++;
	}
	return false;
}

int TestOpencvAndroid(MonoArray* image, int image_height, int image_width){
	image_height_ = image_height;
	image_width_ = image_width;
	Mat img = getMatFromMonoArray(image);
	Point asd(5, 5);
	int redVal = img.at<Vec3b>(5, 5)[2];
	return redVal;
}

void InitializeTracker(MonoArray* image, int image_height, int image_width, bool mirroredImage)
{
	mirrored_image_ = mirroredImage;
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

uchar* GetMapImage()
{
	delete map_image;
	Mat map_mat = panorama_tracker_.GetMapImage();
	Mat flipped; flip(map_mat, flipped, 1);
	map_image = new uchar[flipped.cols * flipped.rows * 3];
	memcpy(map_image, flipped.data, flipped.cols * flipped.rows * 3);
	return map_image;
}

uchar* GetMapImageCustomSize(){
	delete map_image;
	Mat map_mat = panorama_tracker_.GetMapImageFull();
	Mat flipped; flip(map_mat, flipped, 1);
	map_image = new uchar[flipped.cols*flipped.rows*3];
	memcpy(map_image, flipped.data, flipped.cols * flipped.rows * 3);
	return map_image;
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

void Set(int setting, double value){
	SettingValue val = static_cast<SettingValue>(setting);
	panorama_tracker_.tracker_settings.Set(val, value);
}
}
