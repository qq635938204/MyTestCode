
// CodeDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <string>
#include "afxcmn.h"
#include "afxeditbrowsectrl.h"
using namespace std;

enum TARGET
{
	UTF8=0,
	GB2312,
	GBK,
};

enum SRC
{
	BASE64=0,
	QUOTED_PRINTABLE,
};


// CCodeDlg �Ի���
class CCodeDlg : public CDialogEx
{
// ����
public:
	CCodeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CODE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CSplitButton m_target;
	CRichEditCtrl m_Text;
	CSplitButton m_SrcCode;
	CMFCEditBrowseCtrl m_path;
private:
	long m_lTarget;
	CString m_csSrcStr;
	long m_lSrc;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonDecode();
	afx_msg void OnBnClickedButtonEncode();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonEmpty();	
	afx_msg void OnBnClickedMfcbuttonMd5();
};

std::string base64_encode(const string& src);
std::string base64_decode(const string & src);
void FormatOutPut(const CString& csSrc, CString& csDest,long lType);
std::string quotedprintable_encode(const string&src);
std::string quotedprintable_decode(const string&src);