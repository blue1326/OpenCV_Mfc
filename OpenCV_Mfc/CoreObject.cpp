#include "stdafx.h"
#include "CoreObject.h"


CCoreObject::CCoreObject()
	:m_fTimeAcc(0.f)
	, frameCnt(0)
	, frameCntLimit(0)
	, timeElapsed(0)
	,m_CallPerSec(60)
{
	m_Timer = CTimer::CreateTimer();
	m_Timer->Start();
}


CCoreObject::~CCoreObject()
{
	m_matImage.release();
	m_matGray.release();
	m_matR.release();
	m_matG.release();
	m_matB.release();
	m_matHistogram.release();
	m_matHistogramR.release();
	m_matHistogramG.release();
	m_matHistogramB.release();
}


unsigned int CCoreObject::GetDataStreamType()
{
	return BitFlag;
}

void CCoreObject::LoadVideo(const char* FilePath, const CWnd* _targetDC)
{
	//VideoCapture vc(FilePath);
	
	
	m_VideoCapture.open(FilePath);
	if (!m_VideoCapture.isOpened())
	{
		
	}

	//static_cast<CStatic*>(const_cast<CWnd*>(_targetDC));
	


	//m_VideoCapture.set(CAP_PROP_FRAME_WIDTH, 800);
	//m_VideoCapture.set(CAP_PROP_FRAME_HEIGHT, 600);
	
	SetFrameLimit((const float)m_VideoCapture.get(CAP_PROP_FPS));
}




void CCoreObject::DisplayVideo(const CWnd* _targetDC)
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}
	
	if (!m_VideoCapture.read(m_matImage))
	{
		m_VideoCapture.release();
		ResetPanel(_targetDC);
		runningFlag = false;
		return;
	}
	runningFlag = true;
	
	///trans
	CRect rc,rc2;
	_targetDC->GetClientRect(&rc);
	_targetDC->GetClientRect(&rc2); //cull unsused surface
	//calculate video size ratio
	AdjustImageRatio(rc);

	cvtColor(m_matImage, m_matGray, COLOR_BGR2GRAY);
	RGBFiltering(m_matImage);
	CalcHistogram();
	

	Mat mattemp = m_matImage;
	/*int padding = 0;
	if (bpp < 32)
		padding = 4 - (m_matImage.cols % 4);
	if (padding == 4)
		padding = 0;
	int border = 0;
	if (bpp > 32)
		border = 4 - (m_matImage.cols % 4);

	Mat mattemp;
	if (border > 0 || m_matImage.isContinuous() == false)
		copyMakeBorder(m_matImage, mattemp, 0, 0, 0, border, BORDER_CONSTANT, 0);
	else*/
	

	
	CClientDC dc(const_cast<CWnd*>(_targetDC));
	
	
	ShowImage(_targetDC, mattemp, rc);
	CullImage(_targetDC, &rc, &rc2);

	mattemp.release();


}


void CCoreObject::DisplayVideoR(const CWnd* _targetDC)
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}

	if (!runningFlag)
	{
		ResetPanel(_targetDC);
		return;
	}

	///trans
	CRect rc, rc2;
	_targetDC->GetClientRect(&rc);
	_targetDC->GetClientRect(&rc2); 
	//calculate video size ratio
	AdjustImageRatio(rc);

	Mat mattemp = m_matR;

	//CClientDC dc(const_cast<CWnd*>(_targetDC));


	ShowImage(_targetDC, mattemp, rc);
	CullImage(_targetDC, &rc, &rc2);
	mattemp.release();
}


void CCoreObject::DisplayVideoG(const CWnd* _targetDC)
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}

	if (!runningFlag)
	{
		ResetPanel(_targetDC);
		return;
	}

	///trans
	CRect rc, rc2;
	_targetDC->GetClientRect(&rc);
	_targetDC->GetClientRect(&rc2);
	//calculate video size ratio
	AdjustImageRatio(rc);

	Mat mattemp = m_matG;

	//CClientDC dc(const_cast<CWnd*>(_targetDC));


	ShowImage(_targetDC, mattemp, rc);
	CullImage(_targetDC, &rc, &rc2);
	mattemp.release();
}

void CCoreObject::DisplayVideoB(const CWnd* _targetDC)
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}

	if (!runningFlag)
	{
		ResetPanel(_targetDC);
		return;
	}

	///trans
	CRect rc, rc2;
	_targetDC->GetClientRect(&rc);
	_targetDC->GetClientRect(&rc2);
	//calculate video size ratio
	AdjustImageRatio(rc);

	Mat mattemp = m_matB;

	//CClientDC dc(const_cast<CWnd*>(_targetDC));


	ShowImage(_targetDC, mattemp, rc);
	CullImage(_targetDC, &rc, &rc2);
	mattemp.release();
}

bool CCoreObject::VideoLoaded()
{
	return m_VideoCapture.isOpened();
}



void CCoreObject::UseCamVideo()
{
	if (m_VideoCapture.isOpened())
	{
		m_VideoCapture.release();
		runningFlag = false;
	}
	destroyAllWindows();
	m_VideoCapture.get(0);
	if (!m_VideoCapture.isOpened())
	{
		return;
	}
	BitFlag &= ~USEVIDEO;
	BitFlag &= ~USEIMAGE;
	BitFlag |= USEWEBCAM;
	m_VideoCapture.set(CAP_PROP_FRAME_WIDTH, 800);
	m_VideoCapture.set(CAP_PROP_FRAME_HEIGHT, 600);
	/*CRect rc;
	rc.right = 400;
	rc.bottom = 300;

	AdjustImageRatio(rc);*/

	cvtColor(m_matImage, m_matGray, COLOR_BGR2GRAY);
	RGBFiltering(m_matImage);
	CalcHistogram();
}


void CCoreObject::UseKinnectVideo()
{
	if (m_VideoCapture.isOpened())
	{
		m_VideoCapture.release();
		runningFlag = false;
	}
	destroyAllWindows();
	m_VideoCapture.get(CAP_OPENNI2);
	if (!m_VideoCapture.isOpened())
	{
		m_VideoCapture.get(CAP_OPENNI);
		if (!m_VideoCapture.isOpened())
		{
			return;
		}
		
	}
	BitFlag &= ~USEVIDEO;
	BitFlag &= ~USEIMAGE;
	BitFlag &= ~USEWEBCAM;
	BitFlag |= USEKINECT;
	m_VideoCapture.set(CAP_PROP_FRAME_WIDTH, 800);
	m_VideoCapture.set(CAP_PROP_FRAME_HEIGHT, 600);
	/*CRect rc;
	rc.right = 400;
	rc.bottom = 300;

	AdjustImageRatio(rc);*/

	cvtColor(m_matImage, m_matGray, COLOR_BGR2GRAY);
	RGBFiltering(m_matImage);
	CalcHistogram();
}

void CCoreObject::LoadImage(const char* FilePath, const CWnd* _targetDC)
{
	ResetPanel(_targetDC);
	m_matImage = imread(cv::String(FilePath));

	CRect rc, rc2;
	_targetDC->GetClientRect(&rc);
	_targetDC->GetClientRect(&rc2); //cull unsused surface
	//calculate video size ratio
	AdjustImageRatio(rc);

	//resize(m_matImage, m_matImage, Size(rc.right, rc.bottom));
	cvtColor(m_matImage, m_matGray, COLOR_BGR2GRAY);
	RGBFiltering(m_matImage);
	CalcHistogram();


	Mat mattemp = m_matImage;

	
	ShowImage(_targetDC, mattemp, rc);
	CullImage(_targetDC, &rc2, &rc);
	mattemp.release();
}



void CCoreObject::DisplayImageR(const CWnd* _targetDC)
{
	ResetPanel(_targetDC);
	CRect rc, rc2;
	_targetDC->GetClientRect(&rc);
	_targetDC->GetClientRect(&rc2); //cull unsused surface
	//calculate video size ratio
	AdjustImageRatio(rc);
	Mat mattemp = m_matR;

	ShowImage(_targetDC, mattemp, rc);
	CullImage(_targetDC, &rc2, &rc);
	mattemp.release();
}


void CCoreObject::DisplayImageG(const CWnd* _targetDC)
{
	ResetPanel(_targetDC);
	CRect rc, rc2;
	_targetDC->GetClientRect(&rc);
	_targetDC->GetClientRect(&rc2); //cull unsused surface
	//calculate video size ratio
	AdjustImageRatio(rc);
	Mat mattemp = m_matG;

	ShowImage(_targetDC, mattemp, rc);
	CullImage(_targetDC, &rc2, &rc);
	mattemp.release();
}


void CCoreObject::DisplayImageB(const CWnd* _targetDC)
{
	ResetPanel(_targetDC);
	CRect rc, rc2;
	_targetDC->GetClientRect(&rc);
	_targetDC->GetClientRect(&rc2); //cull unsused surface
	//calculate video size ratio
	AdjustImageRatio(rc);
	Mat mattemp = m_matB;

	ShowImage(_targetDC, mattemp, rc);
	CullImage(_targetDC, &rc2, &rc);
	mattemp.release();
}


void CCoreObject::DisplayHistogramImage(const CWnd* _targetDC)
{
	ResetPanel(_targetDC);
	CRect rc, rc2;
	_targetDC->GetClientRect(&rc);
	_targetDC->GetClientRect(&rc2); //cull unsused surface
	//calculate video size ratio
	AdjustImageRatio(rc);
	Mat mattemp = m_matHistogram;

	ShowImage(_targetDC, mattemp, rc);
	CullImage(_targetDC, &rc2, &rc);
	mattemp.release();
}


void CCoreObject::DisplayHistogramImageR(const CWnd* _targetDC)
{
	ResetPanel(_targetDC);
	CRect rc, rc2;
	_targetDC->GetClientRect(&rc);
	_targetDC->GetClientRect(&rc2); //cull unsused surface
	//calculate video size ratio
	AdjustImageRatio(rc);
	Mat mattemp = m_matHistogramR;

	ShowImage(_targetDC, mattemp, rc);
	CullImage(_targetDC, &rc2, &rc);
	mattemp.release();
}


void CCoreObject::DisplayHistogramImageG(const CWnd* _targetDC)
{
	ResetPanel(_targetDC);
	CRect rc, rc2;
	_targetDC->GetClientRect(&rc);
	_targetDC->GetClientRect(&rc2); //cull unsused surface
	//calculate video size ratio
	AdjustImageRatio(rc);
	Mat mattemp = m_matHistogramG;

	ShowImage(_targetDC, mattemp, rc);
	CullImage(_targetDC, &rc2, &rc);
	mattemp.release();
}


void CCoreObject::DisplayHistogramImageB(const CWnd* _targetDC)
{
	ResetPanel(_targetDC);
	CRect rc, rc2;
	_targetDC->GetClientRect(&rc);
	_targetDC->GetClientRect(&rc2); //cull unsused surface
	//calculate video size ratio
	AdjustImageRatio(rc);
	Mat mattemp = m_matHistogramB;

	ShowImage(_targetDC, mattemp, rc);
	CullImage(_targetDC, &rc2, &rc);
	mattemp.release();
}


void CCoreObject::CalcHistogram()
{
	const int ch_no[] = { 0 };
	const int ch_noR[] = { 2 };
	const int ch_noG[] = { 1 };
	const int ch_noB[] = { 0 };
	float ch_range[] = { 0.0,255.0 };
	const float* ch_Ranges = ch_range;
	int num_bins = 255;
	calcHist(&m_matGray, 1, ch_no, Mat(), m_matHistogram, 1, &num_bins, &ch_Ranges);
	calcHist(&m_matR, 1, ch_noR, Mat(), m_matHistogramR, 1, &num_bins, &ch_Ranges);
	calcHist(&m_matG, 1, ch_noG, Mat(), m_matHistogramG, 1, &num_bins, &ch_Ranges);
	calcHist(&m_matB, 1, ch_noB, Mat(), m_matHistogramB, 1, &num_bins, &ch_Ranges);
	
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / num_bins);
	Mat histimg(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	Mat histimgR(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	Mat histimgG(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	Mat histimgB(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	normalize(m_matHistogram, m_matHistogram, 0, histimg.rows, NORM_MINMAX, -1, Mat());
	normalize(m_matHistogramR, m_matHistogramR, 0, histimgR.rows, NORM_MINMAX, -1, Mat());
	normalize(m_matHistogramG, m_matHistogramG, 0, histimgG.rows, NORM_MINMAX, -1, Mat());
	normalize(m_matHistogramB, m_matHistogramB, 0, histimgB.rows, NORM_MINMAX, -1, Mat());
	for (int i = 1; i < num_bins; i++)
	{
		line(histimg,
			Point(bin_w*(i - 1), hist_h - cvRound(m_matHistogram.at<float>(i - 1)))
			, Point(bin_w*(i), hist_h - cvRound(m_matHistogram.at<float>(i)))
			, Scalar(255, 255, 255), 2, 8, 0);
		line(histimgR,
			Point(bin_w*(i - 1), hist_h - cvRound(m_matHistogramR.at<float>(i - 1)))
			, Point(bin_w*(i), hist_h - cvRound(m_matHistogramR.at<float>(i)))
			, Scalar(0, 0, 255), 2, 8, 0);
		line(histimgG,
			Point(bin_w*(i - 1), hist_h - cvRound(m_matHistogramG.at<float>(i - 1)))
			, Point(bin_w*(i), hist_h - cvRound(m_matHistogramG.at<float>(i)))
			, Scalar(0, 255, 0), 2, 8, 0);
		line(histimgB,
			Point(bin_w*(i - 1), hist_h - cvRound(m_matHistogramB.at<float>(i - 1)))
			, Point(bin_w*(i), hist_h - cvRound(m_matHistogramB.at<float>(i)))
			, Scalar(255, 0, 0), 2, 8, 0);
	}
	
	m_matHistogram = histimg;
	m_matHistogramR = histimgR;
	m_matHistogramG = histimgG;
	m_matHistogramB = histimgB;

	histimg.release();
	histimgR.release();
	histimgG.release();
	histimgB.release();
	
	
}

void CCoreObject::DisplayHistogramVideo(const CWnd* _targetDC)
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}

	if (!runningFlag)
	{
		ResetPanel(_targetDC);
		return;
	}
	///trans
	CRect rc, rc2;
	_targetDC->GetClientRect(&rc);
	_targetDC->GetClientRect(&rc2);
	//calculate video size ratio
	AdjustImageRatio(rc);

	Mat mattemp = m_matHistogram;

	CClientDC dc(const_cast<CWnd*>(_targetDC));


	ShowImage(_targetDC, mattemp, rc);
	CullImage(_targetDC, &rc, &rc2);
	mattemp.release();
}


void CCoreObject::DisplayHistogramVideoR(const CWnd* _targetDC)
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}

	if (!runningFlag)
	{
		ResetPanel(_targetDC);
		return;
	}
	///trans
	CRect rc, rc2;
	_targetDC->GetClientRect(&rc);
	_targetDC->GetClientRect(&rc2);
	//calculate video size ratio
	AdjustImageRatio(rc);

	Mat mattemp = m_matHistogramR;

	CClientDC dc(const_cast<CWnd*>(_targetDC));


	ShowImage(_targetDC, mattemp, rc);
	CullImage(_targetDC, &rc, &rc2);
	mattemp.release();
}


void CCoreObject::DisplayHistogramVideoG(const CWnd* _targetDC)
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}

	if (!runningFlag)
	{
		ResetPanel(_targetDC);
		return;
	}
	///trans
	CRect rc, rc2;
	_targetDC->GetClientRect(&rc);
	_targetDC->GetClientRect(&rc2);
	//calculate video size ratio
	AdjustImageRatio(rc);

	Mat mattemp = m_matHistogramG;

	CClientDC dc(const_cast<CWnd*>(_targetDC));


	ShowImage(_targetDC, mattemp, rc);
	CullImage(_targetDC, &rc, &rc2);
	mattemp.release();
}

void CCoreObject::DisplayHistogramVideoB(const CWnd* _targetDC)
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}

	if (!runningFlag)
	{
		ResetPanel(_targetDC);
		return;
	}
	///trans
	CRect rc, rc2;
	_targetDC->GetClientRect(&rc);
	_targetDC->GetClientRect(&rc2);
	//calculate video size ratio
	AdjustImageRatio(rc);

	Mat mattemp = m_matHistogramB;

	CClientDC dc(const_cast<CWnd*>(_targetDC));

	
	ShowImage(_targetDC, mattemp, rc);
	CullImage(_targetDC, &rc, &rc2);
	mattemp.release();
}

void CCoreObject::TimerTick()
{
	m_Timer->Tick();
}

bool CCoreObject::PermitCall()
{
	bool isLimit = false;

	frameCnt++;
	m_fTimeAcc += m_Timer->DeltaTime();
	if (m_fTimeAcc >= m_CallPerSec)
	{
		frameCntLimit++;
		m_fTimeAcc = 0.f;
		isLimit = true;
	}

/*
	if ((m_Timer->TotalTime() - timeElapsed) >= 1.0f)
	{
		int fps = frameCnt;
		int limitedfps = frameCntLimit;
		float mspf = 1000.0f / fps;

		frameCnt = 0;
		frameCntLimit = 0;
		timeElapsed += 1.0f;
	}*/

	return isLimit;
}

void CCoreObject::ShowImage(const CWnd* _targetDC, Mat _targetMat,CRect _targetRect)
{
	CClientDC dc(const_cast<CWnd*>(_targetDC));
	
	int bpp = 8 * (int)_targetMat.elemSize();
	assert((bpp == 8 || bpp == 24 || bpp == 32));

	//resize(_targetMat, _targetMat, Size(_targetRect.right, _targetRect.bottom));
	BITMAPINFO* bminfo = CreateBitmapInfo(_targetMat.cols, _targetMat.rows, bpp);
	SetStretchBltMode(dc.GetSafeHdc(), COLORONCOLOR);
	
	if (_targetMat.cols == _targetRect.Width() && _targetMat.rows == _targetRect.Height())
	{
		SetDIBitsToDevice(dc.GetSafeHdc(), _targetRect.left, _targetRect.top, _targetRect.Width(), _targetRect.Height(), 0, 0, 0, _targetMat.rows, _targetMat.data, bminfo, DIB_RGB_COLORS);
	}
	else
	{
		int imgWidth = _targetMat.cols;
		int imgHeight = _targetMat.rows;
		StretchDIBits(dc.GetSafeHdc(), _targetRect.left, _targetRect.top, _targetRect.Width(), _targetRect.Height(), 0, 0, imgWidth, imgHeight, _targetMat.data, bminfo, DIB_RGB_COLORS, SRCCOPY);

	}
	delete[]bminfo;
	bminfo = NULL;
}

void CCoreObject::ShowImage(const String& _winname, Mat _targetMat, CRect _winsize)
{
	float x = _winsize.Width();
	float y = _winsize.Height();
	resize(_targetMat, _targetMat, Size(_winsize.Width(), _winsize.Height()));
	namedWindow(_winname,WINDOW_AUTOSIZE);
	imshow(_winname, _targetMat);
}

void CCoreObject::CullImage(const CWnd* _targetDC, LPCRECT cullSurface, LPCRECT fullSurface)
{
	CClientDC dc(const_cast<CWnd*>(_targetDC));
	dc.ExcludeClipRect(cullSurface); // 이미지 출력된 부분을 제외한

	dc.FillSolidRect(fullSurface, GetSysColor(COLOR_BTNFACE)); // 전체
}

void CCoreObject::RGBFiltering(Mat _tagetImg)
{
	vector<Mat> vecRGBMats;
	split(_tagetImg, vecRGBMats);

	m_matGreyR = vecRGBMats[2];
	m_matGreyG = vecRGBMats[1];
	m_matGreyB = vecRGBMats[0];



	Mat fillZero(Mat::zeros(m_matImage.size(),CV_8UC1));
	Mat R[] = { fillZero , fillZero , vecRGBMats[2] };
	Mat G[] = { fillZero , vecRGBMats[1] , fillZero };
	Mat B[] = { vecRGBMats[0] , fillZero , fillZero };

	

	merge(R, 3, m_matR);
	merge(G, 3, m_matG);
	merge(B, 3, m_matB);

}

void CCoreObject::ResetPanel(const CWnd* _targetDC)
{
	CClientDC dc(const_cast<CWnd*>(_targetDC));
	CRect rc;
	_targetDC->GetClientRect(&rc);
	dc.FillSolidRect(&rc, GetSysColor(COLOR_BTNFACE));
}

BITMAPINFO* CCoreObject::CreateBitmapInfo(int w, int h, int bpp)
{
	BITMAPINFO* bitmapinfo = NULL;

	if (bpp == 8)
		bitmapinfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
	else // 24 or 32bit
		bitmapinfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO)];

	bitmapinfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapinfo->bmiHeader.biPlanes = 1;
	bitmapinfo->bmiHeader.biBitCount = bpp;
	bitmapinfo->bmiHeader.biCompression = BI_RGB;
	bitmapinfo->bmiHeader.biSizeImage = 0;
	bitmapinfo->bmiHeader.biXPelsPerMeter = 0;
	bitmapinfo->bmiHeader.biYPelsPerMeter = 0;
	bitmapinfo->bmiHeader.biClrUsed = 0;
	bitmapinfo->bmiHeader.biClrImportant = 0;
	if (bpp == 8)
	{
		for (int i = 0; i < 256; i++)
		{
			bitmapinfo->bmiColors[i].rgbBlue = (BYTE)i;
			bitmapinfo->bmiColors[i].rgbGreen = (BYTE)i;
			bitmapinfo->bmiColors[i].rgbRed = (BYTE)i;
			bitmapinfo->bmiColors[i].rgbReserved = 0;
		}
	}

	bitmapinfo->bmiHeader.biWidth = w;
	bitmapinfo->bmiHeader.biHeight = -h;
	return bitmapinfo;
}

void CCoreObject::AdjustImageRatio(CRect& rc)
{
	float fImageRatio = float(m_matImage.cols) / float(m_matImage.rows); //
	float fRectRatio = float(rc.right) / float(rc.bottom);
	float fScaleFactorX,fScaleFactorY;
	if (fImageRatio < fRectRatio)
	{
		fScaleFactorX = float(rc.bottom) / float(m_matImage.rows);
		int rightWithRatio =m_matImage.cols * fScaleFactorX;
		float halfOfDifX = ((float)rc.right - (float)rightWithRatio) / (float)2;
		rc.left = (LONG)halfOfDifX;
		rc.right = (LONG)rightWithRatio+halfOfDifX;
	}
	else {
		fScaleFactorY = float(rc.right) / float(m_matImage.cols);
		//fScaleFactorX = float(rc.bottom) / float(m_matImage.rows);
		int bottomWithRatio = m_matImage.rows * fScaleFactorY;
		//int rightWithRatio = m_matImage.cols * fScaleFactorX;
		float halfOfDifY = ((float)rc.bottom - (float)bottomWithRatio) / (float)2;
		//float halfOfDifX = ((float)rc.right - (float)rightWithRatio) / (float)2;
		rc.top = (LONG)halfOfDifY;
		rc.bottom = (LONG)bottomWithRatio;
		
		//rc.right = (LONG)rightWithRatio+halfOfDifX;
	}
}

void CCoreObject::SetFrameLimit(const float& _Limit)
{
	m_CallPerSec = 1.f / _Limit;
}



void CCoreObject::LoadVideo(const char* FilePath)
{
	destroyAllWindows();
	m_VideoCapture.open(FilePath);
	if (!m_VideoCapture.isOpened())
	{

	}
	BitFlag |= USEVIDEO;
	BitFlag &= ~USEIMAGE;
	BitFlag &= ~USEWEBCAM;
	SetFrameLimit((const float)m_VideoCapture.get(CAP_PROP_FPS));
}
void CCoreObject::DisplayVideo()
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}
	if (!m_VideoCapture.read(m_matImage))
	{
		m_VideoCapture.release();
		runningFlag = false;
		return;
	}
	runningFlag = true;

	//setBasicwindowsize
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;
	//adjust video size ratio based on basicsize
	AdjustImageRatio(rc);

	cvtColor(m_matImage, m_matGray, COLOR_BGR2GRAY);
	RGBFiltering(m_matImage);
	CalcHistogram();


	Mat mattemp = m_matImage;

	ShowImage(String("Main Video"), mattemp, rc);

	mattemp.release();

}

void CCoreObject::MeanShift()
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}

	if (!runningFlag)
	{
		return;
	}

	Mat  roi, hsv_roi, mask;
	
	Mat mattemp = m_matImage;
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;
	//Rect track_window(0, 0, rc.right, rc.bottom);
	Rect track_window(mattemp.cols/2, mattemp.rows/2, 100, 50);
	roi = mattemp(track_window);
	cvtColor(roi, hsv_roi, COLOR_BGR2HSV);
	inRange(hsv_roi, Scalar(0, 60, 32), Scalar(180, 255, 255), mask);
	float range_[] = { 0,180 };
	const float* range[] = { range_ };
	Mat roi_hist;
	int histsize[] = { 180 };
	int channels[] = { 0 };
	calcHist(&hsv_roi, 1, channels, mask, roi_hist, 1, histsize, range);
	normalize(roi_hist, roi_hist, 0, 255, NORM_MINMAX);
	//iterations
	TermCriteria term_crit(TermCriteria::EPS | TermCriteria::COUNT, 10, 1);
	Mat hsv, dst;

	//Mat mattemp = m_matMeanShift;
	
	/*if (frame.empty())
		break;*/

	cvtColor(mattemp, hsv, COLOR_BGR2HSV);
	calcBackProject(&hsv, 1, channels, roi_hist, dst, range);

	// apply meanshift to get the new location
	meanShift(dst, track_window, term_crit);

	
	// Draw it on image
	rectangle(mattemp, track_window, 255, 2);
	//imshow("img2", frame);
	AdjustImageRatio(rc);
	ShowImage(String("MeanShift"), mattemp, rc);
	mattemp.release();
	
	
}
void CCoreObject::DisplayVideoR()
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}

	if (!runningFlag)
	{
		return;
	}
	//setBasicwindowsize
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;
	//adjust video size ratio based on basicsize
	AdjustImageRatio(rc);

	Mat mattemp = m_matR;

	ShowImage(String("R Video"), mattemp, rc);
	mattemp.release();
}
void CCoreObject::DisplayVideoG()
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}

	if (!runningFlag)
	{
		return;
	}
	//setBasicwindowsize
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;
	//adjust video size ratio based on basicsize
	AdjustImageRatio(rc);

	Mat mattemp = m_matG;

	ShowImage(String("G Video"), mattemp, rc);
	mattemp.release();
}

void CCoreObject::DisplayVideoB()
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}

	if (!runningFlag)
	{
		return;
	}
	//setBasicwindowsize
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;
	//adjust video size ratio based on basicsize
	AdjustImageRatio(rc);

	Mat mattemp = m_matB;

	ShowImage(String("B Video"), mattemp, rc);
	mattemp.release();
}

void CCoreObject::LoadImage(const char* FilePath)
{
	if (m_VideoCapture.isOpened())
	{
		m_VideoCapture.release();
		runningFlag = false;
	}
	destroyAllWindows();
	m_matImage = imread(cv::String(FilePath));
	BitFlag &= ~USEVIDEO;
	BitFlag |= USEIMAGE;
	BitFlag &= ~USEWEBCAM;
	/*CRect rc;
	rc.right = 400;
	rc.bottom = 300;
	
	AdjustImageRatio(rc);*/

	cvtColor(m_matImage, m_matGray, COLOR_BGR2GRAY);
	RGBFiltering(m_matImage);
	CalcHistogram();


	/*Mat mattemp = m_matImage;


	ShowImage(String("Main IMG"), mattemp, rc);
	mattemp.release();*/
}


void CCoreObject::DisplayImage()
{
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;

	AdjustImageRatio(rc);
	Mat mattemp = m_matImage;

	ShowImage(String("Main IMG"), mattemp, rc);
	mattemp.release();
}

void CCoreObject::DisplayImageR()
{
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;
	
	AdjustImageRatio(rc);
	Mat mattemp = m_matR;

	ShowImage(String("R IMG"), mattemp, rc);
	mattemp.release();
}
void CCoreObject::DisplayImageG()
{
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;

	AdjustImageRatio(rc);
	Mat mattemp = m_matG;

	ShowImage(String("G IMG"), mattemp, rc);
	mattemp.release();
}
void CCoreObject::DisplayImageB()
{
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;

	AdjustImageRatio(rc);
	Mat mattemp = m_matB;

	ShowImage(String("B IMG"), mattemp, rc);
	mattemp.release();
}
void CCoreObject::DisplayHistogramImage()
{
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;

	AdjustImageRatio(rc);
	Mat mattemp = m_matHistogram;

	ShowImage(String("Hist IMG"), mattemp, rc);
	mattemp.release();
}
void CCoreObject::DisplayHistogramImageR()
{
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;

	AdjustImageRatio(rc);
	Mat mattemp = m_matHistogramR;

	ShowImage(String("HistR IMG"), mattemp, rc);
	mattemp.release();
}
void CCoreObject::DisplayHistogramImageG()
{
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;

	AdjustImageRatio(rc);
	Mat mattemp = m_matHistogramG;

	ShowImage(String("HistG IMG"), mattemp, rc);
	mattemp.release();
}
void CCoreObject::DisplayHistogramImageB()
{
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;

	AdjustImageRatio(rc);
	Mat mattemp = m_matHistogramB;

	ShowImage(String("HistB IMG"), mattemp, rc);
	mattemp.release();
}
void CCoreObject::DisplayHistogramVideo()
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}

	if (!runningFlag)
	{
		return;
	}
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;

	AdjustImageRatio(rc);

	Mat mattemp = m_matHistogram;

	ShowImage(String("Hist Video"), mattemp, rc);
	mattemp.release();
}
void CCoreObject::DisplayHistogramVideoR()
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}

	if (!runningFlag)
	{
		return;
	}
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;

	AdjustImageRatio(rc);

	Mat mattemp = m_matHistogramR;

	ShowImage(String("HistR Video"), mattemp, rc);
	mattemp.release();
}
void CCoreObject::DisplayHistogramVideoG()
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}

	if (!runningFlag)
	{
		return;
	}
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;

	AdjustImageRatio(rc);

	Mat mattemp = m_matHistogramG;

	ShowImage(String("HistG Video"), mattemp, rc);
	mattemp.release();
}

void CCoreObject::DisplayHistogramVideoB()
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}

	if (!runningFlag)
	{
		return;
	}
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;

	AdjustImageRatio(rc);

	Mat mattemp = m_matHistogramB;

	ShowImage(String("HistB Video"), mattemp, rc);
	mattemp.release();
}

void CCoreObject::DisplayGreyImageR()
{
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;

	AdjustImageRatio(rc);
	Mat mattemp = m_matGreyR;

	ShowImage(String("HistGreyR IMG"), mattemp, rc);
	mattemp.release();
}

void CCoreObject::DisplayGreyImageG()
{
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;

	AdjustImageRatio(rc);
	Mat mattemp = m_matGreyG;

	ShowImage(String("HistGreyG IMG"), mattemp, rc);
	mattemp.release();
}

void CCoreObject::DisplayGreyImageB()
{
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;

	AdjustImageRatio(rc);
	Mat mattemp = m_matGreyB;

	ShowImage(String("HistGreyB IMG"), mattemp, rc);
	mattemp.release();
}


void CCoreObject::DisplayGreyVideoR()
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}

	if (!runningFlag)
	{
		return;
	}
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;

	AdjustImageRatio(rc);

	Mat mattemp = m_matGreyR;

	ShowImage(String("HistGreyR Video"), mattemp, rc);
	mattemp.release();
}

void CCoreObject::DisplayGreyVideoG()
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}

	if (!runningFlag)
	{
		return;
	}
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;

	AdjustImageRatio(rc);

	Mat mattemp = m_matGreyG;

	ShowImage(String("HistGreyG Video"), mattemp, rc);
	mattemp.release();
}

void CCoreObject::DisplayGreyVideoB()
{
	if (!m_VideoCapture.isOpened())
	{
		return;
	}

	if (!runningFlag)
	{
		return;
	}
	CRect rc;
	rc.right = 400;
	rc.bottom = 300;

	AdjustImageRatio(rc);

	Mat mattemp = m_matGreyB;

	ShowImage(String("HistGreyB Video"), mattemp, rc);
	mattemp.release();
}
