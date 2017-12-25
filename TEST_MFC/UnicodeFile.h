#if !defined(UNICODEFILE_H__96656FC0_EC55_4275_ADC0_46F4E8843A78__INCLUDED_)
#define UNICODEFILE_H__96656FC0_EC55_4275_ADC0_46F4E8843A78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

class CUnicodeFile
{
public:
	CUnicodeFile(LPCTSTR pszFile,int mode);
	~CUnicodeFile(void);

	enum OpenFlags {
		modeRead =			(int)0x0000,
		modeWrite =			(int)0x0001,
		modeReadWrite =		(int)0x0002,
		modeNoTruncate =	(int)0x0004
	};
	BOOL Open();
	void Close();
	void WriteString(LPCTSTR lpsz);
	void ReadString(CString& str);
	void SeekToEnd();
	void SeekToBegin();
	BOOL Exists();

private:
	FILE *fStream;
	CString m_strFile;
	TCHAR m_mode[5];
	CStdioFile *pFile;
};

#endif
