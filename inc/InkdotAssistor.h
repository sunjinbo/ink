/* ====================================================================
 * File: InkdotAssistor.h
 * Created: 03/04/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_INKDOTASSISTOR_H
#define C_INKDOTASSISTOR_H

// INCLUDS
#include <e32base.h>
#include "Inkdot.hrh"

// FORWARD DECLARATIONS
class CBmpUtils;
class CFbsBitmap;
class CFbsBitmapDevice;
class CFbsBitGc;

class CInkdotAssistor : public CBase
    {
public:
    static CInkdotAssistor* NewL();
    virtual ~CInkdotAssistor();

public:
    // New methods
    CFbsBitmap* Bitmap( TInkdotType aInkdot );
    CFbsBitmap* Mask( TInt aRadius );

private:
    void ConstructL();
    CInkdotAssistor();

private: // Data
    CBmpUtils* iUtils; // Own
    CFbsBitmap* iMask; // Own
    CFbsBitmapDevice* iMaskDevice; // Own
    CFbsBitGc* iMaskContext; // Own
    TSize iMaskSize;
    };

#endif // C_INKDOTASSISTOR_H

// End of File
