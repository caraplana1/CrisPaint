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
		ELIPSE_SELECTED,
		SELECTION_SELECTED,
		UP_SELECTED,
		DOWN_SELECTED
	};

	Primitive_Selection m;
	bool selectColor = false;
	int shapeSelected = -1;
	CColorDialog colorDial;
	CCrisPaintDoc* GetDocument() const;
private:
	CDC doubleBuffer;

// Operations
public:
	// =======================
	// ** Drawing functions **
	// =======================

	// Line
	void BegingSetLine(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);
	void EndSetLine(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);

	// Circle
	void BegingSetCircle(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);
	void EndSetCircle(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);

	// Elipse
	void BegingSetElipse(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);
	void EndSetElipse(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);

	// Triangle
	void BegingSetTriangle(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);

	// Curve
	void BegingSetCurve(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);
	void EndSetCurve(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);

	// Square
	void BegingSetSquare(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);
	void EndSetSquare(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);

	// Selection
	int StartSelection(UINT nflags, CPoint point, CCrisPaintDoc* pDoc);

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
	afx_msg void OnUpdateSelect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateUp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDown(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColor(CCmdUI* pCmdUI);

	afx_msg void OnLine();
	afx_msg void OnCircle();
	afx_msg void OnCurve();
	afx_msg void OnSquare();
	afx_msg void OnTriangle();
	afx_msg void OnElipse();
	afx_msg void OnSelect();
	afx_msg void OnColor();

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

