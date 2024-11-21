
// CrisPaintView.cpp : implementation of the CCrisPaintView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CrisPaint.h"
#endif

#include "CrisPaintDoc.h"
#include "CrisPaintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCrisPaintView

IMPLEMENT_DYNCREATE(CCrisPaintView, CView)

BEGIN_MESSAGE_MAP(CCrisPaintView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CCrisPaintView construction/destruction

CCrisPaintView::CCrisPaintView() noexcept
{
	// TODO: add construction code here

}

CCrisPaintView::~CCrisPaintView()
{
}

BOOL CCrisPaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCrisPaintView drawing

void CCrisPaintView::OnDraw(CDC* /*pDC*/)
{
	CCrisPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CCrisPaintView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCrisPaintView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCrisPaintView diagnostics

#ifdef _DEBUG
void CCrisPaintView::AssertValid() const
{
	CView::AssertValid();
}

void CCrisPaintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCrisPaintDoc* CCrisPaintView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCrisPaintDoc)));
	return (CCrisPaintDoc*)m_pDocument;
}
#endif //_DEBUG


// CCrisPaintView message handlers
