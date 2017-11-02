/* ====================================================================
 * File: Canvas.cpp
 * Created: 03/04/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <e32math.h>
#include <Canvas.mbg>
#include "Canvas.h"
#include "CanvasObserver.h"
#include "InkdotAssistor.h"
#include "Inkdot.h"
#include "BmpUtils.h"
#include "InkdotFactory.h"

// CONSTANS
#if defined( __WINS__ )
_LIT( KMbmCanvasFileName, "Z:\\resource\\apps\\canvas.mbm" );
#else
_LIT( KMbmCanvasFileName, "\\resource\\apps\\canvas.mbm" );
#endif // __WINS__

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CCanvas::NewL
// Standard Symbian OS construction sequence
// ----------------------------------------------------------------------------
//
CCanvas* CCanvas::NewL( 
    MCanvasObserver& aObserver, CFbsBitGc*& aGc, const TRect& aRect )
    {
    CCanvas* self = new (ELeave) CCanvas( aObserver, aGc );
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CCanvas::~CCanvas
// ----------------------------------------------------------------------------
//
CCanvas::~CCanvas()
    {
    delete iAssistor;
    delete iTouchInkdot;
    delete iUtils;
    delete iInkdotFactory;
    iInkdotList.ResetAndDestroy();
    }

// ----------------------------------------------------------------------------
// CCanvas::Gc
// ----------------------------------------------------------------------------
//
CFbsBitGc& CCanvas::Gc()
    {
    return *iGc; 
    }

// ----------------------------------------------------------------------------
// CCanvas::Assistor
// ----------------------------------------------------------------------------
//
CInkdotAssistor& CCanvas::Assistor()
    {
    return *iAssistor;
    }

// ----------------------------------------------------------------------------
// CCanvas::DoDraw
// ----------------------------------------------------------------------------
//
void CCanvas::DoDraw()
    {
    DrawBackground();
    DrawInkdots();
    DrawTouchInkdot();
    }

// ----------------------------------------------------------------------------
// CCanvas::Clear
// ----------------------------------------------------------------------------
//
void CCanvas::Clear()
    {
    iCount = 0;
    iTouched = EFalse;
    iInkdotList.ResetAndDestroy();
    }

// ----------------------------------------------------------------------------
// CCanvas::StartL
// ----------------------------------------------------------------------------
//
void CCanvas::StartL( TInt aInkdotNbr )
    {
    iInkdotList.ResetAndDestroy();
    iInkdotFactory->CreateL( iInkdotList, aInkdotNbr );
    }

// ----------------------------------------------------------------------------
// CCanvas::SplashTest
// ----------------------------------------------------------------------------
//
TBool CCanvas::SplashTest( const CInkdot& aInkdot ) const
    {
    if ( iTouched )
        {
        if ( iTouchInkdot
            && iTouchInkdot != &aInkdot
            && iTouchInkdot->Intersects( aInkdot ) )
            {
            return ETrue;
            }

        for ( TInt i = 0; i < iInkdotList.Count(); i++ )
            {
            if ( iInkdotList[i] != &aInkdot
                && iInkdotList[i]->IsSplash()
                && iInkdotList[i]->Intersects( aInkdot ) )
                {
                return ETrue;
                }
            }
        }
    return EFalse;
    }

// ----------------------------------------------------------------------------
// CCanvas::WipeL
// ----------------------------------------------------------------------------
//
void CCanvas::WipeL( const CInkdot& aInkdot )
    {
    TInt index( 0 );
    if ( KErrNone == Find( aInkdot, index ) )
        {
        iInkdotList.Remove( index );
        iInkdotList.Compress();
        iObserver.AddScoreL( aInkdot.Score() );
        delete &aInkdot;
        ++iCount;
        }

    if ( iTouchInkdot == &aInkdot )
        {
        delete iTouchInkdot;
        iTouchInkdot = NULL;
        }
    
    if ( ! HasSplashInkdot() )
        {
        iObserver.CompletedL( iCount );
        }
    }

// ----------------------------------------------------------------------------
// CCanvas::Reverse
// ----------------------------------------------------------------------------
//
void CCanvas::Reverse()
    {
    if ( iTouchInkdot )
        {
        iTouchInkdot->Reverse();
        }
    
    for ( TInt i = 0; i < iInkdotList.Count(); i++ )
        {
        iInkdotList[ i ]->Reverse();
        }
    }

// ----------------------------------------------------------------------------
// CCanvas::Draw
// ----------------------------------------------------------------------------
//
void CCanvas::Draw()
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CCanvas::HandlePointerEventL
// ----------------------------------------------------------------------------
//
void CCanvas::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    if ( !iTouched && Rect().Contains( aPointerEvent.iPosition ) )
        {
        iTouched = ETrue;
        TInkdotData inkdotData;
        inkdotData.SetXY( aPointerEvent.iPosition );
        inkdotData.SetType( ETouchInkdot );
        iTouchInkdot = CInkdot::NewL( *this, inkdotData );
        }
    }

// ----------------------------------------------------------------------------
// CCanvas::ConstructL
// ----------------------------------------------------------------------------
//
void CCanvas::ConstructL( const TRect& aRect )
    {
    // Create a window for this application view
    CreateWindowL();

    SetRect( aRect );

    iUtils = CBmpUtils::NewL( 
                        KMbmCanvasFileName, 
                        EMbmCanvasCanvas_prt,
                        EMbmCanvasLastElement 
                        );

    iAssistor = CInkdotAssistor::NewL();

    iInkdotFactory = CInkdotFactory::NewL( *this );

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CCanvas::CCanvas
// ----------------------------------------------------------------------------
//
CCanvas::CCanvas( MCanvasObserver& aObserver, CFbsBitGc*& aGc )
    : iObserver ( aObserver ), iGc ( aGc )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CCanvas::DrawBackground
// ----------------------------------------------------------------------------
//
void CCanvas::DrawBackground()
    {
    iGc->SetPenStyle( CGraphicsContext::ENullPen );
    iGc->SetBrushStyle( CGraphicsContext::ENullBrush );

    if ( Rect().Width() < Rect().Height() )
        {
        iGc->DrawBitmap( 
                TRect( TPoint( 0,0 ), Rect().Size() ),
                iUtils->Bitmap( EMbmCanvasCanvas_prt ) );
        }
    else
        {
        iGc->DrawBitmap( 
                TRect( TPoint( 0,0 ), Rect().Size() ),
                iUtils->Bitmap( EMbmCanvasCanvas_lsc ) );
        }
    }

// ----------------------------------------------------------------------------
// CCanvas::DrawInkdots
// ----------------------------------------------------------------------------
//
void CCanvas::DrawInkdots()
    {
    for ( TInt i = 0; i < iInkdotList.Count(); i++ )
        {
        iInkdotList[i]->DoDraw();
        }
    }

// ----------------------------------------------------------------------------
// CCanvas::DrawTouchInkdot
// ----------------------------------------------------------------------------
//
void CCanvas::DrawTouchInkdot()
    {
    if ( iTouchInkdot )
        {
        iTouchInkdot->DoDraw();
        }
    }

// ----------------------------------------------------------------------------
// CCanvas::Rand
// ----------------------------------------------------------------------------
//
TInt CCanvas::Rand( TInt aRange ) const
    {
    return Math::Random() % aRange;
    }

// ----------------------------------------------------------------------------
// CCanvas::Find
// ----------------------------------------------------------------------------
//
TInt CCanvas::Find( const CInkdot& aInkdot, TInt& aIndex ) const
        {
        for ( TInt i = 0; i < iInkdotList.Count(); i++ )
            {
            if ( iInkdotList[i] == &aInkdot )
                {
                aIndex = i;
                return KErrNone;
                }
            }
        return KErrNotFound;
        }

// ----------------------------------------------------------------------------
// CCanvas::HasSplashInkdot
// ----------------------------------------------------------------------------
//
TBool CCanvas::HasSplashInkdot() const
    {
    if ( iTouchInkdot )
        {
        return ETrue;
        }

    for ( TInt i = 0; i < iInkdotList.Count(); i++ )
        {
        if ( iInkdotList[ i ]->IsSplash() )
            {
            return ETrue;
            }
        }

    return EFalse;
    }

// End of File
