
// CrisPaintView.h : interface of the CCrisPaintView class
//

#pragma once

class CCrisPaintView : public CView
{
protected: // create from serialization only
	CCrisPaintView() noexcept;
	DECLARE_DYNCREATE(CCrisPaintView)

// Attributes
public:
	CCrisPaintDoc* GetDocument() const;
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

// Operations
public:

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
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCicle(CCmdUI* pCmdUI);
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

};

#ifndef _DEBUG  // debug version in CrisPaintView.cpp
inline CCrisPaintDoc* CCrisPaintView::GetDocument() const
   { return reinterpret_cast<CCrisPaintDoc*>(m_pDocument); }
#endif

