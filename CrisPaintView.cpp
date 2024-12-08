
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
#include "CShape.h"
#include "CLine.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CCurve.h"
#include "CElipse.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ===========================================
// ** Use to set multiple vertex of a shape ** 
// ===========================================
int CURRENT_TRIANGLE_VERTEX; 

// CCrisPaintView

IMPLEMENT_DYNCREATE(CCrisPaintView, CView)

BEGIN_MESSAGE_MAP(CCrisPaintView, CView)
	// Button and mouse
	ON_WM_CONTEXTMENU()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()

	// Line Selection
	ON_UPDATE_COMMAND_UI(ID_LINE, &CCrisPaintView::OnUpdateLine)
	ON_COMMAND(ID_LINE, &CCrisPaintView::OnLine)

	// Circle Selection
	ON_UPDATE_COMMAND_UI(ID_CIRCLE, &CCrisPaintView::OnUpdateCircle)
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

	// Selection Selection
	ON_UPDATE_COMMAND_UI(ID_ELIPSE, &CCrisPaintView::OnUpdateSelect)
	ON_COMMAND(ID_ELIPSE, &CCrisPaintView::OnSelect)
END_MESSAGE_MAP()

// CCrisPaintView construction/destruction

CCrisPaintView::CCrisPaintView() noexcept
{
	// TODO: add construction code here
	m = NOTHING_SELECTED;
	CURRENT_TRIANGLE_VERTEX = 0;
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

void CCrisPaintView::OnDraw(CDC* pDC)
{
	CCrisPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CShape* aux;
	int lastPos = pDoc->shapes.size() - 1;

	for (int i = 0; i <= lastPos; i++)
	{
		aux = pDoc->shapes[i];
		if (aux->IsReady() || (!aux->IsReady() && i == lastPos))
			aux->render(pDC);
	}

}

void CCrisPaintView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
	CView::OnRButtonUp(nFlags, point);
}

void CCrisPaintView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CCrisPaintDoc* pdoc = GetDocument();
	ASSERT_VALID(pdoc);
	if (!pdoc)
		return;

	if (pdoc->shapes.size() == 0)
		return;

	switch (m)
	{
	case CCrisPaintView::NOTHING_SELECTED:
		break;
	case CCrisPaintView::LINE_SELECTED:
		EndDrawLine(nFlags, point, pdoc);
		break;
	case CCrisPaintView::CIRCLE_SELECTED:
		EndDrawCircle(nFlags, point, pdoc);
		break;
	case CCrisPaintView::CURVE_SELECTED:
		EndDrawCurve(nFlags, point, pdoc);
		break;
	case CCrisPaintView::SQUARE_SELECTED:
		EndDrawSquare(nFlags, point, pdoc);
		break;
	case CCrisPaintView::TRIANGLE_SELECTED:
		EndDrawTriangle(nFlags, point, pdoc);
		break;
	case CCrisPaintView::ELIPSE_SELECTED:
		EndDrawElipse(nFlags, point, pdoc);
		break;
	}

	ClientToScreen(&point);
	CView::OnLButtonUp(nFlags, point);
}

void CCrisPaintView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CCrisPaintDoc* pdoc = GetDocument();
	ASSERT_VALID(pdoc);
	if (!pdoc)
		return;

	if (m != TRIANGLE_SELECTED)
		CURRENT_TRIANGLE_VERTEX = 0;

	switch (m)
	{
	case CCrisPaintView::NOTHING_SELECTED:
		break;
	case CCrisPaintView::LINE_SELECTED:
		DrawLine(nFlags, point, pdoc);
		break;
	case CCrisPaintView::CIRCLE_SELECTED:
		DrawCircle(nFlags, point, pdoc);
		break;
	case CCrisPaintView::CURVE_SELECTED:
		DrawCurve(nFlags, point, pdoc);
		break;
	case CCrisPaintView::SQUARE_SELECTED:
		DrawSquare(nFlags, point, pdoc);
		break;
	case CCrisPaintView::TRIANGLE_SELECTED:
		DrawTriangle(nFlags, point, pdoc);
		break;
	case CCrisPaintView::ELIPSE_SELECTED:
		DrawElipse(nFlags, point, pdoc);
		break;
	}

	ClientToScreen(&point);
	CView::OnLButtonDown(nFlags, point);
}

void CCrisPaintView::OnMouseMove(UINT nFlags, CPoint point)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CString s;
	s.Format(L"%d, %d", point.x, point.y);
	pMainFrame->setStatusBar(s);

	CView::OnMouseMove(nFlags, point);
}

void CCrisPaintView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// Gets the points to draw the primitives
#pragma region Primitives setting
	// Drawing Line
	void CCrisPaintView::DrawLine(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
		pDoc->shapes.push_back((CShape*)(new CLine(point.x, point.y, point.x, point.y)));
	}

	void CCrisPaintView::EndDrawLine(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
		int pos = pDoc->shapes.size() - 1;
		CLine* line = (CLine*)pDoc->shapes[pos];
		line->setEnd(point.x, point.y);
		Invalidate(1);
	}

	// Drawing Circle
	void CCrisPaintView::DrawCircle(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
	}

	void CCrisPaintView::EndDrawCircle(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
	}

	// Drawing Elipse
	void CCrisPaintView::DrawElipse(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
	}

	void CCrisPaintView::EndDrawElipse(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
	}

	// Drawing Triangle
	void CCrisPaintView::DrawTriangle(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
		if (CURRENT_TRIANGLE_VERTEX == 0)
		{
			pDoc->shapes.push_back((CShape*) new CTriangle(point.x, point.y, point.x, point.y, point.x, point.y));
			CURRENT_TRIANGLE_VERTEX++;
		}
		else if (CURRENT_TRIANGLE_VERTEX == 1)
		{
			int pos = pDoc->shapes.size() - 1;
			CTriangle* tri = (CTriangle*)pDoc->shapes[pos];
			tri->setSecond(point.x, point.y);
			CURRENT_TRIANGLE_VERTEX++;
			Invalidate(1);
		}
		else if (CURRENT_TRIANGLE_VERTEX == 2)
		{
			int pos = pDoc->shapes.size() - 1;
			CTriangle* tri = (CTriangle*)pDoc->shapes[pos];
			tri->setThird(point.x, point.y);
			CURRENT_TRIANGLE_VERTEX = 0;
			Invalidate(1);
		}
	}

	void CCrisPaintView::EndDrawTriangle(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
	}

	// Drawing Curve
	void CCrisPaintView::DrawCurve(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
	}

	void CCrisPaintView::EndDrawCurve(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
	}

	// Drawing square
	void CCrisPaintView::DrawSquare(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
		pDoc->shapes.push_back((CShape*)new CRectangle(point.x, point.y, point.x, point.y));
	}

	void CCrisPaintView::EndDrawSquare(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
		int pos = pDoc->shapes.size() - 1;
		CRectangle* square = (CRectangle*)pDoc->shapes[pos];
		square->setEndPoint(point.x, point.y);
		Invalidate(1);
	}

#pragma endregion

// Select what primitive you want to draw
#pragma region Primitives Selection Menu

	// Line
	void CCrisPaintView::OnUpdateLine(CCmdUI* pCmdUI)
	{
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(m == LINE_SELECTED);
	}

	void CCrisPaintView::OnLine()
	{
		m = m == LINE_SELECTED ? NOTHING_SELECTED : LINE_SELECTED;
	}

	// Circle
	void CCrisPaintView::OnUpdateCircle(CCmdUI* pCmdUI)
	{
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(m == CIRCLE_SELECTED);
	}

	void CCrisPaintView::OnCircle()
	{
		m = m == CIRCLE_SELECTED ? NOTHING_SELECTED : CIRCLE_SELECTED;
	}

	// Curve
	void CCrisPaintView::OnUpdateCurve(CCmdUI* pCmdUI)
	{
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(m == CURVE_SELECTED);
	}

	void CCrisPaintView::OnCurve()
	{
		m = m == CURVE_SELECTED ? NOTHING_SELECTED : CURVE_SELECTED;
	}

	// Square
	void CCrisPaintView::OnUpdateSquare(CCmdUI* pCmdUI)
	{
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(m == SQUARE_SELECTED);
	}

	void CCrisPaintView::OnSquare()
	{
		m = m == SQUARE_SELECTED ? NOTHING_SELECTED : SQUARE_SELECTED;
	}

	// Triangle
	void CCrisPaintView::OnUpdateTriangle(CCmdUI* pCmdUI)
	{
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(m == TRIANGLE_SELECTED);
	}

	void CCrisPaintView::OnTriangle()
	{
		m = m == TRIANGLE_SELECTED ? NOTHING_SELECTED : TRIANGLE_SELECTED;
	}

	// Elipse
	void CCrisPaintView::OnUpdateElipse(CCmdUI* pCmdUI)
	{
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(m == ELIPSE_SELECTED);
	}

	void CCrisPaintView::OnUpdateSelect(CCmdUI* pCmdUI)
	{
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(m == SELECTION_SELECTED); 
	} 

	void CCrisPaintView::OnUpdateUp(CCmdUI* pCmdUI)
	{
		if (SELECTION_SELECTED != m)
			return;
	}

	void CCrisPaintView::OnUpdateDown(CCmdUI* pCmdUI)
	{
		if (SELECTION_SELECTED != m)
			return;
	}

	void CCrisPaintView::OnElipse()
	{
		m = m == ELIPSE_SELECTED ? NOTHING_SELECTED : ELIPSE_SELECTED;
	}

	void CCrisPaintView::OnSelect()
	{
		m = m == ELIPSE_SELECTED ? NOTHING_SELECTED : SELECTION_SELECTED;
	}
#pragma endregion

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
