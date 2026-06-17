// XYZListBox.cpp : implementation file
//

#include "stdafx.h"
#include "grapher.h"
#include "XYZListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXYZListBox

/*
 NO X1 Y1 Z0 ????????????????????????????
 .. .. .. ..
 .. .. .. ..
 .. .. .. ..
*/

CXYZListBox::CXYZListBox()
{
}

CXYZListBox::~CXYZListBox()
{
}


BEGIN_MESSAGE_MAP(CXYZListBox, CListBox)
	//{{AFX_MSG_MAP(CXYZListBox)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXYZListBox message handlers

int CXYZListBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	
	return 0;
}
