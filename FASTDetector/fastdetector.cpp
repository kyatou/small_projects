//
// FAST detector test
//


#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <string.h>
#include <time.h>

using namespace cv;
using namespace std;

//Detect fast descriptor and draw keypoints
void FASTDetect(Mat colorImage)
{
	vector<cv::KeyPoint> keypoints;
	FastFeatureDetector fast(40);
	Mat gsimage;
	cvtColor(colorImage, gsimage, CV_BGR2GRAY);
	keypoints.clear();
	fast.detect(gsimage, keypoints);
	drawKeypoints(colorImage, keypoints, colorImage, cv::Scalar(255, 255, 255),
		DrawMatchesFlags::DRAW_OVER_OUTIMG);
}


int main(int argc, char** argv)
{
	int cameraId = 0;
	int i = 0;
	Mat view;
	VideoCapture capture;
	capture.open(cameraId);
	uchar key;
	if (!capture.isOpened())
		return fprintf(stderr, "Could not initialize video (%d) capture\n",
				cameraId), -2;

	//Set up font
	int fontFace = FONT_HERSHEY_SIMPLEX;
	double fontScale = 1;
	int thickness = 1;
	int baseline = 0;
	Point textOrg(30, 50);

	//process time
	double start=0,finish=0;
	double procTime=0;
	double freq=getTickFrequency();

	namedWindow("FAST", 1);

	String text="";
	

	for (i = 0;; i++) 
	{

		if (capture.isOpened())
 		{
			Mat view0;
			capture >> view0;
			view0.copyTo(view);
		}
		start = static_cast<double> (getTickCount());
		FASTDetect(view);
		finish = static_cast<double> (getTickCount());
		procTime= (finish - start) /freq;

		
		char chr[256];
		sprintf(chr,"%f ms",procTime*1000);
		text = string(chr);
		putText(view, text, textOrg, fontFace, fontScale, Scalar::all(255),
				thickness, 8);

		imshow("FAST", view);

		key = waitKey(30);
		if ((key & 255) == 27)
			break;
	}

	return 0;
}


