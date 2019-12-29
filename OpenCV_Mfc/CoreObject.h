#pragma once
#include "Singleton.h"

#include "opencv2/opencv.hpp"

#include "Timer.h"
using namespace cv;

class CCoreObject :public CSingleton<CCoreObject>
{
public:
	CCoreObject();
	virtual ~CCoreObject();
private:
	unsigned int BitFlag = 0;
	const unsigned int USEIMAGE = 1 << 0;
	const unsigned int USEVIDEO = 1 << 1;
	const unsigned int USEWEBCAM = 1 << 2;
	const unsigned int USEKINECT = 1 << 4;
public:
	unsigned int GetDataStreamType();
	
public://videofunctions
	void LoadVideo(const char* FilePath , const CWnd* _targetDC);
	void DisplayVideo(const CWnd* _targetDC);
	void DisplayVideoR(const CWnd* _targetDC);
	void DisplayVideoG(const CWnd* _targetDC);
	void DisplayVideoB(const CWnd* _targetDC);
	void DisplayHistogramVideo(const CWnd* _targetDC);
	void DisplayHistogramVideoR(const CWnd* _targetDC);
	void DisplayHistogramVideoG(const CWnd* _targetDC);
	void DisplayHistogramVideoB(const CWnd* _targetDC);
	bool VideoLoaded();
	///non unse mfc picture control
	
	void UseCamVideo();
	void UseKinnectVideo();
	void LoadVideo(const char* FilePath);
	void DisplayVideo();
	void DisplayVideoR();
	void DisplayVideoG();
	void DisplayVideoB();
	void DisplayHistogramVideo();
	void DisplayHistogramVideoR();
	void DisplayHistogramVideoG();
	void DisplayHistogramVideoB();
	void DisplayGreyVideoR();
	void DisplayGreyVideoG();
	void DisplayGreyVideoB();

public://imagefunctions
	void LoadImage(const char* FilePath , const CWnd* _targetDC);
	void DisplayImageR(const CWnd* _targetDC);
	void DisplayImageG(const CWnd* _targetDC);
	void DisplayImageB(const CWnd* _targetDC);
	void DisplayHistogramImage(const CWnd* _targetDC);
	void DisplayHistogramImageR(const CWnd* _targetDC);
	void DisplayHistogramImageG(const CWnd* _targetDC);
	void DisplayHistogramImageB(const CWnd* _targetDC);
	///non use mfc picture control
	void LoadImage(const char* FilePath);
	void DisplayImage();
	void DisplayImageR();
	void DisplayImageG();
	void DisplayImageB();
	void DisplayHistogramImage();
	void DisplayHistogramImageR();
	void DisplayHistogramImageG();
	void DisplayHistogramImageB();
	
	void DisplayGreyImageR();
	void DisplayGreyImageG();
	void DisplayGreyImageB();
public://histogram
	void CalcHistogram();
	
public://timerfunctions
	void TimerTick();
	bool PermitCall();
private:
	void ShowImage(const CWnd* _targetDC, Mat _targetMat,CRect _targetRect);
	void ShowImage(const String& _winname, Mat _targetMat,CRect _winsize);
	void CullImage(const CWnd* _targetDC, LPCRECT cullSurface, LPCRECT fullSurface);
	void RGBFiltering(Mat _tagetImg);
	void ResetPanel(const CWnd* _targetDC);

public://imageProcessing algorithms
	void MeanShift();
private:
	bool isinit = false;
	Rect m_MeanShiftWindow;
	void InitMeanShiftWindow();
private:
	Mat m_matImage;
	Mat m_matGray;
	Mat m_matR;
	Mat m_matG;
	Mat m_matB;
	Mat m_matHistogram;
	Mat m_matHistogramR;
	Mat m_matHistogramG;
	Mat m_matHistogramB;
	Mat m_matGreyR;
	Mat m_matGreyG;
	Mat m_matGreyB;
	Mat m_matMeanShift;
	/*Mat m_histimg;
	Mat m_histimgR;
	Mat m_histimgG;
	Mat m_histimgB;*/
	//BITMAPINFO* _bitminfo;
	VideoCapture m_VideoCapture;
	//void CreateBitmapInfo(int w, int h, int bpp);
	bool runningFlag = false;

	BITMAPINFO* CreateBitmapInfo(int w, int h, int bpp);
	void AdjustImageRatio(CRect& rc);
private://histogram elements
	int histSize[1];
	float hrange[2];

private://timer elements
	shared_ptr<CTimer> m_Timer;
	float m_fTimeAcc;
	float m_CallPerSec;
	int frameCnt;
	int frameCntLimit;
	float timeElapsed;
	void SetFrameLimit(const float& _Limit);
};

