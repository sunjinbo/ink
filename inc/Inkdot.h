/* ====================================================================
 * File: Inkdot.h
 * Created: 03/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_INKDOT_H
#define C_INKDOT_H

// INCLUDS
#include <coecntrl.h>
#include "InkdotData.h"

// FORWARD DECLARATIONS
class CCanvas;

class CInkdot : public CTimer
    {
public:
    static CInkdot* NewL( CCanvas& aCanvas, const TInkdotData& aInkdotData );
    virtual ~CInkdot();

public: // New methods
    void DoDraw();
    void SetVector( TInt aVectorX, TInt aVectorY );
    TBool IsSplash() const;
    TBool Intersects( const CInkdot& aInkdot ) const;
    void SetScore( TInt aScore );
    TInt Score() const;
    void Reverse();

public: // From CTimer
    void RunL();

private:
    void ConstructL();
    CInkdot( CCanvas& aCanvas, const TInkdotData& aInkdotData );

private: // New methods
    void InitVector();
    void DoMove();
    void DoSplash();
    void DoExpire();
    static TInt TimerCallback( TAny* aPtr );
    static TInt ExpireCallback( TAny* aPtr );
    TInt Rand( TInt aRange ) const;
    TRect ClientRect() const;
    void HitTest();
    void Stop();

private: // Data
    CCanvas& iCanvas;
    CPeriodic* iPeriodic; // Own
    TInkdotData iData;
    TInt iVectorX;
    TInt iVectorY;
    TInt iScore;
    };

#endif // C_INKDOT_H

// End of File
