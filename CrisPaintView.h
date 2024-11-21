
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
};

#ifndef _DEBUG  // debug version in CrisPaintView.cpp
inline CCrisPaintDoc* CCrisPaintView::GetDocument() const
   { return reinterpret_cast<CCrisPaintDoc*>(m_pDocument); }
#endif

