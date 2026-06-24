#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "String++.h"

////////////////////////////////////////////////////////////////////////////////
// CStringEx Class

CStringEx::CStringEx(const char* str)
{
	if(str == 0)
	{
		m_nLength = 0;
		m_pData = 0;
	}
	else
	{
		m_nLength = strlen(str);
		m_pData = new char[m_nLength + 1];
		assert(m_pData != 0);
		strcpy(m_pData, str);
	}
}

CStringEx::CStringEx(const CStringEx& str)
{ 
	if(str == 0)
	{
		m_nLength = 0;
		m_pData = 0;
	}
	else
	{
		m_nLength = str.m_nLength; 
		m_pData = new char[m_nLength + 1];
		assert(m_pData != 0);
		strcpy(m_pData, str.m_pData); 
	}
}

int CStringEx::GetLength() const 
{
   if (m_pData) return strlen(m_pData);
   else return 0;
}

int CStringEx::IsEmpty() const 
{
   return GetLength()>0 ? FALSE:TRUE;
}

void CStringEx::Empty() 
{
   m_nLength=0;
   if (m_pData) {
      delete m_pData;
      m_pData=0;
   }
}

int CStringEx::Find(const char chr) const 
{
   return Find(chr,0);
}

int CStringEx::ReverseFind(char chr) const 
{
   if (IsEmpty()) return -1;
   char *ptr=strrchr(m_pData,chr);
   if (ptr) return (int)(ptr-m_pData);
   else return -1;
}

int CStringEx::Find(const char chr,int nStart) const
{
   if (nStart>=m_nLength) return -1;
   char *ptr=strchr(m_pData+nStart,chr);
   if (ptr) return (int)(ptr-m_pData);
   else return -1;
}

int CStringEx::FindOneOf(const char *sChars) const
{
   char *ptr=strchrs(m_pData,sChars);
   if (ptr) return (int)(ptr-m_pData);
   else return -1;
}
 
int CStringEx::Find(const char *str) const
{ 
   return Find(str,0);
}

int CStringEx::Find(const char *str,int nStart) const
{
   if (nStart>=m_nLength) return -1;
   char *ptr=strstr(m_pData+nStart,str);
   if (ptr) return (int)(ptr-m_pData);
   else return -1;
}
   
CStringEx CStringEx::Mid( int nFirst, int nCount ) const
{
   if (nCount<=0) return CStringEx((const char*)0);
   int nPos=nFirst+nCount;
   char chr=m_pData[nPos];
   m_pData[nPos]=0;
   CStringEx newString((const char*)(m_pData+nFirst));
   m_pData[nPos]=chr;
   return newString;
}

CStringEx CStringEx::Mid( int nFirst ) const
{
   return Mid(nFirst,GetLength());
}


CStringEx CStringEx::Left(int nCount) const
{
   return Mid(nCount);
}


CStringEx CStringEx::Right(int nCount) const
{
   int nFirst=GetLength()-nCount;
   return Mid(nFirst,nCount);
}

void CStringEx::TrimRight()
{
   if (!m_pData) return;
   strtrimright(m_pData);
   m_nLength=strlen(m_pData);
}

void CStringEx::TrimLeft()
{
   if (!m_pData) return;
   strtrimleft(m_pData);
   m_nLength=strlen(m_pData);
}

void CStringEx::TrimLeft(LPCTSTR str)
{
   int nCount=0;
   while (strchr(str,m_pData[nCount]))
      nCount++;
   Delete(0,nCount);
}

char CStringEx::GetAt(int nIndex) const
{
   if (nIndex>=m_nLength) return 0;
   return m_pData[nIndex];
}

void CStringEx::SetAt(int nIndex, char chr)
{
   if (nIndex>=m_nLength) return;
   m_pData[nIndex]=chr;
   if (!chr) m_nLength=strlen(m_pData);
}

int CStringEx::Replace(const char *sOld,const char *sNew)
{
   unsigned int nLength=strlen(m_pData);
   unsigned int nSrcLength=strlen(sOld);
   unsigned int nDstLength=strlen(sNew);
   unsigned int nCount=0;
   char *p,*ptr;
   for (p=m_pData;
   p<(m_pData+nLength) && (p=strstr(p,sOld));
   p+=nSrcLength)
      nCount++;
   if (!nCount)
      return 0;
   nCount=nLength+nCount*(nDstLength-nSrcLength);
   p=ptr=new char[nCount+1];
   if (nCount>=nLength) {
      strcpy(ptr,m_pData);
      while (p=strstr(p,sOld)) {
         strdel(ptr,p,strlen(sOld));
         strins(ptr,p,sNew);
         p+=nDstLength;
      }
   } else if (nCount==nDstLength) {
      strcpy(ptr,sNew);
   } else
      memset(ptr,0,nCount);
   delete m_pData;
   m_pData=ptr;
   m_nLength=strlen(ptr);
   return nCount;
}

int CStringEx::Insert(int nIndex,const char *str)
{
   assert(m_nLength==(int)strlen(m_pData));
   m_nLength+=strlen(str);
   char *ptr=new char[m_nLength+1];
   strcpy(ptr,m_pData);
   delete m_pData;
   m_pData=ptr;
   strins(m_pData,ptr+nIndex,str);
   assert(m_nLength==(int)strlen(m_pData));
   return m_nLength;
}

int CStringEx::Delete(int nIndex,int nCount)
{
   if ((nIndex+nCount)>m_nLength)
      nCount=m_nLength-nIndex;
   strcpy(m_pData+nIndex,m_pData+nIndex+nCount);
   m_nLength-=nCount;
   assert(m_nLength==(int)strlen(m_pData));
   return nCount;
}

// Y.Kim,20030209) Add string at the end.
int CStringEx::Add(const char *qAdd)
{
   return Insert(GetLength(),qAdd);
}

// Y.Kim,20030209) Add string tranformed from an integer at the end.
int CStringEx::AddInteger(int nAdd,int nBase)
{
   char qNumber[256];
   char *pNumber=_itoa(nAdd,qNumber,nBase);
   return Add((const char*)pNumber);
}
 
// Y.Kim,20030209) Add string tranformed from a double at the end.
int CStringEx::AddDouble(double dAdd,const char *qFormat)
{
   char qNumber[256];
   sprintf(qNumber,qFormat,dAdd);
   return Add(qNumber);
}

int CStringEx::Compare(const char *str) const
{
   return strcmp(m_pData,str);
}

int CStringEx::Compare(const char *str,unsigned int count) const
{
   return strncmp(m_pData,str,count);
}

CStringEx& CStringEx::operator +=(const CStringEx& str)
{
	m_nLength += str.m_nLength;
	char* pNew = new char[m_nLength + 1];
	assert(pNew != 0);
	strcpy(pNew, m_pData);
	strcat(pNew, str.m_pData);
	delete m_pData;
	m_pData = pNew;

	return *this;
}

CStringEx& CStringEx::operator =(const char* str)
{
	if (m_pData) delete m_pData;
   m_nLength = str ? strlen(str):0;
	m_pData = new char[m_nLength + 1]; 
	assert(m_pData != 0);
   if (str) strcpy(m_pData, str);
   else m_pData=0;

	return *this;
}

CStringEx& CStringEx::operator =(const CStringEx& str)
{
	assert(str != 0);
	if (m_pData) delete m_pData;
   m_nLength = str.m_pData ? strlen(str.m_pData):0;
	m_pData = new char[m_nLength + 1]; 
	assert(m_pData != 0);
	if (str.m_pData) strcpy(m_pData, str.m_pData);
   else m_pData=0;

	return *this;
}

int CStringEx::Format(const char* format, ...)
{
	assert(format != 0);

	int len;
	char* MaxBuf;
	for(int i = 5; ; i ++)
	{
		len = (int)pow(2, i);
		MaxBuf = new char[len];
		if (!MaxBuf) return 0;
		// some UNIX's do not support vsnprintf and snprintf
		len = _vsnprintf(MaxBuf, len, format, (char*)(&format + 1));
		if (len > 0) break;
		delete []MaxBuf;
		if (len == 0) return 0;
	}

	if (!m_pData)
	{
		m_nLength = len;
		m_pData = new char[m_nLength + 1];
	}
	else if (m_nLength < len)
	{
		delete m_pData;
		m_nLength = len;
		m_pData = new char[m_nLength + 1];
	}
	if (m_pData) 
		strcpy(m_pData, MaxBuf);
	else
		len = 0;
	delete []MaxBuf;

	return len;
}

bool CStringEx::Match(char* Wildcards, char* str)
{
	bool Yes = 1;

	//iterate and delete '?' and '*' one by one
	while(*Wildcards != '\0' && Yes && *str != '\0')
	{
		if (*Wildcards == '?') str ++;
		else if (*Wildcards == '*')
		{
			Yes = Scan(Wildcards, str);
			Wildcards --;
		}
		else
		{
			Yes = (*Wildcards == *str);
			str ++;
		}
		Wildcards ++;
	}
	while (*Wildcards == '*' && Yes)  Wildcards ++;

	return Yes && *str == '\0' && *Wildcards == '\0';
}

// scan '?' and '*'
bool CStringEx::Scan(char*& Wildcards, char*& str)
{
	// remove the '?' and '*'
	for(Wildcards ++; *str != '\0' && (*Wildcards == '?' || *Wildcards == '*'); Wildcards ++)
		if (*Wildcards == '?') str ++;
	while ( *Wildcards == '*') Wildcards ++;
	
	// if str is empty and Wildcards has more characters or,
	// Wildcards is empty, return 
	if (*str == '\0' && *Wildcards != '\0') return false;
	if (*str == '\0' && *Wildcards == '\0')	return true; 
	// else search substring
	else
	{
		char* wdsCopy = Wildcards;
		char* strCopy = str;
		bool  Yes     = 1;
		do 
		{
			if (!Match(Wildcards, str))	strCopy ++;
			Wildcards = wdsCopy;
			str		  = strCopy;
			while ((*Wildcards != *str) && (*str != '\0')) str ++;
			wdsCopy = Wildcards;
			strCopy = str;
		}while ((*str != '\0') ? !Match(Wildcards, str) : (Yes = false) != false);

		if (*str == '\0' && *Wildcards == '\0')	return true;

		return Yes;
	}
}

//bool operator==(const CStringEx& s1, const CStringEx& s2);

bool operator==(const CStringEx& s1, const char* s2)
{
   const char *p1=(const char*)s1;
   if (!p1 || !s2) return FALSE;
   return !strcmp(p1,s2);
}

//bool operator==(const char* s1, const CStringEx& s2);
//bool operator!=(const CStringEx& s1, const CStringEx& s2);
//bool operator!=(const CStringEx& s1, const char* s2);
//bool operator!=(const char* s1, const CStringEx& s2);
//bool operator<(const CStringEx& s1, const CStringEx& s2);
//bool operator<(const CStringEx& s1, const char* s2);
//bool operator<(const char* s1, const CStringEx& s2);
//bool operator>(const CStringEx& s1, const CStringEx& s2);
//bool operator>(const CStringEx& s1, const char* s2);
//bool operator>(const char* s1, const CStringEx& s2);
//bool operator<=(const CStringEx& s1, const CStringEx& s2);
//bool operator<=(const CStringEx& s1, const char* s2);
//bool operator<=(const char* s1, const CStringEx& s2);
//bool operator>=(const CStringEx& s1, const CStringEx& s2);
//bool operator>=(const CStringEx& s1, const char* s2);
//bool operator>=(const char* s1, const CStringEx& s2);

////////////////////////////////////////////////////////////////////////////////
// CTokenExEx Class

CTokenEx::CTokenEx( CStringEx string,const char *delimiter )
{
	m_sTarget=_T((LPCTSTR)string);
   m_sDelimiter=_T(delimiter);
}

CTokenEx::CTokenEx( const char *string,const char *delimiter )
{
   m_sTarget=_T(string);
   m_sDelimiter=_T(delimiter);
}

CTokenEx::CTokenEx()
{
	m_sTarget=_T("");
   m_sDelimiter=_T("");
}

CTokenEx::~CTokenEx()
{
}

int CTokenEx::IsNext()
{
   if (m_sTarget.IsEmpty()) return FALSE;
   if (m_sTarget.FindOneOf((LPCTSTR)m_sDelimiter)>0) return TRUE;
   if (m_sTarget.GetLength()) return TRUE;
   return FALSE;
}

CStringEx CTokenEx::GetNextToken()
{
   CStringEx rString=_T("");
   int nPos;
   while (!(nPos=m_sTarget.FindOneOf((LPCTSTR)m_sDelimiter))) {
      m_sTarget.Delete(0);
   }
   if (nPos>0) {
      rString=m_sTarget.Mid(0,nPos);
      m_sTarget.Delete(0,nPos+1);
   } else {
      rString=m_sTarget;
      m_sTarget.Empty();
   }
   return rString;
}

int CTokenEx::GetNextTokenCount()
{
   CStringEx sBackUp(m_sTarget);
   int nCount=0;
   while (IsNext()) {
      GetNextToken();
      nCount++;
   }
   m_sTarget=sBackUp;
   return nCount;
}

CStringEx CTokenEx::GetTokenByIndex( unsigned int nIndex )
{
   CStringEx sBackUp(m_sTarget),rString;
   unsigned int nCount=0;
   while (IsNext()) {
      if (nCount==nIndex) {
         rString=GetNextToken();
         m_sTarget=sBackUp;
         return rString;
      }
      GetNextToken();
      nCount++;
   }
   m_sTarget=sBackUp;
   return _T("");
}

CStringEx CTokenEx::GetTokenValueOfEq( const CStringEx& sTarget )
{
   CStringEx sBackUp(m_sTarget),rToken,rTarget;
   int nResult;
   while (IsNext()) {
      rToken=GetNextToken();
      nResult=rToken.Find("=");
      rTarget=rToken.Left(nResult);
      if (!rTarget.Compare(sTarget)) {
         rTarget+="=";
         rToken.Replace(rTarget,"");
         rToken.TrimLeft();
         m_sTarget=sBackUp;
         return rToken;
      }
   }
   m_sTarget=sBackUp;
   return _T("");
}

////////////////////////////////////////////////////////////////////////////////
// End of String++.cpp
