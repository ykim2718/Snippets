#if !defined(AFX_GRAPHERPALLETEDIALOGPPG_H__0F24C35B_4552_11D5_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GRAPHERPALLETEDIALOGPPG_H__0F24C35B_4552_11D5_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GrapherPalleteDialogPpg.h : Declaration of the CGrapherPalleteDialogPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CGrapherPalleteDialogPropPage : See GrapherPalleteDialogPpg.cpp.cpp for implementation.

class CGrapherPalleteDialogPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGrapherPalleteDialogPropPage)
	DECLARE_OLECREATE_EX(CGrapherPalleteDialogPropPage)

// Constructor
public:
	CGrapherPalleteDialogPropPage();

// Dialog Data
	//{{AFX_DATA(CGrapherPalleteDialogPropPage)
	enum { IDD = IDD_PROPPAGE_GRAPHERPALLETEDIALOG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CGrapherPalleteDialogPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHERPALLETEDIALOGPPG_H__0F24C35B_4552_11D5_9E85_0000E8C3064A__INCLUDED)
