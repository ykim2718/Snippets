#include "stdafx.h"
#include "Token.h"

/////////////////////////////////////////////////////////////////////////////
// shik96

CToken::CToken( CString string,const char *delimiter )
{
	m_sTarget=_T((LPCTSTR)string);
   m_sDelimiter=_T(delimiter);
}

CToken::CToken( const char *string,const char *delimiter )
{
   m_sTarget=_T(string);
   m_sDelimiter=_T(delimiter);
}

CToken::CToken()
{
	m_sTarget=_T("");
   m_sDelimiter=_T("");
}

CToken::~CToken()
{
}

BOOL CToken::IsNext()
{
   if (m_sTarget.IsEmpty()) return FALSE;
   if (m_sTarget.FindOneOf((LPCTSTR)m_sDelimiter)>0) return TRUE;
   if (m_sTarget.GetLength()) return TRUE;
   return FALSE;
}

CString CToken::GetNextToken()
{
   CString rString=_T("");
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

int CToken::GetNextTokenCount()
{
   CString sBackUp(m_sTarget);
   int nCount=0;
   while (IsNext()) {
      GetNextToken();
      nCount++;
   }
   m_sTarget=sBackUp;
   return nCount;
}

CString CToken::GetTokenByIndex( unsigned int nIndex )
{
   CString sBackUp(m_sTarget),rString;
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

CString CToken::GetTokenValueOfEq( const CString& sTarget )
{
   CString sBackUp(m_sTarget),rToken,rTarget;
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

/////////////////////////////////////////////////////////////////////////////

template <class T,int nrl,int nrh,int ncl,int nch>
T** AlloMatrix(int nrl,int nrh,int ncl,int nch) {
   T**mtx=new T*[nrh-nrl+1];
   mtx-=nrl;
   for (int i=nrl;i<=nrh;i++) {
      mtx[i]=new T[nch-ncl+1];
      mtx[i]-=ncl;
   }
   return mtx;
};

/////////////////////////////////////////////////////////////////////////////
// str++.cpp