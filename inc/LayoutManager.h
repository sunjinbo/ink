/* ====================================================================
 * File: LayoutManager.h
 * Created: 03/06/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_LAYOUTMANAGER_H
#define C_LAYOUTMANAGER_H

// INCLUDE FILES
#include <e32base.h>
#include "LayoutValues.h"

// FORWARD DECLARATIONS
class TAknLayoutRect;

// CLASS DECLARATION
/**
* CLayoutManager class
*
* @since S60 5.0
*/
class CLayoutManager : public CBase
    {
public: // Constructor and Destructor
    static CLayoutManager* NewL();
    virtual ~CLayoutManager();    

public: // New functions
    void ResolutionChanged( TOrientation aOrientation = EAutomatic );
    void LayoutRect( TComponent aComponent, TRect& rect ) const;

private: // Constructor
    CLayoutManager();
    void ConstructL();

private: // Data members
    TResolution iResolution;
    };

#endif // C_LAYOUTMANAGER_H

// End of File
