#include "StdAfx.h"
#include "UnicodeFile.h"

CUnicodeFile::CUnicodeFile(LPCTSTR pszFile,int mode)
{
	pFile = NULL;
	fStream = NULL;
	ZeroMemory(m_mode,sizeof(m_mode));
	m_strFile.Format(L"%s",pszFile);
	
	int nMode = 0;
	
	if(mode & modeReadWrite)
	{
		if(mode & modeNoTruncate)
		{
			if(Exists())
			{
				//if file does not exists r+ eill give error
				m_mode[nMode++]= L'r';
				m_mode[nMode++]= L'+';
			}
			else
			{
				//if file does not extsts w+ will create a new file
				m_mode[nMode++]= L'w';
				m_mode[nMode++]= L'+';
			}
		}
		else
		{
			m_mode[nMode++]= L'w';
			m_mode[nMode++]= L'+';
		}
	}
	else
	{
		if((mode&modeRead) && (mode&modeWrite))
		{
			if(mode & modeNoTruncate)
			{
				if(Exists())
				{
					//if file does not exists r+ eill give error
					m_mode[nMode++]= L'r';
					m_mode[nMode++]= L'+';
				}
				else
				{
					//if file does not extsts w+ will create a new file
					m_mode[nMode++]= L'w';
					m_mode[nMode++]= L'+';
				}
			}
			else
			{
				m_mode[nMode++]= L'w';
				m_mode[nMode++]= L'+';
			}
		}
		else if(mode & modeRead)
		{
			m_mode[nMode++]= L'r';
			m_mode[nMode++]= L't';
		}
		else if(mode & modeWrite)
		{
			if(mode & modeNoTruncate)
			{
				m_mode[nMode++]= L'a';
				m_mode[nMode++]= L't';
			}
			else
			{
				m_mode[nMode++]= L'w';
				m_mode[nMode++]= L't';
			}
		}
		else
		{
			m_mode[nMode++]= L'r';
			m_mode[nMode++]= L't';
		}
	}
}

CUnicodeFile::~CUnicodeFile(void)
{
	Close();
}

BOOL CUnicodeFile::Exists()
{
	if(GetFileAttributes(m_strFile) == INVALID_FILE_ATTRIBUTES)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL CUnicodeFile::Open()
{
	CString md(m_mode);
	md += L",ccs=UTF-8";
	errno_t e = _tfopen_s(&fStream, m_strFile, md);
	if (e != 0)
	{
		return FALSE;
	}
	else
	{
		pFile = new CStdioFile(fStream);
		return TRUE;
	}
}

void CUnicodeFile::Close()
{
	if(pFile)
	{
		pFile->Close();
		delete pFile;
		pFile = NULL;
		fStream = NULL;
	}
}

void CUnicodeFile::WriteString(LPCTSTR lpsz)
{
	pFile->WriteString(lpsz);
}

void CUnicodeFile::ReadString(CString& str)
{
	pFile->ReadString(str);
}

void CUnicodeFile::SeekToEnd()
{
	pFile->SeekToEnd();
}

void CUnicodeFile::SeekToBegin()
{
	pFile->SeekToBegin();
}
