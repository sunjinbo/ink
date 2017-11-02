/* ====================================================================
 * File: ButtonObserver.h
 * Created: 03/06/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

#ifndef M_BUTTONOBSERVER_H
#define M_BUTTONOBSERVER_H

// INCLUDES
#include <e32std.h>

// FORWARD DECLARATIONS
class CMenuButton;

// CLASS DECLARATION
class MButtonObserver
    {
public: // New methods
    virtual void HandleClickedL( const CMenuButton& aBtn ) = 0;
    };

#endif // M_BUTTONOBSERVER_H

// End of File
