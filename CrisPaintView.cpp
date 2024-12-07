
// CrisPaintView.cpp : implementation of the CCrisPaintView class
//

#include "pch.h"
#include "framework.h"
#include "MainFrm.h"
#include <iostream>
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CrisPaint.h"
#endif

#include "CrisPaintDoc.h"
#include "CrisPaintView.h"
#include "CTypes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCrisPaintView

IMPLEMENT_DYNCREATE(CCrisPaintView, CView)

BEGIN_MESSAGE_MAP(CCrisPaintView, CView)
	ON_WM_CONTEXTMENU()
	// Line Selection
	ON_UPDATE_COMMAND_UI(ID_LINE, &CCrisPaintView::OnUpdateLine)
	ON_COMMAND(ID_LINE, &CCrisPaintView::OnLine)

	// Circle Selection
	ON_UPDATE_COMMAND_UI(ID_CIRCLE, &CCrisPaintView::OnUpdateCicle)
	ON_COMMAND(ID_CIRCLE, &CCrisPaintView::OnCircle)

	// Curve Selection
	ON_UPDATE_COMMAND_UI(ID_CURVE, &CCrisPaintView::OnUpdateCurve)
	ON_COMMAND(ID_CURVE, &CCrisPaintView::OnCurve)
	
	// Triangle Selection
	ON_UPDATE_COMMAND_UI(ID_TRIANGLE, &CCrisPaintView::OnUpdateTriangle)
	ON_COMMAND(ID_TRIANGLE, &CCrisPaintView::OnTriangle)

	// Square Selection
	ON_UPDATE_COMMAND_UI(ID_SQUARE, &CCrisPaintView::OnUpdateSquare)
	ON_COMMAND(ID_SQUARE, &CCrisPaintView::OnSquare)

	// Elipse Selection
	ON_UPDATE_COMMAND_UI(ID_ELIPSE, &CCrisPaintView::OnUpdateElipse)
	ON_COMMAND(ID_ELIPSE, &CCrisPaintView::OnElipse)

	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CCrisPaintView construction/destruction

CCrisPaintView::CCrisPaintView() noexcept
{
	// TODO: add construction code here
	m = NOTHING_SELECTED;
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

void CCrisPaintView::OnUpdateLine(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(m == LINE_SELECTED);
}

void CCrisPaintView::OnUpdateCicle(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(m == CIRCLE_SELECTED);
}

void CCrisPaintView::OnUpdateCurve(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(m == CURVE_SELECTED);
}

void CCrisPaintView::OnUpdateSquare(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(m == SQUARE_SELECTED);
}

void CCrisPaintView::OnUpdateTriangle(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(m == TRIANGLE_SELECTED);
}

void CCrisPaintView::OnUpdateElipse(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(m == ELIPSE_SELECTED);
}

void CCrisPaintView::OnLine()
{
	m = m == LINE_SELECTED ? NOTHING_SELECTED : LINE_SELECTED;
}

void CCrisPaintView::OnCircle()
{
	m = m == CIRCLE_SELECTED ? NOTHING_SELECTED : CIRCLE_SELECTED;
}

void CCrisPaintView::OnCurve()
{
	m = m == CURVE_SELECTED ? NOTHING_SELECTED : CURVE_SELECTED;
}

void CCrisPaintView::OnSquare()
{
	m = m == SQUARE_SELECTED ? NOTHING_SELECTED : SQUARE_SELECTED;
}

void CCrisPaintView::OnTriangle()
{
	m = m == TRIANGLE_SELECTED ? NOTHING_SELECTED : TRIANGLE_SELECTED;
}

void CCrisPaintView::OnElipse()
{
	m = m == ELIPSE_SELECTED ? NOTHING_SELECTED : ELIPSE_SELECTED;
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
