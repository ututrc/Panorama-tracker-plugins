#include "PanoramaTracker.h"

#define DLLEXPORT __declspec(dllexport)

typedef void* MonoArray;

int image_width_;
int image_height_;
float calculate_orientation_time_;

PanoramaTracker panorama_tracker_;

uchar* ret_image;
uchar* map_image;
uchar* resized_image;

int* arr_test;

Mat getMatFromMonoArray(MonoArray* frame);

extern "C"{
	//Methods for testing the functionality of OpenCV in the Unity3D app
	void DLLEXPORT TestOpencvEditor(MonoArray* image, int image_height, int image_width);
	DLLEXPORT uchar* TestImgSend(MonoArray* image, int image_height, int image_width);
	DLLEXPORT uchar* GetMapImage();
	DLLEXPORT uchar* ResizeImage(MonoArray* image, int height, int width, int new_height, int new_width);
	void DLLEXPORT InitializeTracker(MonoArray* image, int image_height, int image_width);
	//Actual tracking function, should be called with each frame
	void DLLEXPORT CalculateOrientation(MonoArray* image);
	//Tracker can be used by giving it custom orientations from gyro for example
	void DLLEXPORT SetCustomOrientation(float x, float y, float z);
	void DLLEXPORT Reset();
	void DLLEXPORT ViewMap(int mapSize, bool view_keypoints, bool view_cells);

	//For optimization debugging, return time per each calculate orientation
	float DLLEXPORT CalcOrientationTime();
	//Get a debug string from the tracker that contains statistical data
	DLLEXPORT const char* GetDebugString();
	void DLLEXPORT SetPyramidical(bool pyr);

	//Accessing PtSettings Set method to adjust tracker settings
	void DLLEXPORT Set(int setting, double value);

	int DLLEXPORT GetMapWidth();
	int DLLEXPORT GetMapHeight();

	float DLLEXPORT GetTrackingQuality();

	/*
	INFO ABOUT THE TRACKER STATUS
	*/
	float DLLEXPORT GetRotationX();
	float DLLEXPORT GetRotationY();
	float DLLEXPORT GetRotationZ();
}