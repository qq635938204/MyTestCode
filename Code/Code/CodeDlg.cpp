
// CodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Code.h"
#include "CodeDlg.h"
#include "afxdialogex.h"
#include "utf8.hpp"
#include "resource.h"
#include "../MD5/MD5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SAFE_DELETE(ptr) if((ptr)){delete (ptr); (ptr) = NULL;}


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCodeDlg 对话框



CCodeDlg::CCodeDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CCodeDlg::IDD, pParent), m_lTarget(0), m_lSrc(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPLITTARGET, m_target);
	DDX_Control(pDX, IDC_RICHEDIT2_TEXT, m_Text);
	DDX_Control(pDX, IDC_SPLIT_SRC, m_SrcCode);
	DDX_Control(pDX, IDC_MFCEDITBROWSE_PATH, m_path);
}

BEGIN_MESSAGE_MAP(CCodeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCodeDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCodeDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_DECODE, &CCodeDlg::OnBnClickedButtonDecode)
	ON_BN_CLICKED(IDC_BUTTON_ENCODE, &CCodeDlg::OnBnClickedButtonEncode)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CCodeDlg::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_EMPTY, &CCodeDlg::OnBnClickedButtonEmpty)
	ON_BN_CLICKED(IDC_MFCBUTTON_MD5, &CCodeDlg::OnBnClickedMfcbuttonMd5)
END_MESSAGE_MAP()


// CCodeDlg 消息处理程序

BOOL CCodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//ModifyStyle(NULL, WS_THICKFRAME);
	m_target.SetDropDownMenu(IDR_MENU_TAR, 0);
	m_SrcCode.SetDropDownMenu(IDR_MENU_SRC,0);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCodeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCodeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCodeDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CCodeDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CCodeDlg::OnBnClickedButtonDecode()
{
	// TODO:  在此添加控件通知处理程序代码
	CString csText;
	wstring wstrText;
	m_Text.GetWindowText(csText);
	if (csText.IsEmpty())
		return;
	m_csSrcStr = csText;
	switch (m_lSrc)
	{
	case BASE64:
		csText.Replace(_T("\r\n"), _T(""));
		break;
	case QUOTED_PRINTABLE:
		csText.Replace(_T("=\r\n"), _T(""));
		break;
	default:
		break;
	}
	
	int ibytes = WideCharToMultiByte(CP_ACP, 0, csText.GetBuffer(), -1, NULL, 0, NULL, NULL);
	char*pText = new char[ibytes + 1];
	memset(pText, 0, ibytes + 1);
	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, csText, -1, pText, ibytes, NULL, NULL);
	string str, strValue;
	str = pText;
	switch (m_lSrc)
	{
	case BASE64:
		strValue = base64_decode(str);
		break;
	case QUOTED_PRINTABLE:
		strValue = quotedprintable_decode(str);
		break;
	default:
		break;
	}
	
	switch (m_lTarget)
	{
	case UTF8:
	{
		Utf8::Decode(strValue, wstrText);
		csText = wstrText.c_str();
	}
		break;
	case GBK:
	case GB2312:
	{
		csText = strValue.c_str();
				   
	}
		break;
	default:
		break;
	}
	m_Text.SetWindowText(csText);
	m_Text.PostMessage(WM_VSCROLL, SB_TOP, 0);
	SAFE_DELETE(pText);
}


void CCodeDlg::OnBnClickedButtonEncode()
{
	// TODO:  在此添加控件通知处理程序代码
	CString csText;
	string strResult, strSrc;
	m_Text.GetWindowText(csText);
	if (csText.IsEmpty())
		return;
	m_csSrcStr = csText;
	switch (m_lTarget)
	{
	case UTF8:
	{
		wstring wstrText = csText.GetBuffer();
		Utf8::Encode(wstrText, strSrc);
	}
		break;
	case GBK:
	case GB2312:
	{
		int ibytes = WideCharToMultiByte(CP_ACP, 0, csText, -1, NULL, 0, NULL, NULL);
		char*pText = new char[ibytes + 1];
		memset(pText, 0, ibytes + 1);
		WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, csText, -1, pText, ibytes, NULL, NULL);
		strSrc = pText;
		SAFE_DELETE(pText);
	}
		break;
	default:
		break;
	}

	switch (m_lSrc)
	{
	case BASE64:
		strResult = base64_encode(strSrc);
		break;
	case QUOTED_PRINTABLE:
		strResult = quotedprintable_encode(strSrc);
		break;
	default:
		break;
	}
	csText = strResult.c_str();

	CString csOut;
	FormatOutPut(csText, csOut,m_lSrc);
	m_Text.SetWindowText(csOut);
	m_Text.PostMessage(WM_VSCROLL, SB_TOP, 0);
}


static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

static const char base64_table[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


static inline bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(const string& decoded_string)
{
	const char base64_pad = '=';
	char end = '\0';
	string out;
	size_t inlen = decoded_string.size();
	size_t inlen1, inlen2 = inlen % 3;
	inlen1 = inlen - inlen2;
	int i;
	if (inlen1 > 0)
	for (i = 0; i < inlen1; i += 3)
	{
		out += base64_table[(decoded_string[i] & 0xFF) >> 2];

		out += base64_table[((decoded_string[i] & 0x3) << 4) | ((decoded_string[i + 1] & 0xF0) >> 4)];
		out += base64_table[((decoded_string[i + 1] & 0xF) << 2) | ((decoded_string[i + 2] & 0xC0) >> 6)];
		out += base64_table[decoded_string[i + 2] & 0x3f];
	}
	if (inlen2 > 0)
	{
		unsigned char fragment;
		out += base64_table[(decoded_string[inlen1] & 0xFF) >> 2];
		fragment = (decoded_string[inlen1] & 0x3) << 4;
		if (inlen2 > 1)
			fragment |= (decoded_string[inlen1 + 1] & 0xF0) >> 4;
		out += base64_table[fragment];
		out += (inlen2 < 2) ? base64_pad : base64_table[(decoded_string[inlen1 + 1] & 0xF) << 2];
		out += base64_pad;
	}
	out += end;
	return out;
}

std::string base64_decode(std::string const& encoded_string) 
{
	size_t in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i == 4) {
			for (i = 0; i < 4; i++)
				char_array_4[i] = (unsigned char)base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
		for (j = i; j < 4; j++)
			char_array_4[j] = 0;

		for (j = 0; j < 4; j++)
			char_array_4[j] = (unsigned char)base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	return ret;
}


BOOL CCodeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_COMMAND)
	{
		switch (pMsg->wParam)
		{
		case ID_TARGET_UTF:
		{
			m_lTarget = UTF8;
			m_target.SetWindowText(_T("UTF-8"));
		}
			break;
		case ID_TARGET_GB2312:
		{
			m_lTarget = GB2312;
			m_target.SetWindowText(_T("GB2312"));
		}
			break;
		case ID_TARGET_GBK:
		{
			m_lTarget = GBK;
			m_target.SetWindowText(_T("GBK"));
		}
			break;
		case ID_SRC_BASELINE:
		{
			m_lSrc = BASE64;
			m_SrcCode.SetWindowText(_T("Base64"));
		}
			break;
		case ID_SRC_QUOTED32775:
		{
			m_lSrc = QUOTED_PRINTABLE;
			m_SrcCode.SetWindowText(_T("Quoted-printable"));
		}
			break;
		default:
			break;
		}

	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CCodeDlg::OnBnClickedButtonBack()
{
	// TODO:  在此添加控件通知处理程序代码
	m_Text.SetWindowText(m_csSrcStr); 
	m_Text.UpdateWindow();
}


void CCodeDlg::OnBnClickedButtonEmpty()
{
	// TODO:  在此添加控件通知处理程序代码
	CString csText;
	m_Text.GetWindowText(m_csSrcStr);
	csText.Empty();
	m_Text.SetWindowText(csText);
	m_Text.UpdateWindow();
}


void FormatOutPut(const CString& csSrc, CString& csDest,long lType)
{
	if (csSrc.IsEmpty())
		return;
	csDest.Empty();
	int n = 0, i = 0;
	for (n = 0; n < csSrc.GetLength();n++)
	{
		csDest += csSrc[n];
		i++;
		if (i == 70)
		{
			switch (lType)
			{
			case BASE64:
				csDest += _T("\r\n");
				break;
			case QUOTED_PRINTABLE:
				break;
			default:
				break;
			}
			i = 0;
		}
	}
}

std::string	quotedprintable_encode(const string& src)
{
	int line_len;
	int max_line_len = 70;
	char tmp[8];
	// 输出的行长度计数         
	line_len = 0;
	char end = '\0';
	string dst;
	for (size_t i = 0; i < src.size(); i++)
	{         // ASCII 33-60, 62-126原样输出，其余的需编码         
		if ((src[i] >= '!') && (src[i] <= '~') && (src[i] != '='))
		{
			dst += src[i];
			line_len++;
		}
		else
		{
			char c1 = 0x0F & (src[i] >> 4);
			char c2 = 0x0F & src[i];

			dst += '=';
			dst += (c1 < 0xA) ? (c1 + 48) : (c1 + 55);
			dst += (c2 < 0xA) ? (c2 + 48) : (c2 + 55);
			line_len += 3;
		}
		if (line_len >= max_line_len)
		{
			sprintf_s(tmp,8, "=\r\n");
			dst += tmp;
			line_len = 0;
		}
	}       // 输出加个结束符     
	dst += end;
	return dst;
}

std::string quotedprintable_decode(const string& src)
{
	// 输出的字符计数     
	size_t i = 0;
	string dst;
	char tmp = 0, end = '\0';
	while (i < src.size())
	{
		if (src[i] == '=')// 是编码字节     
		{
			if (i<src.size() - 2)
			{
				char ch1 = src[i + 1];
				char ch2 = src[i + 2];
				if ((src[i + 1] == '/r') || (src[i + 1] == '/n')) continue;
				tmp = ((ch1>'9') ? (ch1 - 'A' + 10) : (ch1 - '0')) * 16 + ((ch2>'9') ? (ch2 - 'A' + 10) : (ch2 - '0'));
				dst += tmp;
				i += 3;
			}
		}
		else// 非编码字节       
		{
			dst += src[i];
			i++;
		}

	}       // 输出加个结束符     
	dst += end;
	return dst;
}

void CCodeDlg::OnBnClickedMfcbuttonMd5()
{
	// TODO:  在此添加控件通知处理程序代码
	CString csPath,csMD5;
	m_path.GetWindowText(csPath);
	if (csPath.IsEmpty())
		return;
	char*pPath = NULL,*pText=NULL;
	int nSize = WideCharToMultiByte(CP_ACP, 0, csPath, -1, NULL, 0, NULL, NULL);
	long lSize(0);
	pPath = new char[nSize + 1];
	memset(pPath, 0, nSize + 1);
	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, csPath, -1, pPath, nSize, NULL, NULL);
	FILE *pFile;
	if (fopen_s(&pFile, pPath, "a+") == 0)
	{
		fseek(pFile, SEEK_SET, SEEK_END);
		lSize = ftell(pFile);
		pText = new char[lSize + 1];
		memset(pText, 0, lSize + 1);
		fseek(pFile, 0, SEEK_SET);
		fread_s(pText, lSize, 1, lSize, pFile);
		/*CMD5 md5;
		md5.init();
		md5.UpdateMd5(pText, lSize);
		md5.Finalize();
		md5.printMd5();
		csMD5 = md5.GetMd5().c_str();*/
		fclose(pFile);
		SAFE_DELETE(pText);
	}
	SAFE_DELETE(pPath);
	m_Text.SetWindowText(csMD5);
}
