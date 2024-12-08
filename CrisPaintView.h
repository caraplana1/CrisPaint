// CrisPaintView.h : interface of the CCrisPaintView class
#pragma once

class CCrisPaintView : public CView
{
protected: // create from serialization only
	CCrisPaintView() noexcept;
	DECLARE_DYNCREATE(CCrisPaintView)

// Attributes
public:
	enum Primitive_Selection
	{
		NOTHING_SELECTED,
		LINE_SELECTED,
		CIRCLE_SELECTED,
		CURVE_SELECTED,
		SQUARE_SELECTED,
		TRIANGLE_SELECTED,
		ELIPSE_SELECTED
	};

	Primitive_Selection m;
	CCrisPaintDoc* GetDocument() const;

// Operations
public:
	// =======================
	// ** Drawing functions **
	// =======================

	// Line
	void DrawLine(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);
	void EndDrawLine(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);

	// Circle
	void DrawCircle(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);
	void EndDrawCircle(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);

	// Elipse
	void DrawElipse(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);
	void EndDrawElipse(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);

	// Triangle
	void DrawTriangle(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);
	void EndDrawTriangle(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);

	// Curve
	void DrawCurve(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);
	void EndDrawCurve(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);

	// Square
	void DrawSquare(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);
	void EndDrawSquare(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CCrisPaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	// ====================
	// ** Menu selection **
	// ====================

	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCircle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCurve(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSquare(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTriangle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateElipse(CCmdUI* pCmdUI);

	afx_msg void OnLine();
	afx_msg void OnCircle();
	afx_msg void OnCurve();
	afx_msg void OnSquare();
	afx_msg void OnTriangle();
	afx_msg void OnElipse();

	// Button and mouse handling
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in CrisPaintView.cpp
inline CCrisPaintDoc* CCrisPaintView::GetDocument() const
   { return reinterpret_cast<CCrisPaintDoc*>(m_pDocument); }
#endif

