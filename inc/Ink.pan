/* ====================================================================
 * File: Ink.pan
 * Created: 03/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef INK_PAN
#define INK_PAN

#include <e32std.h>

/** Ink application panic codes */
enum TInkPanics 
    {
    EInkBadCommands = 1,
    EInkBadRadius, // 2
    EInkBadInkdotType, // 3
    EInkBadEyeFrame, // 4
    EInkInvlidIndex, // 5
    EInkLackConfiguration // 6
    // add further panics here
    };

inline void Panic( TInkPanics aReason )
    {
    _LIT( applicationName,"Ink" );
    User::Panic( applicationName, aReason );
    }

#endif // INK_PAN

// End of File
