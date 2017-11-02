/* ====================================================================
 * File: Title.h
 * Created: 03/26/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_TITLE_H
#define C_TITLE_H

// INCLUDS
#include <e32base.h>

// FORWARD DECLARATIONS
class CFbsBitGc;
class CBmpUtils;

class CTitle : public CBase
    {
public:
    static CTitle* NewL( CFbsBitGc*& aGc, const TRect& aRect );
    virtual ~CTitle();

public: // New functions
    void DoDraw();
    void SetEnabled( TBool aEnabled );
    TBool IsEnabled() const;
    void SetRect( const TRect& aRect );
    TRect Rect() const;

private: // Constructor
    void ConstructL( const TRect& aRect );
    CTitle( CFbsBitGc*& aGc );

private:
    // New functions
    void DoEffects();
    static TInt TimerCallback( TAny* aPtr );

private: // Data
    CFbsBitGc*& iGc; // Not own
    CBmpUtils* iUtils; // Own
    CPeriodic* iPeriodic; // Own
    TRect iRect;
    TBool iEnabled;
    TInt iBitmap;
    TBool iReverse;
    };

#endif // C_TITLE_H

// End of File
