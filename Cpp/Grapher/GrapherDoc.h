// GrapherDoc.h : interface of the CGrapherDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GrapherDOC_H__236879AD_E21F_11D4_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GrapherDOC_H__236879AD_E21F_11D4_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGrapherDoc : public CDocument
{
protected: // create from serialization only
	CGrapherDoc();
	DECLARE_DYNCREATE(CGrapherDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrapherDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGrapherDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGrapherDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GrapherDOC_H__236879AD_E21F_11D4_9E85_0000E8C3064A__INCLUDED_)
