/* ====================================================================
 * File: CanvasObserver.h
 * Created: 03/08/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

#ifndef M_CANVASOBSERVER_H
#define M_CANVASOBSERVER_H

// INCLUDES
#include <e32std.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION
class MCanvasObserver
    {
public: // New methods
    virtual void CompletedL( TInt aCount ) = 0;
    virtual void AddScoreL( TInt aScore ) = 0;
    };

#endif // M_CANVASOBSERVER_H

// End of File
