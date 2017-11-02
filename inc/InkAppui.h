/* ====================================================================
 * File: InkAppUi.h
 * Created: 01/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_INKAPPUI_H
#define C_INKAPPUI_H

// INLUCDE FILES
#include <aknappui.h>

// FORWARD DECLARATIONS
class CInkAppView;

class CInkAppUi : public CAknAppUi
    {
public:
    void ConstructL();
    CInkAppUi();
    virtual ~CInkAppUi();

public: // New methods
    void LaunchBrowserL();

public: // from CAknAppUi
    void HandleCommandL(TInt aCommand);
    void HandleResourceChangeL( TInt aType );

private: // Member data
    CInkAppView* iAppView;

    };

#endif // C_INKAPPUI_H

// End of File
