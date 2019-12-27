
// OpenCV_MfcDlg.h: 헤더 파일
//

#pragma once

#include "CoreObject.h"
// COpenCVMfcDlg 대화 상자
class COpenCVMfcDlg : public CDialogEx
{
// 생성입니다.
public:
	COpenCVMfcDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENCV_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpenimage();

	shared_ptr<CCoreObject> m_Core;

	afx_msg void OnFileOpenvideo();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
	unsigned int LimitedFrame = 60;

	unsigned int FrameCallStack = 0;
	unsigned int PermitCall = 0;

public:
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();


private:
	unsigned int BitFlag = 0;
	const unsigned int op1 = 1 << 0;
	const unsigned int op2 = 1 << 1;
	const unsigned int op3 = 1 << 2;
	const unsigned int op4 = 1 << 3;
	const unsigned int op5 = 1 << 4;
	const unsigned int op6 = 1 << 5;
	const unsigned int op7 = 1 << 6;
	const unsigned int op8 = 1 << 7;
	const unsigned int op9 = 1 << 8;
	const unsigned int op10 = 1 << 9;
	const unsigned int op11 = 1 << 10;
public:
	afx_msg void OnBnClickedCheck8();
	afx_msg void OnBnClickedCheck9();
	afx_msg void OnBnClickedCheck10();
	afx_msg void OnUsecamvideo();
	afx_msg void OnUseOpenNi();
	afx_msg void OnBnClickedCheck11();
};
