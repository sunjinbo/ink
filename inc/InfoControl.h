/* ====================================================================
 * File: InfoControl.h
 * Created: 03/06/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_INFOCONTROL_H
#define C_INFOCONTROL_H

// INCLUDS
#include <e32base.h>

// FORWARD DECLARATIONS
class CFbsBitGc;

class CInfoControl : public CTimer
    {
public:
    // Enmus
    enum TInfoFont
        {
        ELatinPlain12,
        ELatinBold12,
        ELatinBold13,
        ELatinBold16,
        ELatinBold17,
        ELatinBold19,
        ENumberPlain5,
        EClockBold30,
        ELatinClock14
        };

public: // Symbian constructor and destructor
    static CInfoControl* NewL(
        CFbsBitGc*& aGc,
        const TRect& aRect );
    virtual ~CInfoControl();

public: // New methods
    void SetTextL( const TDesC& aText );
    void SetTimeout( TInt aTimeout );
    void SetEnabled( TBool aEnabled );
    TBool IsEnabled() const;
    void SetInfoFont( TInfoFont aFont );
    void SetColor( TRgb aColor );
    void SetAlign( TAlign aAlign );
    void DoDraw();
    void SetRect( const TRect& aRect );
    TRect Rect() const;

private: // Constructor
    void ConstructL( const TRect& aRect );
    CInfoControl( CFbsBitGc*& aGc );

private: // From CTimer
    void RunL();
    void DoCancel();

private: // New methods
    void Start();
    void Stop();
    TInt Timeout() const;
    const CFont* InfoFont();

private: // Data
    CFbsBitGc*& iGc;
    HBufC* iText;
    TBool iEnabled;
    TRect iRect;
    TInfoFont iFont;
    TRgb iColor;
    TInt iTextBaseline;
    CGraphicsContext::TTextAlign iAlign;
    };

#endif // C_INFOCONTROL_H

// End of File
