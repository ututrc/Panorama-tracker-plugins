#ifndef PANORAMATRACKERANDROID_H_
#define PANORAMATRACKERANDROID_H_

#include "PanoramaTracker.h"
#include <opencv2/core/core.hpp>

typedef void* MonoArray;

int image_width_;
int image_height_;
bool mirrored_image_;

//MapManager map_manager_;
PanoramaTracker panorama_tracker_;
float calculate_orientation_time_;
uchar* map_image;

extern "C"{
	//Convert the pointer from Unity3D to a Mat
	Mat getMatFromMonoArray(MonoArray* frame);
	//Test plugin functionality
	int pluginTest();
	//Get the map images that can be viewed in Unity3D as byte arrays
	uchar* GetMapImage();
	uchar* GetMapImageFull();
	//Test OpenCV functionality
	void TestOpencvEditor(MonoArray* image, int image_height, int image_width);
	int TestOpencvAndroid(MonoArray* image, int image_height, int image_width);
	//Start the tracker
	void InitializeTracker(MonoArray* image, int image_height, int image_width, bool mirroredImage);
	//Estimate the orientation, call with each new frame
	void CalculateOrientation(MonoArray* image);
	//A custom rotation can be set to the tracker
	void SetCustomOrientation(float x, float y, float z);
	void Reset();
	void ViewMap();

	//Return the time elapsed for a single frame of orientation calculation
	float CalcOrientationTime();

	//Get information string from the tracker
	const char* GetDebugString();
	int GetMapWidth();
	int GetMapHeight();
	float GetTrackingQuality();
	void SetPyramidical(bool pyr);
	//Get info about the trackers current orientation
	float GetRotationX();
	float GetRotationY();
	float GetRotationZ();
	//Adjust tracker settings
	void Set(int setting, double value);
}



#endif /* PANORAMATRACKERANDROID_H_ */
