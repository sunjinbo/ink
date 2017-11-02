/* ====================================================================
 * File: Canvas.h
 * Created: 03/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_CANVAS_H
#define C_CANVAS_H

// INCLUDS
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CFbsBitGc;
class CInkdotAssistor;
class CInkdot;
class MCanvasObserver;
class CBmpUtils;
class CInkdotFactory;

class CCanvas : public CCoeControl
    {
public: // Symbian constructor and destructor
    static CCanvas* NewL( 
        MCanvasObserver& aObserver, 
        CFbsBitGc*& aGc, 
        const TRect& aRect 
        );
    virtual ~CCanvas();

public: // New methods
    CFbsBitGc& Gc();
    CInkdotAssistor& Assistor();
    void DoDraw();
    void Clear();
    void StartL( TInt aInkdotNbr = 0 );
    TBool SplashTest( const CInkdot& aInkdot ) const;
    void WipeL( const CInkdot& aInkdot );
    void Reverse();

public: // From CCoeControl
    void Draw();
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );

private:
    void ConstructL( const TRect& aRect );
    CCanvas( MCanvasObserver& aObserver, CFbsBitGc*& aGc );

private: // New methods
    void DrawBackground();
    void DrawInkdots();
    void DrawTouchInkdot();
    TInt Rand( TInt aRange ) const;
    TInt Find( const CInkdot& aInkdot, TInt& aIndex ) const;
    TBool HasSplashInkdot() const;

private: // Data
    MCanvasObserver& iObserver;
    CFbsBitGc*& iGc; // Not own
    CInkdotAssistor* iAssistor; // Own
    RPointerArray<CInkdot> iInkdotList; // Own
    CInkdot* iTouchInkdot; // Own
    CBmpUtils* iUtils; // Own
    CInkdotFactory* iInkdotFactory; // Own
    TBool iTouched;
    TInt iCount;
    };

#endif // C_CANVAS_H

// End of File
