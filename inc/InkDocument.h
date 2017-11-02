/* ====================================================================
 * File: InkDocument.h
 * Created: 03/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_INCDOCUMENT_H
#define C_INCDOCUMENT_H

// INCLUDS
#include <akndoc.h>

// FORWARD DECLARATIONS
class CInkAppUi;
class CEikApplication;

class CInkDocument : public CAknDocument
    {
public:
    static CInkDocument* NewL(CEikApplication& aApp);
    static CInkDocument* NewLC(CEikApplication& aApp);
    virtual ~CInkDocument();

public: // from CAknDocument
    CEikAppUi* CreateAppUiL();

private:
    void ConstructL();
    CInkDocument(CEikApplication& aApp);

    };

#endif // C_INCDOCUMENT_H

// End of File
