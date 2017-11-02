/* ====================================================================
 * File: InkApplication.h
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_INKAPPLICATION_H
#define C_INKAPPLICATION_H

// INCLUDS
#include <aknapp.h>

class CInkApplication : public CAknApplication
    {
public:  // from CAknApplication
    TUid AppDllUid() const;

protected: // from CAknApplication
    CApaDocument* CreateDocumentL();
    };

#endif // C_INKAPPLICATION_H

// End of File
