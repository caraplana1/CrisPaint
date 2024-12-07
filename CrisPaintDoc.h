
// CrisPaintDoc.h : interface of the CCrisPaintDoc class
//


#pragma once
#include <vector>
#include "CShape.h"


class CCrisPaintDoc : public CDocument
{
protected: // create from serialization only
	CCrisPaintDoc() noexcept;
	DECLARE_DYNCREATE(CCrisPaintDoc)

// Attributes
public:
	// List of shapes to draw in orden.
	std::vector<CShape*> shapes; 

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CCrisPaintDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
