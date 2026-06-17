#if !defined(AFX_GRAPHERRENOVATORDIALOGPPG_H__9FF3AC6A_4612_11D5_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GRAPHERRENOVATORDIALOGPPG_H__9FF3AC6A_4612_11D5_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GrapherRenovatorDialogPpg.h : Declaration of the CGrapherRenovatorDialogPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CGrapherRenovatorDialogPropPage : See GrapherRenovatorDialogPpg.cpp.cpp for implementation.

class CGrapherRenovatorDialogPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGrapherRenovatorDialogPropPage)
	DECLARE_OLECREATE_EX(CGrapherRenovatorDialogPropPage)

// Constructor
public:
	CGrapherRenovatorDialogPropPage();

// Dialog Data
	//{{AFX_DATA(CGrapherRenovatorDialogPropPage)
	enum { IDD = IDD_PROPPAGE_GRAPHERRENOVATORDIALOG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CGrapherRenovatorDialogPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHERRENOVATORDIALOGPPG_H__9FF3AC6A_4612_11D5_9E85_0000E8C3064A__INCLUDED)
