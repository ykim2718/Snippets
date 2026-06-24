#if !defined(__STR_H__)
#define __STR_H__
////////////////////////////////////////////////////////////////////////////////

#define _T(a) (a)

////////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <string.h>
#include "str.h"

typedef const char *LPCSTR;
typedef LPCSTR LPCTSTR;

class CStringEx
{
public:
	// constructors and destructor
	CStringEx(const CStringEx& str);
	CStringEx(const char* str);
	CStringEx()	{ m_nLength=0; m_pData=0; }
	virtual ~CStringEx()	{ if (m_pData) delete m_pData; }

   // shik96@samsung.co.kr
   // get data length
   int GetLength() const;
   // TRUE if zero length
   int IsEmpty() const;
	// clear contents to empty
   void Empty();

   // find character starting at left, -1 if not found
   int Find(const char chr) const;
   // find character starting at right
   int ReverseFind(char chr) const;
   // find character starting at zero-based index and going right
   int Find(const char chr,int nStart) const;
   // find first instance of any character in passed string
   int FindOneOf(const char *sChars) const;
   // find first instance of substring
   int Find(const char *str) const;
   // find first instance of substring starting at zero-based index
   int Find(const char *str,int nStart) const;
   
   // return nCount characters starting at zero-based nFirst
   CStringEx Mid( int nFirst, int nCount ) const;
   // return all characters starting at zero-based nFirst
   CStringEx Mid( int nFirst ) const;
	// return first nCount characters in string
   CStringEx Left(int nCount) const;
	// return nCount characters from end of string
   CStringEx Right(int nCount) const;

   // Y.Kim,20030209) Remove whitespace from both left and right ends
   void Trim() { TrimLeft();TrimRight(); } 
   // remove whitespace starting from right edge
   void TrimRight();
	// remove whitespace starting from left side
	void TrimLeft();
   // remove continuous occcurrences of characters in
	// passed string, starting from left
   void TrimLeft(LPCTSTR str); //? Y.Kim
   // return single character at zero-based index
   char GetAt(int nIndex) const;
   // set a single character at zero-based index
   void SetAt(int nIndex, char chr);

   // replace occurrences of chOld with chNew
	int Replace(char chOld,char chNew);
      //Return Value:The number of replaced instances of the character. Zero if the string isn't changed.
	// replace occurrences of substring lpszOld with lpszNew;
	// empty lpszNew removes instances of lpszOld
   int Replace(const char *sOld,const char *sNew);
	// remove occurrences of chRemove
	int Remove(char chRemove);
	// insert character at zero-based index; concatenates
	// if index is past end of string
	int Insert(int nIndex,char chr);
	// insert substring at zero-based index; concatenates
	// if index is past end of string
	int Insert(int nIndex,const char *str);
	// delete nCount characters starting at zero-based index
	int Delete(int nIndex,int nCount=1);
   // Y.Kim,20030209) Add string at the end.
   int Add(const char *qAdd);
   // Y.Kim,20030209) Add string tranformed from an integer at the end.
   int AddInteger(int nAdd,int nBase);
   // Y.Kim,20030209) Add string tranformed from a double at the end.
   int AddDouble(double dAdd,const char *qFormat);

   // straight character comparison
   int Compare(const char *str) const;
   int Compare(const char *str,unsigned int count) const;
	// compare ignoring case
	int CompareNoCase(LPCTSTR lpsz) const;

   // :)

	// operator overloading helper
	template <class T> friend CStringEx _cdecl operator +(T var, const CStringEx& str);

	// operator overloading
	CStringEx& operator =(const char* str);
	CStringEx& operator =(const CStringEx& str);
	template <class T>
	CStringEx  operator +(T var) { CStringEx tstr = *this; return tstr += var; }
	CStringEx& operator +=(const char* str)	{ return *this += (CStringEx)str; }
	CStringEx& operator +=(const CStringEx& str);


	// add more logic comparison operators as following, for example, although not efficient
	virtual bool operator !=(char* str)	{ return strcmp(str, m_pData) != 0; }

	// c type string conversion
	operator char* ()					{ return m_pData; }
	operator const char* ()	const		{ return m_pData; }
	char* GetChar()						{ return m_pData; }

	// numeric conversion
	template <class T> GetValue(T& var)	{ return GetVar(var); }

	// search the match string : WildCards can be '?' and '*' combination
	// return value : true (pattern matchs string), false (no match)
	bool Search(const char* WildCards)	{ return Match((char*)WildCards, m_pData); }

	// format string
	int Format(const char* format, ...);

protected:
	// can use faster algorithm for search ?
	virtual bool Match(char*, char*);
	virtual bool Scan(char*&, char*&);

	// data block
	int   m_nLength;
	char* m_pData;
};

bool operator==(const CStringEx& s1, const CStringEx& s2);
bool operator==(const CStringEx& s1, const char* s2);
bool operator==(const char* s1, const CStringEx& s2);
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

template <class T>
CStringEx operator +(T var, const CStringEx& str) 
{ 
	CStringEx svar = var;
	return svar += str; 
}

////////////////////////////////////////////////////////////////////////////////

class CTokenEx
{
public:
	CTokenEx( CStringEx string,const char *delimiter=" \t\n\f\r" );
   CTokenEx( const char *string,const char *delimiter=" \t\n\f\r" );
	CTokenEx();
   ~CTokenEx();
   void operator=(const CStringEx& string) {
      m_sTarget=string;
   }
   void operator=(const char* string) {
      m_sTarget=string;
   }
   void SetDelimiter( const CStringEx &delimiter ) {
      m_sDelimiter=delimiter;
   }
   void GetDelimiter( CStringEx &delimiter ) {
      delimiter=m_sDelimiter;
   }
   int IsNext();
   CStringEx GetNextToken();
	int GetNextTokenCount();
	CStringEx GetTokenByIndex( unsigned int nIndex );
   CStringEx GetTokenValueOfEq( const CStringEx& sTarget );

private:
	CStringEx m_sTarget;
   CStringEx m_sDelimiter;
};

////////////////////////////////////////////////////////////////////////////////
#endif // End of String++.h