/* ====================================================================
 * File: MenuButton.h
 * Created: 03/06/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_MENUBUTTON_H
#define C_MENUBUTTON_H

// INCLUDS
#include <e32base.h>

// FORWARD DECLARATIONS
class MButtonObserver;
class CFbsBitGc;
class CBmpUtils;

class CMenuButton : public CBase
    {
public:
    static CMenuButton* NewL(
        MButtonObserver& aObserver,
        CFbsBitGc*& aGc, 
        const TRect& aRect );
    virtual ~CMenuButton();

public: // New functions
    void DoDraw();
    void DoEffects();
    TInt Id() const;
    void ConstructFromResourceL( TResourceReader& aReader );
    void SetEnabled( TBool aEnabled );
    TBool IsEnabled() const;
    void SetRect( const TRect& aRect );
    TRect Rect() const;
    void ClickL( const TPoint& aPos );

private: // Constructor
    void ConstructL( const TRect& aRect );
    CMenuButton( MButtonObserver& aObserver, CFbsBitGc*& aGc );

private: // Data
    MButtonObserver& iObserver;
    CFbsBitGc*& iGc;
    HBufC* iText;
    CBmpUtils* iUtils;
    CGulIcon* iIcon;
    TInt iBtnId;
    TBool iEnabled;
    CGraphicsContext::TTextAlign iAlign;
    TInt iBitmapId;
    TInt iMaskId;
    TInt iFontHeightInTwips;
    TInt iTextBaseline;
    TRgb iColor;
    TRect iRect;
    };

#endif // C_MENUBUTTON_H

// End of File
