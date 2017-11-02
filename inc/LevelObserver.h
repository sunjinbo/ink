/* ====================================================================
 * File: LevelObserver.h
 * Created: 03/08/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

#ifndef M_LEVELOBSERVER_H
#define M_LEVELOBSERVER_H

// INCLUDES
#include <e32std.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION
class MLevelObserver
    {
public: // New methods
    virtual void GameOverL() = 0;
    };

#endif // M_LEVELOBSERVER_H

// End of File
