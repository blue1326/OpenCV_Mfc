
// OpenCV_MfcDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "OpenCV_Mfc.h"
#include "OpenCV_MfcDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenCVMfcDlg 대화 상자



COpenCVMfcDlg::COpenCVMfcDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPENCV_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenCVMfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COpenCVMfcDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_OPENIMAGE, &COpenCVMfcDlg::OnFileOpenimage)
	ON_COMMAND(ID_FILE_OPENVIDEO, &COpenCVMfcDlg::OnFileOpenvideo)

	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK1, &COpenCVMfcDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &COpenCVMfcDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &COpenCVMfcDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &COpenCVMfcDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &COpenCVMfcDlg::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &COpenCVMfcDlg::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK7, &COpenCVMfcDlg::OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK8, &COpenCVMfcDlg::OnBnClickedCheck8)
	ON_BN_CLICKED(IDC_CHECK9, &COpenCVMfcDlg::OnBnClickedCheck9)
	ON_BN_CLICKED(IDC_CHECK10, &COpenCVMfcDlg::OnBnClickedCheck10)
	ON_COMMAND(ID_FILE_USECAMVIDEO, &COpenCVMfcDlg::OnUsecamvideo)
	ON_COMMAND(ID_FILE_USEOPENNI, &COpenCVMfcDlg::OnUseOpenNi)
	ON_BN_CLICKED(IDC_CHECK11, &COpenCVMfcDlg::OnBnClickedCheck11)
END_MESSAGE_MAP()


// COpenCVMfcDlg 메시지 처리기

BOOL COpenCVMfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_Core = CCoreObject::GetInstance();
	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetTimer(0, 0, NULL); //1000 = 1sec 100 = 0.1sec
	//현재 1초 10번 호출 0.1 일경우 100번 호출 0.01일 경우 1000번 호출
	/*RECT rc;
	GetDlgItem(IDC_IMGCTL)->GetClientRect(&rc);
	CClientDC(GetDlgItem(IDC_IMGCTL)).FillSolidRect(&rc, GetSysColor(COLOR_BTNHIGHLIGHT));*/ // 전체
	//ExtFloodFill(CClientDC(GetDlgItem(IDC_IMGCTL)), 1, 1, RGB(255, 255, 255), FLOODFILLBORDER);



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.

}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void COpenCVMfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR COpenCVMfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void COpenCVMfcDlg::OnFileOpenimage()
{
	CString strFileName;

	CString strFilter;

	// 파일대화창에서 파일 형식 설정

	strFilter = "Bitmap image|*.bmp|JPEG image|*.jpg|GIF image|*.gif|PNG image|*.png|All Files(*.*)|*.*||";

	// TRUE이면 불러오기..., FALSE이면 저장하기...

	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, strFilter);

	dlg.m_ofn.nFilterIndex = 2; // 파일형식의 인덱스로 첨에 보이게... 여기서는 두번째로...



	if (dlg.DoModal() == IDOK)

	{
		strFileName = dlg.m_ofn.lpstrFile; // 파일명 받기

		//m_nFilterIndex = dlg.m_ofn.nFilterIndex; // 파일형식 몇번째 선택했는지...

		// strFileName으로 파일 불러오기를 해주면 됩니다. 위에서 FALSE이면 저장하기...
	}
	if (!strFileName.IsEmpty())
	{
		m_Core->LoadImage((CStringA)strFileName);
		m_Core->DisplayImage();
		if (BitFlag & op1)
			m_Core->DisplayImageR();
		if (BitFlag & op2)
			m_Core->DisplayImageG();
		if (BitFlag & op3)
			m_Core->DisplayImageB();
		if (BitFlag & op4)
			m_Core->DisplayHistogramImage();
		if (BitFlag & op5)
			m_Core->DisplayHistogramImageR();
		if (BitFlag & op6)
			m_Core->DisplayHistogramImageG();
		if (BitFlag & op7)
			m_Core->DisplayHistogramImageB();
		if (BitFlag & op8)
			m_Core->DisplayGreyImageR();
		if (BitFlag & op9)
			m_Core->DisplayGreyImageG();
		if (BitFlag & op10)
			m_Core->DisplayGreyImageB();
	}
}


void COpenCVMfcDlg::OnFileOpenvideo()
{
	CString strFileName;

	CString strFilter;

	// 파일대화창에서 파일 형식 설정

	strFilter = "Video Files(*.AVI;*.WMV;*.MKV;*.MPEG;*.MP4)|*.AVI;*.WMV;*.MKV;*.MPEG;*.MP4|All Files(*.*)|*.*||";

	// TRUE이면 불러오기..., FALSE이면 저장하기...

	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, strFilter);

	dlg.m_ofn.nFilterIndex = 1;



	if (dlg.DoModal() == IDOK)

	{
		strFileName = dlg.m_ofn.lpstrFile; // 파일명 받기

		//m_nFilterIndex = dlg.m_ofn.nFilterIndex; // 파일형식 몇번째 선택했는지...

		// strFileName으로 파일 불러오기를 해주면 됩니다. 위에서 FALSE이면 저장하기...
	}
	if (!strFileName.IsEmpty())
		m_Core->LoadVideo((CStringA)strFileName);

}


void COpenCVMfcDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}


void COpenCVMfcDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void COpenCVMfcDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_Core->TimerTick();
	if (m_Core->PermitCall() && m_Core->VideoLoaded())
	{
		m_Core->DisplayVideo();
		if (BitFlag&op1)
			m_Core->DisplayVideoR();
		if (BitFlag&op2)
			m_Core->DisplayVideoG();
		if (BitFlag&op3)
			m_Core->DisplayVideoB();
		if (BitFlag&op4)
			m_Core->DisplayHistogramVideo();
		if (BitFlag&op5)
			m_Core->DisplayHistogramVideoR();
		if (BitFlag&op6)
			m_Core->DisplayHistogramVideoG();
		if (BitFlag&op7)
			m_Core->DisplayHistogramVideoB();
		if (BitFlag&op8)
			m_Core->DisplayGreyVideoR();
		if (BitFlag&op9)
			m_Core->DisplayGreyVideoG();
		if (BitFlag&op10)
			m_Core->DisplayGreyVideoB();
		if (BitFlag&op11)
			m_Core->MeanShift();
	}

	CDialogEx::OnTimer(nIDEvent);
}


void COpenCVMfcDlg::OnBnClickedCheck1()
{
	if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
	{
		BitFlag |= op1;
	}
	else
	{
		BitFlag &= ~op1;
	}
}


void COpenCVMfcDlg::OnBnClickedCheck2()
{
	if (((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck())
	{
		BitFlag |= op2;
	}
	else
	{
		BitFlag &= ~op2;
	}
}


void COpenCVMfcDlg::OnBnClickedCheck3()
{
	if (((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck())
	{
		BitFlag |= op3;
	}
	else
	{
		BitFlag &= ~op3;
	}
}



void COpenCVMfcDlg::OnBnClickedCheck4()
{
	if (((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck())
	{
		BitFlag |= op4;
	}
	else
	{
		BitFlag &= ~op4;
	}
}


void COpenCVMfcDlg::OnBnClickedCheck5()
{
	if (((CButton*)GetDlgItem(IDC_CHECK5))->GetCheck())
	{
		BitFlag |= op5;
	}
	else
	{
		BitFlag &= ~op5;
	}
}


void COpenCVMfcDlg::OnBnClickedCheck6()
{
	if (((CButton*)GetDlgItem(IDC_CHECK6))->GetCheck())
	{
		BitFlag |= op6;
	}
	else
	{
		BitFlag &= ~op6;
	}
}

void COpenCVMfcDlg::OnBnClickedCheck7()
{
	if (((CButton*)GetDlgItem(IDC_CHECK7))->GetCheck())
	{
		BitFlag |= op7;
	}
	else
	{
		BitFlag &= ~op7;
	}
}



void COpenCVMfcDlg::OnBnClickedCheck8()
{
	if (((CButton*)GetDlgItem(IDC_CHECK8))->GetCheck())
	{
		BitFlag |= op8;
	}
	else
	{
		BitFlag &= ~op8;
	}
}


void COpenCVMfcDlg::OnBnClickedCheck9()
{
	if (((CButton*)GetDlgItem(IDC_CHECK9))->GetCheck())
	{
		BitFlag |= op9;
	}
	else
	{
		BitFlag &= ~op9;
	}
}


void COpenCVMfcDlg::OnBnClickedCheck10()
{
	if (((CButton*)GetDlgItem(IDC_CHECK10))->GetCheck())
	{
		BitFlag |= op10;
	}
	else
	{
		BitFlag &= ~op10;
	}
}


void COpenCVMfcDlg::OnBnClickedCheck11()
{
	if (((CButton*)GetDlgItem(IDC_CHECK11))->GetCheck())
	{
		BitFlag |= op11;
	}
	else
	{
		BitFlag &= ~op11;
	}
}
void COpenCVMfcDlg::OnUsecamvideo()
{
	m_Core->UseCamVideo();
}


void COpenCVMfcDlg::OnUseOpenNi()
{
	m_Core->UseKinnectVideo();
}


