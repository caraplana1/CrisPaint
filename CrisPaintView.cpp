
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
	ON_WM_ERASEBKGND()
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
	ON_UPDATE_COMMAND_UI(ID_SELECT, &CCrisPaintView::OnUpdateSelect)
	ON_COMMAND(ID_SELECT, &CCrisPaintView::OnSelect)

	// Select a color
	ON_UPDATE_COMMAND_UI(ID_COLOR, &CCrisPaintView::OnUpdateColor)
	ON_COMMAND(ID_COLOR, &CCrisPaintView::OnColor)

	// Select a background color
	ON_UPDATE_COMMAND_UI(ID_BACKGROUND_COLOR, &CCrisPaintView::OnUpdateBackgroundColor)
	ON_COMMAND(ID_BACKGROUND_COLOR, &CCrisPaintView::OnBackgroundColor)
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

	// Create an auxiliar ccshape object for render.
	CShape* aux;
	int lastPos = pDoc->shapes.size() - 1;

	for (int i = 0; i <= lastPos; i++)
	{
		aux = pDoc->shapes[i];
		if (aux->IsReady() || (!aux->IsReady() && i == lastPos))
			aux->render(pDC); // Render in the second buffer.
	}

	CRect rect;
	GetClientRect(&rect);

	// pDC->BitBlt(rect.TopLeft().x, rect.TopLeft().y, rect.BottomRight().x, rect.BottomRight().y, doubleBuffer, 0, 0, SRCCOPY);
	pDC->SetBkColor(backgroundColor->getColor());
	
}

#pragma region Device Input 

	// Right mouse button up.
	void CCrisPaintView::OnRButtonUp(UINT nFlags, CPoint point)
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
		CView::OnRButtonUp(nFlags, point);
	}

	// Left mouse button up.
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
			EndSetLine(nFlags, point, pdoc);
			break;
		case CCrisPaintView::CIRCLE_SELECTED:
			EndSetCircle(nFlags, point, pdoc);
			break;
		case CCrisPaintView::CURVE_SELECTED:
			EndSetCurve(nFlags, point, pdoc);
			break;
		case CCrisPaintView::SQUARE_SELECTED:
			EndSetSquare(nFlags, point, pdoc);
			break;
		case CCrisPaintView::ELIPSE_SELECTED:
			EndSetElipse(nFlags, point, pdoc);
			break;
		}

		ClientToScreen(&point);
		CView::OnLButtonUp(nFlags, point);
	}

	// Left mouse button down.
	void CCrisPaintView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		CCrisPaintDoc* pdoc = GetDocument();
		ASSERT_VALID(pdoc);
		if (!pdoc)
			return;

		if (m != SELECTION_SELECTED)
			shapeSelected = -1;

		if (m != TRIANGLE_SELECTED)
			CURRENT_TRIANGLE_VERTEX = 0;

		switch (m)
		{
		case CCrisPaintView::NOTHING_SELECTED:
			break;
		case CCrisPaintView::LINE_SELECTED:
			BegingSetLine(nFlags, point, pdoc);
			break;
		case CCrisPaintView::CIRCLE_SELECTED:
			BegingSetCircle(nFlags, point, pdoc);
			break;
		case CCrisPaintView::CURVE_SELECTED:
			BegingSetCurve(nFlags, point, pdoc);
			break;
		case CCrisPaintView::SQUARE_SELECTED:
			BegingSetSquare(nFlags, point, pdoc);
			break;
		case CCrisPaintView::TRIANGLE_SELECTED:
			BegingSetTriangle(nFlags, point, pdoc);
			break;
		case CCrisPaintView::ELIPSE_SELECTED:
			BegingSetElipse(nFlags, point, pdoc);
			break;
		case CCrisPaintView::SELECTION_SELECTED:
			shapeSelected = StartSelection(nFlags, point, pdoc);
			m = NOTHING_SELECTED;
			break;
		}

		ClientToScreen(&point);
		CView::OnLButtonDown(nFlags, point);
	}

	// Mouse movement
	void CCrisPaintView::OnMouseMove(UINT nFlags, CPoint point)
	{
		CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
		CString s;
		s.Format(L"%d, %d", point.x, point.y);
		pMainFrame->setStatusBar(s);

		CView::OnMouseMove(nFlags, point);
	}

#pragma endregion

void CCrisPaintView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// Gets the points for the primitives
#pragma region Primitives setting
	// Drawing Line
	void CCrisPaintView::BegingSetLine(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
		CLine* lineAux = new CLine(point.x, point.y, point.x, point.y);
		lineAux->SetColor(shapeCurrentColor->getColor());
		pDoc->shapes.push_back((CShape*) lineAux);
	}

	void CCrisPaintView::EndSetLine(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
		int pos = pDoc->shapes.size() - 1;
		CLine* line = (CLine*)pDoc->shapes[pos];
		line->setEnd(point.x, point.y);
		Invalidate(1);
	}

	// Drawing Circle
	void CCrisPaintView::BegingSetCircle(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
		CCircle* circleAux = new CCircle(point.x, point.y, point.x, point.y);
		circleAux->SetColor(shapeCurrentColor->getColor());
		pDoc->shapes.push_back((CShape*) circleAux);
	}

	void CCrisPaintView::EndSetCircle(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
		int pos = pDoc->shapes.size() - 1;
		CCircle* circle = (CCircle*)pDoc->shapes[pos];
		circle->setPointOne(point.x, point.y);
		Invalidate(1);
	}

	// Drawing Elipse
	void CCrisPaintView::BegingSetElipse(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
		CElipse* aux = new CElipse(point.x, point.y, point.x, point.y);
		aux->SetColor(shapeCurrentColor->getColor());
		pDoc->shapes.push_back((CShape*) aux);
	}

	void CCrisPaintView::EndSetElipse(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
		int pos = pDoc->shapes.size() - 1;
		CElipse* elipse = (CElipse*)pDoc->shapes[pos];
		elipse->setSecond(point.x, point.y);
		Invalidate(1);
	}

	// Drawing Triangle
	void CCrisPaintView::BegingSetTriangle(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
		if (CURRENT_TRIANGLE_VERTEX == 0)
		{
			CTriangle* triAux = new CTriangle(point.x, point.y, point.x, point.y, point.x, point.y);
			triAux->SetColor(shapeCurrentColor->getColor());
			pDoc->shapes.push_back((CShape*) triAux);
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

	// Drawing Curve
	void CCrisPaintView::BegingSetCurve(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
	}

	void CCrisPaintView::EndSetCurve(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
	}

	// Drawing square
	void CCrisPaintView::BegingSetSquare(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
		CRectangle* rect =new CRectangle(point.x, point.y, point.x, point.y);
		rect->SetColor(shapeCurrentColor->getColor());
		pDoc->shapes.push_back((CShape*)rect);
	}

	void CCrisPaintView::EndSetSquare(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
		int pos = pDoc->shapes.size() - 1;
		CRectangle* square = (CRectangle*)pDoc->shapes[pos];
		square->setEndPoint(point.x, point.y);
		Invalidate(1);
	}

	int CCrisPaintView::StartSelection(UINT nflags, CPoint point, CCrisPaintDoc* pDoc)
	{
		std::vector<CShape*> shapes = pDoc->shapes;

		for (int i = shapes.size() - 1; i >= 0; i--)
		{
			if (shapes[i]->IsInside(point.x, point.y))
				return i;
		}

		return -1;
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

	void CCrisPaintView::OnUpdateColor(CCmdUI* pCmdUI)
	{
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(selectColor);
	}

	void CCrisPaintView::OnUpdateBackgroundColor(CCmdUI* pCmdUI)
	{
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(changingBackgroundColorActive);
	}

	void CCrisPaintView::OnElipse()
	{
		m = m == ELIPSE_SELECTED ? NOTHING_SELECTED : ELIPSE_SELECTED;
	}

	void CCrisPaintView::OnSelect()
	{
		m = m == SELECTION_SELECTED ? NOTHING_SELECTED : SELECTION_SELECTED;
	}

	void CCrisPaintView::OnColor()
	{
		selectColor = true;

		if (colorDial.DoModal() == IDOK)
			shapeCurrentColor = new CRGB(colorDial.GetColor());

		selectColor = false;

	}

	void CCrisPaintView::OnBackgroundColor()
	{
		changingBackgroundColorActive = true;

		if (colorDial.DoModal() == IDOK)
			backgroundColor = new CRGB(colorDial.GetColor());
	
		changingBackgroundColorActive = false;
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
