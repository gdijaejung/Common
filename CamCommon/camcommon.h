#pragma once


#ifndef _CRT_SECURE_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv/cvaux.h>
//#include "opencv2/nonfree/nonfree.hpp"

#include "../Common/common.h"
using namespace common;

#include "../Network/network.h"


using std::pair;


struct sSharedData
{
	int count;
	cv::Point2f pts[3];
};




#include "linecontour.h"
#include "camera.h"
#include "config.h"
#include "RecognitionConfig.h"
#include "recognitionEdgeconfig.h"
#include "detectpoint.h"
#include "detectpoint.h"
#include "rectcontour.h"
#include "squarecontour.h"
#include "roi.h"
#include "screen.h"
#include "sharedmemcommunication.h"
#include "wndmsgcommunication.h"
#include "udpcommunication.h"
#include "dxcapture.h"
#include "movie.h"
#include "pidcontrol.h"
#include "skewdetect.h"
#include "streamingsender.h"
#include "streamingreceiver.h"
#include "streamingviewer.h"
#include "searchpoint.h"
#include "thresholdfinder.h"
#include "LEDCalibrater.h"
#include "LEDBlinkCapture.h"
#include "videowriter.h"
#include "util.h"



#ifdef _DEBUG
	#pragma comment(lib, "opencv_core2411d.lib")
	#pragma comment(lib, "opencv_highgui2411d.lib")
	#pragma comment(lib, "opencv_imgproc2411d.lib")
	#pragma comment(lib, "opencv_features2d2411d.lib")
	//#pragma comment(lib, "opencv_nonfree2411d.lib")
	#pragma comment(lib, "winmm.lib")
#else
	#pragma comment(lib, "opencv_core2411.lib")
	#pragma comment(lib, "opencv_highgui2411.lib")
	#pragma comment(lib, "opencv_imgproc2411.lib")
	#pragma comment(lib, "opencv_features2d2411.lib")
	//#pragma comment(lib, "opencv_nonfree2411.lib")
	#pragma comment(lib, "winmm.lib")
#endif

