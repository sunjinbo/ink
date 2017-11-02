/* ====================================================================
 * File: InkDocument.cpp
 * Created: 03/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDS
#include "InkAppUi.h"
#include "InkDocument.h"

// CONSTANS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CInkDocument::NewL
// Standard Symbian OS construction sequence
// ----------------------------------------------------------------------------
//
CInkDocument* CInkDocument::NewL(CEikApplication& aApp)
    {
    CInkDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CInkDocument::NewLC
// Standard Symbian OS construction sequence
// ----------------------------------------------------------------------------
//
CInkDocument* CInkDocument::NewLC(CEikApplication& aApp)
    {
    CInkDocument* self = new (ELeave) CInkDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------------------------
// CInkDocument::ConstructL
// ----------------------------------------------------------------------------
//
void CInkDocument::ConstructL()
    {
    // no implementation required
    }    

// ----------------------------------------------------------------------------
// CInkDocument::CInkDocument
// ----------------------------------------------------------------------------
//
CInkDocument::CInkDocument(CEikApplication& aApp) 
    : CAknDocument(aApp) 
    {
    // no implementation required
    }

// ----------------------------------------------------------------------------
// CInkDocument::~CInkDocument
// ----------------------------------------------------------------------------
//
CInkDocument::~CInkDocument()
    {
    // no implementation required
    }

// ----------------------------------------------------------------------------
// CInkDocument::CreateAppUiL
// ----------------------------------------------------------------------------
//
CEikAppUi* CInkDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it,
    // the framework takes ownership of this object
    CEikAppUi* appUi = new (ELeave) CInkAppUi;
    return appUi;
    }

// End of File
