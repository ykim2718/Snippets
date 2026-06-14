#if !defined(AFX_GARGAMELPATTERNFORMATRIXPPG_H__DA81C259_1207_4B5F_9887_BBAD3D45C64E__INCLUDED_)
#define AFX_GARGAMELPATTERNFORMATRIXPPG_H__DA81C259_1207_4B5F_9887_BBAD3D45C64E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GargamelPatternForMatrixPpg.h : Declaration of the CGargamelPatternForMatrixPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixPropPage : See GargamelPatternForMatrixPpg.cpp.cpp for implementation.

class CGargamelPatternForMatrixPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGargamelPatternForMatrixPropPage)
	DECLARE_OLECREATE_EX(CGargamelPatternForMatrixPropPage)

// Constructor
public:
	CGargamelPatternForMatrixPropPage();

// Dialog Data
	//{{AFX_DATA(CGargamelPatternForMatrixPropPage)
	enum { IDD = IDD_PROPPAGE_GARGAMELPATTERNFORMATRIX };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CGargamelPatternForMatrixPropPage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GARGAMELPATTERNFORMATRIXPPG_H__DA81C259_1207_4B5F_9887_BBAD3D45C64E__INCLUDED)
