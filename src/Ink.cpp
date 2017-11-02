/* ====================================================================
 * File: Ink.cpp
 * Created: 03/16/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDS
#include "InkApplication.h"
#include <eikstart.h>

// Create an application, and return a pointer to it
CApaApplication* NewApplication()
    {
    return new CInkApplication;
    }

TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }
    
// End of File
