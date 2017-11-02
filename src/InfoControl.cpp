/* ====================================================================
 * File: InfoControl.cpp
 * Created: 03/06/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <bitstd.h>
#include <StringLoader.h>
#include <fbs.h>
#include <aknutils.h>
#include "InfoControl.h"

// CONSTANTS
//const TInt KMaxBufferLen = 25;
//const TInt KInfoControlTimeout = 1000000; // One second

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CInfoControl::NewL
// ----------------------------------------------------------------------------
//
CInfoControl* CInfoControl::NewL(
    CFbsBitGc*& aGc,const TRect& aRect )
    {
    CInfoControl* self = new (ELeave) CInfoControl( aGc );
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CInfoControl::~CInfoControl
// ----------------------------------------------------------------------------
//
CInfoControl::~CInfoControl()
    {
    Cancel();
    delete iText;
    }

// ----------------------------------------------------------------------------
// CInfoControl::SetLevel
// ----------------------------------------------------------------------------
//
void CInfoControl::SetTextL( const TDesC& aText )
    {
    if ( iText )
        {
        delete iText;
        iText = NULL;
        }
    iText =  HBufC::NewL( aText.Length() );
    TPtr text( iText->Des() );
    text.Copy( aText );
    }

// ----------------------------------------------------------------------------
// CInfoControl::SetTimeout
// ----------------------------------------------------------------------------
//
void CInfoControl::SetTimeout( TInt aTimeout )
    {
    if ( !IsActive() )
        {
        CTimer::After( aTimeout );
        }
    }

// ----------------------------------------------------------------------------
// CInfoControl::SetEnabled
// ----------------------------------------------------------------------------
//
void CInfoControl::SetEnabled( TBool aEnabled )
    {
    iEnabled = aEnabled;
    }

// ----------------------------------------------------------------------------
// CInfoControl::IsEnabled
// ----------------------------------------------------------------------------
//
TBool CInfoControl::IsEnabled() const
    {
    return iEnabled;
    }

// ----------------------------------------------------------------------------
// CInfoControl::SetInfoFont
// ----------------------------------------------------------------------------
//
void CInfoControl::SetInfoFont( TInfoFont aFont )
    {
    iFont = aFont;
    }

// ----------------------------------------------------------------------------
// CInfoControl::SetColor
// ----------------------------------------------------------------------------
//
void CInfoControl::SetColor( TRgb aColor )
    {
    iColor = aColor;
    }

// ----------------------------------------------------------------------------
// CInfoControl::SetAlign
// ----------------------------------------------------------------------------
//
void CInfoControl::SetAlign( TAlign aAlign )
    {
    iAlign = (CGraphicsContext::TTextAlign)aAlign;
    }

// ----------------------------------------------------------------------------
// CInfoControl::DoDraw
// ----------------------------------------------------------------------------
//
void CInfoControl::DoDraw()
    {
    if ( iEnabled && iText )
        {
         iGc->SetBrushStyle( CGraphicsContext::ENullBrush );
         iGc->SetPenColor( iColor );
         iGc->SetPenStyle( CGraphicsContext::ESolidPen );
         iGc->UseFont( InfoFont() );
         iGc->DrawText( *iText, iRect, iTextBaseline, iAlign, 0 );
        }
    }

// ----------------------------------------------------------------------------
// CInfoControl::SetRect
// ----------------------------------------------------------------------------
//
void CInfoControl::SetRect( const TRect& aRect )
    {
    iRect = aRect;
    }

// ----------------------------------------------------------------------------
// CInfoControl::Rect
// ----------------------------------------------------------------------------
//
TRect CInfoControl::Rect() const
    {
    return iRect;
    }

// ----------------------------------------------------------------------------
// CInfoControl::ConstructL
// ----------------------------------------------------------------------------
//
void CInfoControl::ConstructL( const TRect& aRect )
    {
    CTimer::ConstructL();
    iRect = aRect;
    }

// ----------------------------------------------------------------------------
// CInfoControl::CInfoControl
// ----------------------------------------------------------------------------
//
CInfoControl::CInfoControl( CFbsBitGc*& aGc )
    : CTimer( EPriorityStandard ), iGc( aGc ), iEnabled( ETrue )
    {
    CActiveScheduler::Add( this );
    }

// ----------------------------------------------------------------------------
// CInfoControl::RunL
// ----------------------------------------------------------------------------
//
void CInfoControl::RunL()
    {
    if ( iStatus == KErrNone )
        {
        DoCancel();
        iEnabled = EFalse;
        }
    }

// ----------------------------------------------------------------------------
// CInfoControl::DoCancel
// ----------------------------------------------------------------------------
//
void CInfoControl::DoCancel()
    {
    CTimer::DoCancel(); 
    }

// ----------------------------------------------------------------------------
// CInfoControl::InfoFont
// ----------------------------------------------------------------------------
//
const CFont* CInfoControl::InfoFont()
    {
    const CFont* font = NULL;
    switch( iFont )
        {
        case ELatinPlain12:
            font = LatinPlain12();
            iTextBaseline = 12;
            break;
        case ELatinBold12:
            font = LatinBold12();
            iTextBaseline = 12;
            break;
        case ELatinBold13:
            font = LatinBold13();
            iTextBaseline = 13;
            break;
        case ELatinBold16:
            font = LatinBold16();
            iTextBaseline = 16;
            break;
        case ELatinBold17:
            font = LatinBold17();
            iTextBaseline = 17;
            break;
        case ELatinBold19:
            font = LatinBold19();
            iTextBaseline = 19;
            break;
        case ENumberPlain5:
            font = NumberPlain5();
            iTextBaseline = 5;
            break;
        case EClockBold30:
            font = ClockBold30();
            iTextBaseline = 30;
            break;
        case ELatinClock14:
            font = LatinClock14();
            iTextBaseline = 14;
            break;
        default:
            break;
        }
    return font;
    }

// End of File
