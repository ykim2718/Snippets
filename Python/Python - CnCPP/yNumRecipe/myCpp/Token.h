#if !defined(STRCPP_HEADER_INSTALLED)
#define STRCPP_HEADER_INSTALLED

/////////////////////////////////////////////////////////////////////////////
// shik96

class CToken
{
public:
	CToken( CString string,const char *delimiter=" \t\n\f\r" );
   CToken( const char *string,const char *delimiter=" \t\n\f\r" );
	CToken();
   ~CToken();
   void operator=(const CString& string) {
      m_sTarget=string;
   }
   void operator=(const char* string) {
      m_sTarget=string;
   }
   operator LPCTSTR() const
	{ return (LPCTSTR)m_sTarget; }

   void SetDelimiter( const CString &delimiter ) {
      m_sDelimiter=delimiter;
   }
   void GetDelimiter( CString &delimiter ) {
      delimiter=m_sDelimiter;
   }
   BOOL IsNext();
   CString GetNextToken();
	int GetNextTokenCount();
	CString GetTokenByIndex( unsigned int nIndex );
   CString GetTokenValueOfEq( const CString& sTarget );

private:
	CString m_sTarget;
   CString m_sDelimiter;
};

/////////////////////////////////////////////////////////////////////////////

template <class T,int nrl,int nrh,int ncl,int nch>
T** AlloMatrix(int nrl,int nrh,int ncl,int nch);

/////////////////////////////////////////////////////////////////////////////
#endif
