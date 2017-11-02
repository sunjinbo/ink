/* ====================================================================
 * File: InkApplication.cpp
 * Created: 03/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDS
#include "InkDocument.h"
#include "InkApplication.h"

// CONSTANS
// UID for the application, this should correspond to the uid defined in the mmp file
static const TUid KUidInkApp = { 0xAFF05678 };

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CInkApplication::CreateDocumentL
// Create an Ink document, and return a pointer to it
// ----------------------------------------------------------------------------
//
CApaDocument* CInkApplication::CreateDocumentL()
    {  
    CApaDocument* document = CInkDocument::NewL(*this);
    return document;
    }

// ----------------------------------------------------------------------------
// CInkApplication::AppDllUid
// ----------------------------------------------------------------------------
//
TUid CInkApplication::AppDllUid() const
    {
    // Return the UID for the Ink application
    return KUidInkApp;
    }

// End of File
